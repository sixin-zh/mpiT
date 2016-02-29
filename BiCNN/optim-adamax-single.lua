-- Adamax
-- only for single worker
-- Author: Minwei Feng (mfeng@us.ibm.com)
require 'optim'

function optim.adamaxsingle(opfunc, w, config, state)
  local config = config or {}
  local state = state or config
  local lr = config.lr
  local beta1 = config.beta1
  local beta2 = config.beta2
  local epsilon = config.epsilon
  local pc = config.pclient or nil
  state.pversion = state.pversion or 0
  

  local fx,dfdx = opfunc(w)
  state.adamax_t = state.adamax_t or 0
  state.adamax_m = state.adamax_m or torch.Tensor():resizeAs(dfdx):zero()
  state.adamax_u = state.adamax_u or torch.Tensor():resizeAs(dfdx):zero()
  state.adamax_max = state.adamax_max or w.new(2, unpack(dfdx:size():totable())):zero()

  state.adamax_t = state.adamax_t + 1
  state.adamax_m:mul(beta1):add(1-beta1, dfdx)
  state.adamax_max[1]:copy(state.adamax_u):mul(beta2)
  state.adamax_max[2]:copy(dfdx):abs():add(epsilon)
  state.adamax_u:max(state.adamax_max, 1)

  local beta1_t = 1 - math.pow(beta1, state.adamax_t )
  local lr_t = lr /beta1_t
  w:addcdiv(-lr_t, state.adamax_m, state.adamax_u)

  state.pversion = state.pversion + 1
  -- send
  pc:async_send_param()
  pc:wait()
  return w,{fx}
end
