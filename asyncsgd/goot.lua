dofile('utils.lua')

if not opt then
   torch.setdefaulttensortype('torch.FloatTensor')
    opt = {}
    opt.lr = 1e-2
end

opt = opt or {}
opt.data_root = '/home/zsx/data/torch7/mnist10'

state = {}

opt.rank = opt.rank or -1
print(opt.rank, 'ready to run')

require 'sys'
tm = {}
tm.async = 0
tm.fprop = 0
tm.transfer = 0
tm.feval = 0
tm.bprop = 0
tm.cbprop = 0
tm.err = 0
tm.conf = 0
tm.params = 0

-------------------------------------------------------------------
require 'os'
local seed = opt.seed or os.time()
torch.manualSeed(seed)

-------------------------------------------------------------------
require 'nn'
local model = nn.Sequential()
model:add(nn.Linear(32*32,4096))
model:add(nn.Tanh())
model:add(nn.Linear(4096,4096))
model:add(nn.Tanh())
model:add(nn.Linear(4096,4096))
model:add(nn.Tanh())
model:add(nn.Linear(4096,10))
model:add(nn.LogSoftMax())
criterion = nn.ClassNLLCriterion()

-------------------------------------------------------------------
require 'optim'
local opti = optim.sgd
state.optim = {
   learningRate = 0, -- no need to do local gradient update
}

state.theta,state.grad = model:getParameters()
local classes = {'1','2','3','4','5','6','7','8','9','0'}
local confusion = optim.ConfusionMatrix(classes)

-------------------------------------------------------------------
--train_bin = '/home/zsx/data/torch7/mnist10/train_32x32.th7
test_bin = opt.data_root .. '/test_32x32.th7' -- can download it from http://cs.nyu.edu/~zsx/mnist10/test_32x32.th7
train_bin = test_bin
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

-------------------------------------------------------------------
local pclient = opt.pc
if pclient then
   pclient:start(state.theta,state.grad)
   print(opt.rank, 'pclient started', pclient.rank)
end

-------------------------------------------------------------------
local feval = 
function(x)
   local time_feval = sys.clock()
   local time_params = sys.clock()
   -- get new parameters    
   if x ~= state.theta then
      print('copy theta!!')
      state.theta:copy(x)
   end
   -- reset gradients
   state.grad:zero()
   tm.params = tm.params + sys.clock() - time_params
   -- use latest inputs
   local time_transfer = sys.clock()
   local inputs,targets
   -- clone or transfer to avoid overriding while preparing next 
   if opt.device then
      inputs = finputs:cuda()
      targets = ftargets:cuda()
   else
      inputs = finputs:float()
      targets = ftargets:float()
   end
   tm.transfer = tm.transfer + (sys.clock() - time_transfer)

   -- print(tinfo(finputs),tinfo(state.grad))

   -- forward
   local time_fprop = sys.clock()
   local outputs
   outputs = model:forward(inputs)
   tm.fprop = tm.fprop + (sys.clock() - time_fprop)

   --local time_loss = sys.clock()
   local err = criterion:forward(outputs, targets)
   --tm.loss = tm.loss + (sys.clock() - time_loss)

   -- estimate df/dW                                                                     
   local time_bprop = sys.clock()
   local time_cbprop = sys.clock()
   local dE_do = criterion:backward(outputs, targets)
   tm.cbprop = tm.cbprop + (sys.clock() - time_cbprop)
   model:backward(inputs, dE_do)
   tm.bprop = tm.bprop + (sys.clock() - time_bprop)

   local time_err = sys.clock()
   local er
   if type(err) == 'number' then er = err
   else er = err[1] end
   avg_err = avg_err + er
   tm.err = tm.err + sys.clock() - time_err

   local time_confusion = sys.clock()

   --print(tinfo(outputs),tinfo(targets))
   ---confusion:addbatch(outputs, targets)

   tm.conf = tm.conf + (sys.clock() - time_confusion)
   tm.feval = tm.feval + (sys.clock() - time_feval)

   -- print('pclient to async')
   if pclient then
      state.grad:mul(-opt.lr)
      local time_async = sys.clock()       
      pclient:async_send_grad()
      pclient:async_recv_param()
      pclient:wait()
      tm.async = tm.async + (sys.clock() - time_async)
   end

   return er,state.grad
end

-- train
sys.tic()
local mb = 128
avg_err = 0
iter = 0
for epoch = 1,1 do
   for t = 1,trsize,mb do
      -- prepare mini batch
      local mbs = math.min(trsize-t+1,mb)
      finputs = train_data.data:narrow(1,t,mbs)
      ftargets = train_data.labels:narrow(1,t,mbs)

      -- optimize on current mini-batch
      -- local time_train = sys.clock() 
      local x,fx
      x,fx = opti(feval, state.theta, state.optim)
      --tm.train = tm.train + (sys.clock() - time_train)
      
      -- increase iteration count
      iter = iter + 1

      print(opt.rank, iter, 'avg_err', avg_err / iter)
   end
end

print(opt.rank, 'training time', sys.toc())
print(opt.rank, 'factor time', tm)
