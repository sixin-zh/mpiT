-- ADADELTA
-- For single worker only
-- Author: Minwei Feng (mfeng@us.ibm.com)
require 'optim'

function optim.adadeltasingle(opfunc, w, config, state)
  local config = config or {}
  local state = state or config
  local rho = config.rho or 0.9
  local epsilon = config.epsilon or 1e-6
  local pc = config.pclient or nil
  local lr = config.lr
  state.pversion = state.pversion or 0

  local fx,dfdx = opfunc(w)

  if not state.paramVariance then
    state.paramVariance = torch.Tensor():typeAs(w):resizeAs(dfdx):zero()
    state.paramStd = torch.Tensor():typeAs(w):resizeAs(dfdx):zero()
    state.delta = torch.Tensor():typeAs(w):resizeAs(dfdx):zero()
    state.accDelta = torch.Tensor():typeAs(w):resizeAs(dfdx):zero()
  end
  state.paramVariance:mul(rho):addcmul(1-rho,dfdx,dfdx)
  state.paramStd:resizeAs(state.paramVariance):copy(state.paramVariance):add(epsilon):sqrt()
  state.delta:resizeAs(state.paramVariance):copy(state.accDelta):add(epsilon):sqrt():cdiv(state.paramStd):cmul(dfdx)
  w:add(-lr, state.delta)
  state.accDelta:mul(rho):addcmul(1-rho, state.delta, state.delta)


  state.pversion = state.pversion + 1
  -- send
  pc:async_send_param()
  pc:wait()
  return w,{fx}
end
