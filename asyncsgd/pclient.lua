-- Parameter client
-- Author: Sixin Zhang (zsx@cims.nyu.edu)
require 'mpiT'

local pClient = torch.class('pClient')

function pClient:__init(conf,state)
   self.state = state or {}
   self.rank = conf.rank or -1
   self.sranks = conf.sranks or {} -- server ranks
   self.cranks = conf.cranks or {} -- client ranks   
   self.plong = conf.plong or 0 -- size of whole parameter
   self.pstorage = conf.pstorage or torch.Storage()
   self.gstorage = conf.gstorage or torch.Storage()
   self.emptys = torch.Storage()
   self.sinfo = {}
   self.mtype = mpiT.FLOAT
   self.mworld = conf.world or mpiT.COMM_WORLD
   self.coq = Queue() -- coroutine queue
   self.state.on = false
   self.state.io = false
   self.conf = conf
end

local function pClient_sendinit(self,srank,offset,size)
   coroutine.yield(mpiT.signal_INIT)   
   --print('pClient:sendinit',self.rank,srank,offset,size)
   self.sinfo[srank] = {}
   self.sinfo[srank].offset = offset
   self.sinfo[srank].size = size
   local cinfo = torch.LongStorage(2)
   cinfo[1] = offset
   cinfo[2] = size
   mpiT.aio_send(cinfo,2,mpiT.LONG,
		 srank,mpiT.tag_ps_recv_init,self.mworld,self.state)
   --print('pClient:sendinit done')
   coroutine.yield(mpiT.signal_DONE)
end

local function pClient_sendstop(self,srank) 
   coroutine.yield(mpiT.signal_INIT)
   local tostop = torch.ByteStorage(1):fill(1)
   mpiT.aio_send(tostop,1,mpiT.BYTE,
		 srank,mpiT.tag_ps_recv_stop,self.mworld,self.state)
   coroutine.yield(mpiT.signal_DONE)   
end

local function pClient_sendgrad(self,grad,srank)
   coroutine.yield(mpiT.signal_INIT)
   local sgrad = torch.Storage(grad,
			       self.sinfo[srank].offset,
			       self.sinfo[srank].size)
   mpiT.aio_send(sgrad,sgrad:size(),self.mtype,
		 srank,mpiT.tag_ps_recv_grad,self.mworld,self.state)
   mpiT.aio_recv(self.emptys,0,self.mtype,
                 srank,mpiT.tag_ps_recv_grad_tail,self.mworld,self.state)
   coroutine.yield(mpiT.signal_DONE)
end

local function pClient_sendparam(self,param,srank)
   coroutine.yield(mpiT.signal_INIT)
   local sparam = torch.Storage(param,
				self.sinfo[srank].offset,
				self.sinfo[srank].size)
   mpiT.aio_send(sparam,sparam:size(),self.mtype,
		 srank,mpiT.tag_ps_recv_param,self.mworld,self.state)
   mpiT.aio_recv(self.emptys,0,self.mtype,
                 srank,mpiT.tag_ps_recv_param_tail,self.mworld,self.state)
   coroutine.yield(mpiT.signal_DONE)
end

local function pClient_recvparam(self,param,srank)
   coroutine.yield(mpiT.signal_INIT)
   mpiT.aio_send(self.emptys,0,self.mtype,
		 srank,mpiT.tag_ps_recv_header,self.mworld,self.state)
   local sparam = torch.Storage(param,
				self.sinfo[srank].offset,
				self.sinfo[srank].size)
   mpiT.aio_recv(sparam,sparam:size(),self.mtype,
		 srank,mpiT.tag_ps_send_param,self.mworld,self.state)
   coroutine.yield(mpiT.signal_DONE)   
end

function pClient:async_recv_param()
   local param = self.pstorage
   for i,srank in pairs(self.sranks) do
      --print('pc ' .. self.rank .. ' recv param from ' .. srank)
      local co = mpiT.co_execute(pClient_recvparam,{self,param,srank})
      self.coq:push(co)
   end
end

function pClient:async_send_grad()
   local grad = self.gstorage
   for i,srank in pairs(self.sranks) do
      --print('pc ' .. self.rank .. ' send grad to ' .. srank)
      local co = mpiT.co_execute(pClient_sendgrad,{self,grad,srank})
      self.coq:push(co)
   end
end

function pClient:async_send_param()
   local param = self.pstorage
   for i,srank in pairs(self.sranks) do
      --print('pc send param to ' .. srank)
      local co = mpiT.co_execute(pClient_sendparam,{self,param,srank})
      self.coq:push(co)
   end
end

local function pClient_init(self)
   -- set offset size for each piece of parameter server
   local offset = 1
   local size = math.floor(self.plong/#self.sranks)
   for i,srank in pairs(self.sranks) do
      if i == #self.sranks then
	 size = self.plong - offset + 1
      end
      local co = mpiT.co_execute(pClient_sendinit,{self,srank,offset,size})
      self.coq:push(co)
      offset = offset + size
   end
   mpiT.co_wait(self.coq)
   -- init pserver param
   if self.rank == self.cranks[1] then
      self:async_send_param(self.pstorage)
   end
   mpiT.co_wait(self.coq)
end

function pClient:ping(nb)
   local nb = nb or self.coq:len()
   for n=1,nb do
      mpiT.co_ping(self.coq)
   end
end

function pClient:reset(param,grad)
   if param then
      self.pstorage = param:storage()
      self.plong = self.pstorage:size()
      if grad then
	 self.gstorage = grad:storage()
	 assert(self.plong == self.gstorage:size())
      end
   end  
end

function pClient:wait()
   mpiT.co_wait(self.coq)
end

function pClient:stop()
   self:wait()
   -- stop servers
   for i,srank in pairs(self.sranks) do
      -- print('to stop server', srank)
      local co0 = mpiT.co_execute(pClient_sendstop,{self,srank})
      self.coq:push(co0)
   end
   self:wait()
   self.state.io = false
   self.state.on = false
end

function pClient:start(param,grad)
   self.state.on = true
   self.state.io = true
   if param then
      self.pstorage = param:storage()
      self.plong = self.pstorage:size()
      if grad then
	 self.gstorage = grad:storage()
	 assert(self.plong == self.gstorage:size())
      end
   end
   -- print('i am pc',self.rank,'p',self.pstorage:size(),'g',self.gstorage:size())
   pClient_init(self)
end
