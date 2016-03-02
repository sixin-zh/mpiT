-- Adadelta
-- Author: Minwei Feng (mfeng@us.ibm.com)
require 'optim'

function optim.adadelta(opfunc, w, config, state)
  local config = config or {}
  local state = state or config
  local rho = config.rho or 0.9
  local epsilon = config.epsilon or 1e-6
  local mode = config.mode or 'global'  -- global or local
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
    end
  elseif pc and su==1 then
    if mode == 'global' then
      pc:async_send_grad()
      pc:async_recv_param()
      local synctime = sys.clock()
      pc:wait()
      state.dusync = state.dusync + sys.clock()-synctime
    end
  else
    assert(false)
  end
  state.pversion = state.pversion + 1
  return w,{fx}
end
