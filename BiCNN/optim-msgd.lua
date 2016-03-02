-- MSGD
-- Nesterov's momentum, see e.g. Sutskever et al., ICML 2013
-- Author: Sixin Zhang (zsx@cims.nyu.edu)
require 'optim'

function optim.msgd(opfunc, w, config, state)
  local config = config or {}
  local state = state or config

  local lr = config.lr or 0
  local lrd = config.lrd or 0
  local lrp = config.lrp or 0
  local mom = config.mom or 0
  local mmax = config.mommax or 1
  local mlrd = config.momdecay or 0
  local l2wd = config.l2wd or 0

  local pc = config.pclient or nil
  state.pversion = state.pversion or 0


  if lrd ~= 0 then 
      lr = lr / (1 + state.pversion*lrd)
  end
  if mom > 0 then
    if mlrd > 0 then
      mom = math.min(mmax, 1-0.5/(1+state.pversion/mlrd))
    end
    if not state.vt then
      state.vt = w:clone():zero()
    end
    state.vt:mul(mom)
    w:add(state.vt)
  end
  local fx,dfdx = opfunc(w)
  if l2wd ~= 0 then dfdx:add(l2wd,w) end
  local clr = lr
  if lrd > 0 and lrp > 0 then
    clr = lr / math.pow(1+state.pversion*lrd,lrp)
  end
  w:add(-clr,dfdx)
  if mom > 0 then
    state.vt:add(-clr,dfdx)
  end
  state.pversion = state.pversion + 1
  -- send
  pc:async_send_param()
  pc:wait()
  return w,{fx}
end
