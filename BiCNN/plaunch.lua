require 'mpiT'
dofile('init.lua')

cmd = torch.CmdLine('_')
cmd:text()
cmd:text('Options:')
cmd:option('-threads', 1, 'number of threads')
cmd:option('-optimization', 'downpour', 'optimization method: sgd | downpour | eamsgd')
cmd:option('-learningRate', 1e-2, 'learning rate at t=0')
cmd:option('-batchSize', 1, 'mini-batch size (1 = pure stochastic)')
cmd:option('-weightDecay', 0.000001, 'weight decay')
cmd:option('-momentum', 0, 'momentum (SGD only)')
cmd:option('-commperiod' , 1, ' sync updates')
cmd:option('-movingrate' , 0.05, 'moving rate')
cmd:option('-type', 'float', 'type: double | float | cuda')
cmd:option('-trainFile', 'release/Question_answerlabels.train.ibmprep.ibminput', 'input training file')
cmd:option('-validFile', 'release/Question_answerlabels.dev.ibmprep.ibminput', 'input validation file')
cmd:option('-testFile1', 'release/Question_answerlabels.test1.ibmprep.ibminput', 'input test file 1')
cmd:option('-testFile2', 'release/Question_answerlabels.test2.ibmprep.ibminput', 'input test file 2')
cmd:option('-label2answFile', 'release/label2answers.ibmprep', 'preprocessed lable2answers file')
cmd:option('-embeddingFile', 'release/filtered.wordvec.vecs100.txt', 'input embedding file')
cmd:option('-embeddingDim', 100, 'input word embedding dimension')
cmd:option('-contConvWidth', 2, 'continuous convolution filter width')
cmd:option('-wordHiddenDim', 200, 'first hidden layer output dimension')
cmd:option('-numFilters', 3000, 'CNN filters amount')
cmd:option('-epoch', 50, 'maximum epoch')
cmd:option('-L1reg', 0, 'L1 regularization coefficient')
cmd:option('-L2reg', 1e-4, 'L2 regularization coefficient')
cmd:option('-margin', 0.02, 'margin for hinge loss')
cmd:option('-maxnegsample', 100, 'maximum sampling times for negative examples')
cmd:option('-validMode', 'lastClient', 'validation type: none | lastClient| additionalTester')
cmd:option('-validSleepTime', 0, 'validation sleep time, only for additionalTester')
cmd:option('-servRecvgrad', true, 'server recvgrad')
cmd:option('-servSendparam', true, 'server send param to workers')
cmd:option('-mmode', 1, '1|2')
cmd:option('-outputprefix', 'none', 'output file prefix')
cmd:option('-prevtime', 0, 'time start point')
cmd:option('-loadmodel', 'none', 'load model file name')
cmd:text()
opt = cmd:parse(arg or {})

-- opt.rank = conf.rank
local oncuda 
if opt.type == 'cuda' then
    oncuda = true
    require 'cutorch'
    require 'cunn'
else
    oncuda = false
    require 'nn'
    require 'nngraph'
end

local AGPU = {1,2} -- ,3,4,5,6,7,8}

mpiT.Init()
local world = mpiT.COMM_WORLD
local rank = mpiT.get_rank(world)
local size = mpiT.get_size(world)
local gpu = nil
if rank == 1 then
  print(opt)
end
conf = {}
conf.lr = opt.learningRate
conf.rank = rank
conf.size = size
conf.world = world
conf.sranks = {}
conf.cranks = {}
conf.tranks = {}
conf.oncuda = oncuda
conf.opt = opt

-- set random seed by rank
torch.manualSeed(rank)
math.randomseed(rank)

local lastWorker = size - 1
if opt.validMode == 'additionalTester' then
   -- if size % 2 ~= 1 then
   --   error("size must be an odd number")
   -- end
    lastWorker = size - 2
end


-- notice the rank starts from 0
for i = 0,lastWorker do
   if math.fmod(i,2)==0 then
      table.insert(conf.sranks,i)
   else
      table.insert(conf.cranks,i)
   end
end

if opt.validMode == 'lastClient' then
    conf.tranks[size-1] = true
elseif opt.validMode == 'additionalTester' then
    conf.tranks[size-1] = true
end

if math.fmod(rank, 2)==0 and rank <= lastWorker then
   -- server   
--   if oncuda and true then
--      require 'cunn'
--      local gpus = cutorch.getDeviceCount()
--      gpu = AGPU[(rank%(size/2)) % gpus + 1]
--      cutorch.setDevice(gpu)
--      print('[server] rank',rank,'use gpu',gpu)
--      torch.setdefaulttensortype('torch.CudaTensor')
--   else
    print('[server] rank ' .. rank .. ' use cpu on ' .. io.popen('hostname -s'):read())
    torch.setdefaulttensortype('torch.FloatTensor')
--   end
    local ps = pServer(conf)
    ps:start()
else
   if oncuda then
      local gpus = cutorch.getDeviceCount()
      gpu = AGPU[(rank%(size/2)) % gpus + 1]
      cutorch.setDevice(gpu)
      print('[client] rank',rank,'use gpu',gpu)
      torch.setdefaulttensortype('torch.CudaTensor')
   else
      print('[client] rank ' .. rank .. ' use cpu on ' .. io.popen('hostname -s'):read())
      torch.setdefaulttensortype('torch.FloatTensor')
   end

   mapWordStr2VectorStr = {}
   mapWordIdx2Vector = {}
   mapWordStr2WordIdx = {}
   mapWordIdx2WordStr = {}
   mapLabel2AnswerIdx = {}
   trainDataSet = {}
   validDataSet = {}
   testDataSet1 = {}
   testDataSet2 = {}

   -- pclient   
   pc = pClient(conf)
   -- go
   dofile('prepareData.lua')
   dofile('bicnn.lua')
end

mpiT.Finalize()
