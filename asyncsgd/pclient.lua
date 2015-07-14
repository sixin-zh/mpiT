require 'mpiT'

local pClient = torch.class('pClient')

function pClient:__init(conf)
   self.state = {}
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
   self.maxsec = conf.maxsec or 60
   self.ss = conf.ss or './pcstate.th'
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
		 srank,mpiT.tag_ps_recv_init,self.mworld)
   --print('pClient:sendinit done')
   coroutine.yield(mpiT.signal_DONE)
end

local function pClient_sendstop(self,srank) 
   coroutine.yield(mpiT.signal_INIT)
   local tostop = torch.ByteStorage(1):fill(1)
   mpiT.aio_send(tostop,1,mpiT.BYTE,
		 srank,mpiT.tag_ps_recv_stop,self.mworld)
   coroutine.yield(mpiT.signal_DONE)   
end

local function pClient_sendgrad(self,grad,srank)
   coroutine.yield(mpiT.signal_INIT)
   local sgrad = torch.Storage(grad,
			       self.sinfo[srank].offset,
			       self.sinfo[srank].size)
   -- print('pClient_sendgrad',srank,sgrad)
   mpiT.aio_send(sgrad,sgrad:size(),self.mtype,
		 srank,mpiT.tag_ps_recv_grad,self.mworld)
   coroutine.yield(mpiT.signal_DONE)
   -- self.state.count_sendgrad = self.state.count_sendgrad + 1
end

local function pClient_sendparam(self,param,srank)
   coroutine.yield(mpiT.signal_INIT)
   local sparam = torch.Storage(param,
				self.sinfo[srank].offset,
				self.sinfo[srank].size)
   mpiT.aio_send(sparam,sparam:size(),self.mtype,
		 srank,mpiT.tag_ps_recv_param,self.mworld)
   coroutine.yield(mpiT.signal_DONE)
end

local function pClient_recvparam(self,param,srank)
   coroutine.yield(mpiT.signal_INIT)
   -- send
   mpiT.aio_send(self.emptys,0,self.mtype,
		 srank,mpiT.tag_ps_recv_header,self.mworld)
   -- print('pClient_recvparam to snd',srank,param:size(),self.sinfo[srank])
   -- recv
   local sparam = torch.Storage(param,
				self.sinfo[srank].offset,
				self.sinfo[srank].size)
   --print('pClient_recvparam to rev',srank,sparam:size())
   mpiT.aio_recv(sparam,sparam:size(),self.mtype,
		 srank,mpiT.tag_ps_send_param,self.mworld)
   --print('pClient_recvparam done',srank)
   coroutine.yield(mpiT.signal_DONE)   
   -- self.state.count_recvparam = self.state.count_recvparam + 1
end

function pClient:async_recv_param()
   local param = self.pstorage
   for i,srank in pairs(self.sranks) do
      local co = mpiT.co_execute(pClient_recvparam,{self,param,srank})
      self.coq:push(co)
   end
end

function pClient:async_send_grad()
   local grad = self.gstorage
   for i,srank in pairs(self.sranks) do
      local co = mpiT.co_execute(pClient_sendgrad,{self,grad,srank})
      self.coq:push(co)
   end
end

function pClient:async_send_param()
   local param = self.pstorage
   for i,srank in pairs(self.sranks) do
      local co = mpiT.co_execute(pClient_sendparam,{self,param,srank})
      self.coq:push(co)
   end
end

local function pClient_init(self)
   -- set offset size for each piece of parameter server
   local offset = 0
   local size = math.floor(self.plong/#self.sranks)
   for i,srank in pairs(self.sranks) do
      if i == #self.sranks then
	 size = self.plong - offset
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

function pClient:wait()
   mpiT.co_wait(self.coq)
end

function pClient:save()
   --print('save state',self.state)
   --torch.save(self.ss,self.state)
end

function pClient:stop()
   -- stop servers
   for i,srank in pairs(self.sranks) do
      -- print('to stop server', srank)
      local co0 = mpiT.co_execute(pClient_sendstop,{self,srank})
      self.coq:push(co0)
   end
   mpiT.co_wait(self.coq)
end

function pClient:start(param,grad)
   --print(param:size(),grad:size())
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
   -- emulate async sgd
   --local begin = os.time()
   --local now = os.time()
   -- self.state.count_recvparam = 0
   -- self.state.count_sendgrad = 0
   -- send p to ps
   --self.coq:clear()   
   --while ((now-begin)<self.maxsec) do
      -- compute g
      -- (get new data)
      -- wait g
      --local param = self.pstorage
      --local grad = self.gstorage
      --grad:fill(os.time())

      --self:async_send_grad(grad)
      --self:async_recv_param(param)
      --self:sync()

      -- print('got param', param)
      --now = os.time()
   --end
   --self:save()
   --self:stop()
end
