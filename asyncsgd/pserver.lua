require 'mpiT'

local pServer = torch.class('pServer')

function pServer:__init(conf)
   self.state = {}
   self.rank = conf.rank or -1
   self.cranks = conf.cranks or {} -- client ranks
   self.mtype = mpiT.FLOAT
   self.mworld = conf.world or mpiT.COMM_WORLD

   self.offset = -1 -- offset of param grad
   self.size = -1 -- size of param grad
   self.tensor = {} -- tensor from storage
   self.storage = {} -- param gradient storage
   self.emptys = torch.Storage()

   self.on = false
   self.coq = Queue() -- coroutine queue

   self.lr = conf.lr or 1e-2

   self.conf = conf
end

local function pServer_recvinit(self,crank)
   --print('pServer:recvinit',crank)
   coroutine.yield(mpiT.signal_INIT)
   -- get meta info
   local cinfo = torch.LongStorage(2)
   mpiT.aio_recv(cinfo,2,mpiT.LONG,
		 crank,mpiT.tag_ps_recv_init,self.mworld)
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
   while (self.on) do
      --print('pServer_sendparam init',crank,self.size)
      -- recv
      mpiT.aio_recv(self.emptys,0,self.mtype,
		    crank,mpiT.tag_ps_recv_header,self.mworld)
      -- send
      --print('pServer_sendparam send',crank)
      -- self.storage.p:fill(os.time()) -- DEBUG
      mpiT.aio_send(self.storage.p,self.size,self.mtype,
		    crank,mpiT.tag_ps_send_param,self.mworld) -- lock?
      --print('send param', crank, self.storage.p)
      --print('pServer_sendparam done',crank)
   end
   coroutine.yield(mpiT.signal_DONE)
end

local function pServer_recvgrad(self,crank)
   coroutine.yield(mpiT.signal_INIT)
   while (self.on) do      
      -- recv
      mpiT.aio_recv(self.storage.g[crank],self.size,self.mtype,
		    crank,mpiT.tag_ps_recv_grad,self.mworld)
      -- apply      
      self.tensor.p:add(-self.lr,self.tensor.g[crank])
      --print('pServer_recvgrad',crank)
      --print('got grad', self.rank, crank, self.storage.g)
   end
   coroutine.yield(mpiT.signal_DONE)
end

local function pServer_recvparam(self,crank)
   coroutine.yield(mpiT.signal_INIT)
   while (self.on) do      
      mpiT.aio_recv(self.storage.p,self.size,self.mtype,
		    crank,mpiT.tag_ps_recv_param,self.mworld)
   end
   coroutine.yield(mpiT.signal_DONE)
end

-- stop, save state
local function pServer_recvstop(self,crank)
   coroutine.yield(mpiT.signal_INIT)
   local tostop = torch.ByteStorage(1)
   mpiT.aio_recv(tostop,1,mpiT.BYTE,
		 crank,mpiT.tag_ps_recv_stop,self.mworld)
   if tostop[1] then
      self.on = false
   end
   coroutine.yield(mpiT.signal_DONE)
   -- print('server', self.rank, 'stoped by', crank)
   mpiT.Finalize()
   exit()
end

function pServer:start()
   self.on = true
   -- init
   self.coq:clear()
   for i,crank in pairs(self.cranks) do
      local co = mpiT.co_execute(pServer_recvinit,{self,crank})
      self.coq:push(co)
   end
   mpiT.co_wait(self.coq)
   -- on request
   for i,crank in pairs(self.cranks) do      
      local co0 = mpiT.co_execute(pServer_recvstop,{self,crank})
      local co1 = mpiT.co_execute(pServer_recvgrad,{self,crank})
      local co2 = mpiT.co_execute(pServer_sendparam,{self,crank})
      if i == 1 then 
         local co3 = mpiT.co_execute(pServer_recvparam,{self,crank})      
         self.coq:push(co3)
      end 
      self.coq:push(co0)
      self.coq:push(co1)
      self.coq:push(co2)
   end
   mpiT.co_wait(self.coq)
end
