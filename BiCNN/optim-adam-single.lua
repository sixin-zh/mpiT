-- Adam
-- only for single worker
-- Author: Minwei Feng (mfeng@us.ibm.com)
require 'optim'

function optim.adamsingle(opfunc, w, config, state)
  local config = config or {}
  local state = state or config
  local lr = config.lr
  local beta1 = config.beta1
  local beta2 = config.beta2
  local epsilon = config.epsilon
  local pc = config.pclient or nil
  state.pversion = state.pversion or 0

  local fx,dfdx = opfunc(w)

  state.adam_t = state.adam_t or 0
  state.adam_m = state.adam_m or torch.Tensor():resizeAs(dfdx):zero()
  state.adam_v = state.adam_v or torch.Tensor():resizeAs(dfdx):zero()
  state.adam_d = state.adam_d or torch.Tensor():resizeAs(dfdx):zero()


  state.adam_t = state.adam_t + 1
  state.adam_m:mul(beta1):add(1-beta1, dfdx)
  state.adam_v:mul(beta2):addcmul(1-beta2, dfdx, dfdx)
  state.adam_d:copy(state.adam_v):sqrt():add(epsilon)
  local beta1_t = 1 - math.pow(beta1, state.adam_t )
  local beta2_t = 1 - math.pow(beta2, state.adam_t )
  local lr_t = lr * math.sqrt(beta2_t)/beta1_t
  w:addcdiv(-lr_t, state.adam_m, state.adam_d)

  state.pversion = state.pversion + 1
  -- send
  pc:async_send_param()
  pc:wait()
  return w,{fx}
end
