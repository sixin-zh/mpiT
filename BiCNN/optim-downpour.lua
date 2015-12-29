-- DOWNPOUR
-- Author: Sixin Zhang (zsx@cims.nyu.edu)
-- when su==1, it is the asyncsgd/hogwild
require 'optim'

function optim.downpour(opfunc, w, config, state)
   local config = config or {}   
   local state = state or config
   
   local lr = config.lr or 0 -- learning rate
   local lrd = config.lrd or 0 -- learning rate decay
   local l2wd = config.l2wd or 0

   local pc = config.pclient or nil
   local su = config.su or 0 -- sync updates (grad and param)

   state.pversion = state.pversion or 0
   state.dusync = state.dusync or 0   
   
   if lrd ~= 0 then 
      lr = lr / (1 + state.pversion*lrd)
   end
   local fx,dfdx = opfunc(w)
   if l2wd ~= 0 then dfdx:add(l2wd, w) end

   if pc and su>1 then
      -- apply lr
      dfdx:mul(-lr)
      -- accumulate grad
      if not config.dfdx then -- need one copy to accumulate
	 config.dfdx = torch.Tensor():typeAs(dfdx):resizeAs(dfdx):fill(0)
	 pc:reset(w,config.dfdx)
      end
      config.dfdx:add(dfdx)
      -- send grads and get new param
      if state.pversion%su==0 then
	 pc:async_send_grad()
	 pc:async_recv_param()
	 local synctime = sys.clock()
         pc:wait()
	 state.dusync = state.dusync + sys.clock()-synctime
	 config.dfdx:fill(0)
      else
	 w:add(dfdx) -- move locally
      end
   elseif pc and su==1 then
      -- apply lr
      dfdx:mul(-lr)
      -- send
      pc:async_send_grad()
      pc:async_recv_param()
      local synctime = sys.clock()
      pc:wait()
      state.dusync = state.dusync + sys.clock()-synctime
   else
      assert(false)
   end
   state.pversion = state.pversion + 1      
   return w,{fx}
end
