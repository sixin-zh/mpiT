-- Parameter server
-- Author: Sixin Zhang (zsx@cims.nyu.edu)
-- Important change: 
-- init the parameter from the first local worker (once and only once)
-- before other service gets started. From the pclient side, 
-- it's also the first local pclient (worker) who sends its parameter
-- to the psever.
require 'mpiT'

local pServer = torch.class('pServer')

function pServer:__init(conf,state)
   self.state = state or {}
   self.rank = conf.rank or -1
   self.cranks = conf.cranks or {} -- client ranks
   self.mtype = mpiT.FLOAT
   self.mworld = conf.world or mpiT.COMM_WORLD

   self.offset = -1 -- offset of param grad
   self.size = -1 -- size of param grad
   self.tensor = {} -- tensor from storage
   self.storage = {} -- param gradient storage
   self.emptys = torch.Storage()

   self.state.on = false
   self.state.io = false
   self.state.iostop = 0
   self.coq = Queue() -- coroutine queue

   self.conf = conf
end

local function pServer_recvinit(self,crank)
   coroutine.yield(mpiT.signal_INIT)
   -- get meta info
   local cinfo = torch.LongStorage(2)
   mpiT.aio_recv(cinfo,2,mpiT.LONG,
		 crank,mpiT.tag_ps_recv_init,self.mworld,self.state)
   -- init storage 
   if self.offset == -1 then
      self.offset = cinfo[1]
      self.size = cinfo[2]
      self.storage.p = torch.Storage(self.size)
      self.storage.g = {}
      self.storage.g[crank] = torch.Storage(self.size)
      self.tensor.p = torch.Tensor(self.storage.p)
      self.tensor.g = {}
      self.tensor.g[crank] = torch.Tensor(self.storage.g[crank])
   else
      assert(self.offset == cinfo[1])
      assert(self.size == cinfo[2])
      self.storage.g[crank] = torch.Storage(self.size)
      self.tensor.g[crank] = torch.Tensor(self.storage.g[crank])
   end
   --print('pServer:recvinit',self.rank,crank,self.offset,self.size)
   coroutine.yield(mpiT.signal_DONE)
end

local function pServer_sendparam(self,crank)
   coroutine.yield(mpiT.signal_INIT)
   while (self.state.on) do
      --print('pServer_sendparam to recv',crank,self.size)
      mpiT.aio_recv(self.emptys,0,self.mtype,
		    crank,mpiT.tag_ps_recv_header,self.mworld,self.state)
      --print('ps ' .. self.rank .. ' send param to ' .. crank)
      if self.state.io then
      	 mpiT.aio_send(self.storage.p,self.size,self.mtype,
		       crank,mpiT.tag_ps_send_param,self.mworld,self.state)
      end
   end
   coroutine.yield(mpiT.signal_DONE)
end

-- Warning: no lock on self.tensor.p during this recvgrad, expect inconsistent read
local function pServer_recvgrad(self,crank)
   coroutine.yield(mpiT.signal_INIT)
   while (self.state.on) do      
      -- recv
      mpiT.aio_recv(self.storage.g[crank],self.size,self.mtype,
		    crank,mpiT.tag_ps_recv_grad,self.mworld,self.state)
      --print('ps ' .. self.rank .. ' recv grad from ' .. crank)
      -- apply
      self.tensor.p:add(self.tensor.g[crank])
      if self.state.on then
         mpiT.aio_send(self.emptys,0,self.mtype,
	  	       crank,mpiT.tag_ps_recv_grad_tail,self.mworld,self.state)
      end
   end
   coroutine.yield(mpiT.signal_DONE)
end

local function pServer_recvparam(self,crank)
   coroutine.yield(mpiT.signal_INIT)
   mpiT.aio_recv(self.storage.p,self.size,self.mtype,
		 crank,mpiT.tag_ps_recv_param,self.mworld,self.state)
   if self.state.on then
      mpiT.aio_send(self.emptys,0,self.mtype,
                    crank,mpiT.tag_ps_recv_param_tail,self.mworld,self.state)
   end
   --print('ps ' .. self.rank .. ' recv param from ' .. crank)
   coroutine.yield(mpiT.signal_DONE)
end

-- stop
function table.len(tbl)
   local l=0
   if tbl then
      for k,v in pairs(tbl) do
	 l=l+1
      end
   end
   return l
end

local function pServer_recvstop(self,crank)
   coroutine.yield(mpiT.signal_INIT)
   local tostop = torch.ByteStorage(1)
   mpiT.aio_recv(tostop,1,mpiT.BYTE,
		 crank,mpiT.tag_ps_recv_stop,self.mworld,self.state)
   if tostop[1] then
      self.state.iostop = self.state.iostop + 1
      if self.state.iostop == table.len(self.cranks) then
	 self.state.on = false
	 self.state.io = false
	 -- print('server', self.rank, 'finally stoped by', crank)
      end
   end
   coroutine.yield(mpiT.signal_DONE)
end

function pServer:start()
   self.state.on = true
   self.state.io = true
   -- init
   self.coq:clear()
   for i,crank in pairs(self.cranks) do
      local co = mpiT.co_execute(pServer_recvinit,{self,crank})
      self.coq:push(co)
   end
   mpiT.co_wait(self.coq)
   for i,crank in pairs(self.cranks) do      
      if i == 1 then 
         -- init the parameter from the first local worker
         local co3 = mpiT.co_execute(pServer_recvparam,{self,crank})      
         self.coq:push(co3)
         mpiT.co_wait(self.coq)
      end
      -- on request
      local co0 = mpiT.co_execute(pServer_recvstop,{self,crank})
      local co1 = mpiT.co_execute(pServer_recvgrad,{self,crank})
      local co2 = mpiT.co_execute(pServer_sendparam,{self,crank})
      self.coq:push(co0)
      self.coq:push(co1)
      self.coq:push(co2)
   end
   mpiT.co_wait(self.coq)
end
