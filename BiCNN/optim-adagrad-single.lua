-- Adagrad
-- single worker only
-- Author: Minwei Feng (mfeng@us.ibm.com)
require 'optim'

function optim.adagradsingle(opfunc, w, config, state)
  local config = config or {}
  local state = state or config

  local lr = config.lr or 0
  local lrd = config.lrd or 0
  local pc = config.pclient or nil
  local epsilon = config.epsilon
  state.pversion = state.pversion or 0

  local clr = lr / (1 + state.pversion*lrd)

  local fx,dfdx = opfunc(w)

  if not state.paramVariance then
    state.paramVariance = torch.Tensor():typeAs(w):resizeAs(dfdx):zero()
    state.paramStd = torch.Tensor():typeAs(w):resizeAs(dfdx)
  end
  state.paramVariance:addcmul(1,dfdx,dfdx)
  state.paramStd:resizeAs(state.paramVariance):copy(state.paramVariance):sqrt()
  w:addcdiv(-clr, dfdx, state.paramStd:add(epsilon))

  state.pversion = state.pversion + 1
  -- send
  pc:async_send_param()
  pc:wait()
  return w,{fx}
end
