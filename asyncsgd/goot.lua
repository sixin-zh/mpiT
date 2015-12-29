-------------------------------------------------------------------
-- Author: Sixin Zhang (zsx@cims.nyu.edu)
-------------------------------------------------------------------
local opt = opt or {}
local state = state or {}
local optname = opt.name or 'sgd'
local lr = opt.lr or 1e-1
local mom = opt.mom or 0
local mb = opt.mb or 128
local mva = opt.mva or 0
local su = opt.su or 1
local maxep = opt.maxepoch or 100
local data_root = opt.data_root or
   io.popen('echo $HOME'):read() .. '/data/torch7/mnist10'
local gpuid = opt.gpuid or -1
local rank = opt.rank or -1
local pclient = opt.pc or nil
-------------------------------------------------------------------
require 'sys'
local tm = {}
tm.feval = 0
tm.sync = 0
-------------------------------------------------------------------
require 'os'
local seed = opt.seed or os.time()
torch.manualSeed(seed) -- remember to set cutorch.manualSeed if needed
-------------------------------------------------------------------
require 'nn'
local model = nn.Sequential()
model:add(nn.Linear(32*32,10))
--model:add(nn.Threshold()) -- relu
--model:add(nn.Dropout())
--model:add(nn.Linear(100,10))
model:add(nn.LogSoftMax())
criterion = nn.ClassNLLCriterion()
state.theta,state.grad = model:getParameters()
-------------------------------------------------------------------
-- data can be downloaded from,
-- http://cs.nyu.edu/~zsx/mnist10/test_32x32.th7
-- http://cs.nyu.edu/~zsx/mnist10/train_32x32.th7
-- remember to reset data_root
-- may use test_bin for fast debug
test_bin = data_root .. '/test_32x32.th7'
train_bin = data_root .. '/train_32x32.th7'
train_data = torch.load(train_bin)
test_data = torch.load(test_bin)
local dim = train_data['data']:size(2)*
            train_data['data']:size(3)*
	    train_data['data']:size(4)
local trsize = train_data['data']:size(1)
local ttsize = test_data['data']:size(1)
train_data.data:resize(trsize,dim)
test_data.data:resize(ttsize,dim)
train_data.data = train_data.data:float():div(255)
test_data.data = test_data.data:float():div(255)
train_data.labels = train_data.labels:float()
test_data.labels = test_data.labels:float()
if gpuid > 0 then
   train_data.data = train_data.data:cuda()
   train_data.labels = train_data.labels:cuda()
   test_data.data = test_data.data:cuda()
   test_data.labels = test_data.labels:cuda()
end
-------------------------------------------------------------------
require 'optim'
local opti
if optname == 'sgd' then
   opti = optim.msgd
   state.optim = {
      lr = lr,
      mommax = mom,      
   }
elseif optname == 'downpour' then
   opti = optim.downpour
   state.optim = {
      lr = lr,
      pclient = pclient,
      su = su,      
   }
elseif optname == 'eamsgd' then
   opti = optim.eamsgd
   state.optim = {
      lr = lr,
      pclient = pclient,
      su = su,
      mva = mva,
      mom = mom,
   }
end
-------------------------------------------------------------------
print('i am ' .. rank .. ' ready to run')
if pclient then
   pclient:start(state.theta,state.grad)
   assert(rank == pclient.rank)
   print('pc ' .. rank .. ' started')
end
-------------------------------------------------------------------
local inputs = nil
local targets = nil
local avg_err = 0
local feval = 
function(x)
   local time_feval = sys.clock()
   -- get new parameters    
   if x ~= state.theta then
      print('copy theta!!')
      state.theta:copy(x)
   end
   -- reset gradients
   state.grad:zero()
   -- forward
   local outputs = model:forward(inputs)
   local err = criterion:forward(outputs, targets)
   -- estimate df/dW
   local dE_do = criterion:backward(outputs, targets)
   model:backward(inputs, dE_do)
   local er
   if type(err) == 'number' then
      er = err -- for cpu
   else
      er = err[1]  -- for gpu
   end
   avg_err = avg_err + er
   tm.feval = tm.feval + (sys.clock() - time_feval)
   return er,state.grad
end

-- train
sys.tic()
local iter = 0
for epoch = 1,maxep do
   for t = 1,trsize,mb do
      -- prepare mini batch
      local mbs = math.min(trsize-t+1,mb)
      -- there's no shuffling in this cycling, just for illustration
      inputs = train_data.data:narrow(1,t,mbs)
      targets = train_data.labels:narrow(1,t,mbs)
      -- optimize on current mini-batch
      local x,fx
      x,fx = opti(feval, state.theta, state.optim)     
      -- increase iteration count
      iter = iter + 1
   end
   print(io.popen('hostname -s'):read(),sys.toc(),rank,
	 'avg_err at epoch ' .. epoch .. ' is ' .. avg_err / iter)
end

if pclient then
   pclient:stop()
end

print(rank,'total training time is', sys.toc())
print(rank,'total function eval time is', tm.feval)
if state.optim.dusync then
   tm.sync = state.optim.dusync
end
print(rank,'total sync time is', tm.sync)
