-- Async EASGD/EAMSGD
-- Author: Sixin Zhang (zsx@cims.nyu.edu)
-- when mom==0, it is the easgd
require 'optim'

function optim.eamsgd(opfunc, w, config, state)
   local config = config or {}   
   local state = state or config
  
   local lr = config.lr or 0   -- learning rate \eta
   local lrd = config.lrd or 0 -- learning rate decay
   local lrp = config.lrp or 0 -- learning rate decay power
   local mom = config.mom or 0 -- momentum term \delta
   local l2wd = config.l2wd or 0

   local pc = config.pclient or nil
   local mva = config.mva or 0 -- moving rate \alpha
   local su = config.su or 1   -- comm period \tau

   state.pversion = state.pversion or 0
   state.dusync = state.dusync or 0

   local fx,dfdx
   local function localupdate()
      if lr ~= 0 then
	 if mom > 0 then
	    if not state.vt then
	       state.vt = w:clone():zero()
	    end
	    state.vt:mul(mom)
	    w:add(state.vt)
	 end	 	 
	 fx,dfdx = opfunc(w)
	 if l2wd ~= 0 then dfdx:add(l2wd, w) end	 
	 local clr = lr
	 if lrd ~= 0 and lrp > 0 then 
	    clr = lr / math.pow(1+state.pversion*lrd,lrp)
	 end
	 w:add(-clr,dfdx)
	 if mom > 0 then
	    state.vt:add(-clr,dfdx)
	 end
	 state.pversion = state.pversion + 1	         
      end
   end
   
   if (pc and su>0 and mva>0) then
      if (state.pversion%su == 0) then
	 if not config.suw then -- need 2 copies
	    config.suw = torch.Tensor():typeAs(w):resizeAs(w):fill(0)
	    config.sug = torch.Tensor():typeAs(w):resizeAs(w):fill(0)
	    pc:reset(config.suw,config.sug)
	 end
	 pc:async_recv_param() -- suw=w*
	 local synctime = sys.clock()
	 pc:wait() -- sug is sent and suw is recv
	 state.dusync = state.dusync + sys.clock()-synctime
	 config.sug:copy(w) -- sug=w
	 config.sug:add(-1,config.suw) -- sug=w-w*
	 config.sug:mul(mva) -- sug=mva*(w-w*)
	 pc:async_send_grad() -- apply w*=w*+mva*(w-w*)
	 local synctime = sys.clock()
	 pc:ping() -- overlap aio and computation
	 state.dusync = state.dusync + sys.clock()-synctime
	 localupdate()
	 w:add(-1,config.sug) -- w=w+mva*(w*-w)
      else
	 localupdate()
      end
   else
      assert(false)
   end
   return w,{fx}
end
