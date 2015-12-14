-- Parameter server
-- Author: Sixin Zhang (zsx@cims.nyu.edu)
-- Augmented by Minwei Feng (mfeng@us.ibm.com)
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
      if self.conf.opt.optimization == 'rmsprop' then
         self.gradAccum = torch.Tensor():resizeAs(self.tensor.p):zero()
         self.gradSqAccum = torch.Tensor():resizeAs(self.tensor.p):zero()
         self.update = torch.Tensor():resizeAs(self.tensor.p):zero()
         self.gradRms = torch.Tensor():resizeAs(self.tensor.p):zero() 
      end
      
      if self.conf.opt.optimization == 'adam' then
         self.adam_t = 0
         self.adam_m = torch.Tensor():resizeAs(self.tensor.p):zero()
         self.adam_v = torch.Tensor():resizeAs(self.tensor.p):zero()
         self.adam_d = torch.Tensor():resizeAs(self.tensor.p):zero()
      end
      
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
 --     if self.rank == 1 then
 --        print("rank " .. self.rank .. " " .. collectgarbage("count"))
 --     end
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
       if self.conf.opt.optimization == 'rmsprop' then
         if self.conf.opt.modeRMSProp == 'global' then
            local decay = self.conf.opt.decayRMSProp
            local lr = self.conf.opt.lrRMSProp
            local momentum = self.conf.opt.momentumRMSProp
            local epsilon = self.conf.opt.epsilonRMSProp
      
            self.gradAccum:mul(decay):add(1 - decay, self.tensor.g[crank])
            self.gradSqAccum:mul(decay):add(1 - decay, torch.cmul(self.tensor.g[crank], self.tensor.g[crank]))
            self.gradRms:copy(self.gradSqAccum)
              :add(-1, torch.cmul(self.gradAccum, self.gradAccum))
              :add(epsilon):sqrt()
            self.update:mul(momentum):add(-lr, torch.cdiv(self.tensor.g[crank], self.gradRms))
            self.tensor.p:add(self.update)
         elseif self.conf.opt.modeRMSProp == 'local' then
            self.tensor.p:add(self.tensor.g[crank])
         end
       elseif self.conf.opt.optimization == 'adam' then
          if self.conf.opt.modeAdam == 'global' then
            local lr = self.conf.opt.lrAdam
            local beta1 = self.conf.opt.beta1Adam
            local beta2 = self.conf.opt.beta2Adam
            local epsilon = self.conf.opt.epsilonAdam
      
            self.adam_t = self.adam_t + 1
            self.adam_m:mul(beta1):add(1-beta1, self.tensor.g[crank])
            self.adam_v:mul(beta2):addcmul(1-beta2, self.tensor.g[crank], self.tensor.g[crank])
            self.adam_d:copy(self.adam_v):sqrt():add(epsilon)
            local beta1_t = 1 - math.pow(beta1, math.floor(self.adam_t/self.conf.opt.stepDivAdam) + 1 )
            local beta2_t = 1 - math.pow(beta2, math.floor(self.adam_t/self.conf.opt.stepDivAdam) + 1 )
            local lr_t = lr * math.sqrt(beta2_t)/beta1_t
            self.tensor.p:addcdiv(-lr_t, self.adam_m, self.adam_d)
         end
      else
         self.tensor.p:add(self.tensor.g[crank])
      end
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
