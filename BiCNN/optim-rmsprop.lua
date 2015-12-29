-- RMSProp
-- Author: Minwei Feng (mfeng@us.ibm.com)
require 'optim'

function optim.rmsprop(opfunc, w, config, state)
   local config = config or {}   
   local state = state or config
   local mode = config.mode or 'global'  -- global or local
   local decay = config.decay
   local lr = config.lr
   local momentum = config.momentum
   local epsilon = config.epsilon
   if mode == 'local' then
      state.gradAccum = state.gradAccum or torch.Tensor():resizeAs(w):fill(0)
      state.gradSqAccum = state.gradSqAccum or torch.Tensor():resizeAs(w):fill(0)
      state.update = state.update or torch.Tensor():resizeAs(w):fill(0)
      state.gradRms = state.gradRms or torch.Tensor():resizeAs(w):fill(0)
   end

   local pc = config.pclient or nil
   local su = config.su or 0 -- sync updates (grad and param)

   state.pversion = state.pversion or 0
   state.dusync = state.dusync or 0   

   local fx,dfdx = opfunc(w)

   if pc and su>1 then

      -- accumulate grad
      if not config.accumulated then -- need one copy to accumulate
	      config.accumulated = torch.Tensor():typeAs(dfdx):resizeAs(dfdx):fill(0)
	      pc:reset(w,config.accumulated)
      end
      
      if mode == 'global' then
        config.accumulated:add(dfdx)
        if state.pversion%su==0 then
           pc:async_send_grad()
           pc:async_recv_param()
           local synctime = sys.clock()
           pc:wait()
           state.dusync = state.dusync + sys.clock()-synctime
           config.accumulated:fill(0)
        else
           --do nothing here
        end
      elseif mode == 'local' then
         state.gradAccum:mul(decay):add(1 - decay, dfdx)
         state.gradSqAccum:mul(decay):add(1 - decay, torch.cmul(dfdx, dfdx))
         state.gradRms:copy(state.gradSqAccum)
           :add(-1, torch.cmul(state.gradAccum, state.gradAccum))
           :add(epsilon):sqrt()
         state.update:mul(momentum):add(-lr, torch.cdiv(dfdx, state.gradRms))  
         config.accumulated:add(state.update)
         if state.pversion%su==0 then
           pc:async_send_grad()
           pc:async_recv_param()
           local synctime = sys.clock()
           pc:wait()
           state.dusync = state.dusync + sys.clock()-synctime
           config.accumulated:fill(0)
         else
           w:add(state.update)
         end
      end
   elseif pc and su==1 then
      if mode == 'global' then
         pc:async_send_grad()
         pc:async_recv_param()
         local synctime = sys.clock()
         pc:wait()
         state.dusync = state.dusync + sys.clock()-synctime
      elseif mode == 'local' then
         if not config.resetupdate then
            config.resetupdate = true
            pc:reset(w,state.update)
         end
         state.gradAccum:mul(decay):add(1 - decay, dfdx)
         state.gradSqAccum:mul(decay):add(1 - decay, torch.cmul(dfdx, dfdx))
         state.gradRms:copy(state.gradSqAccum)
           :add(-1, torch.cmul(state.gradAccum, state.gradAccum))
           :add(epsilon):sqrt()
         state.update:mul(momentum):add(-lr, torch.cdiv(dfdx, state.gradRms)) 
         pc:async_send_grad()
         pc:async_recv_param()
         local synctime = sys.clock()
         pc:wait()
         state.dusync = state.dusync + sys.clock()-synctime
         collectgarbage()
      else
         error("Incorrect mode: " .. mode)
      end
   else
      assert(false)
   end
   state.pversion = state.pversion + 1      
   return w,{fx}
end
