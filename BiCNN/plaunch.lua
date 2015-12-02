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
cmd:option('-decayRMSProp', 0.95, 'decay for rmsprop')
cmd:option('-lrRMSProp', 1e-4, 'learning rate for rmsprop')
cmd:option('-momentumRMSProp', 0.9, 'momentum for rmsprop')
cmd:option('-epsilonRMSProp', 1e-4, 'epsilon for rmsprop')
cmd:option('-modeRMSProp', 'global', 'mode for rmsprop')
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
cmd:option('-validMode', 'additionalTester', 'validation type: none | lastClient | additionalTester')
cmd:option('-validSleepTime', 1, 'validation sleep time in seconds, only for additionalTester')
cmd:option('-servRecvgrad', true, 'server recvgrad')
cmd:option('-servSendparam', true, 'server send param to workers')
cmd:option('-mmode', 1, '1|2')
cmd:option('-outputprefix', 'none', 'output file prefix')
cmd:option('-prevtime', 0, 'time start point')
cmd:option('-loadmodel', 'none', 'load model file name')
cmd:option('-preloadBinary', false, 'load data from binary files')
cmd:option('-testerfirst', false, 'rank 0 is the tester')
cmd:option('-testerlast', false, 'last rank is the tester')
cmd:option('-masterFreq', 2, 'this parameter control the ratio of master and client')
cmd:option('-maxrank', 120, 'max rank used')

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
size = opt.maxrank + 1
if rank > opt.maxrank then
  print('rank ' .. rank .. ' do nothing ')
  while true do
    sys.usleep(1000)
  end
end

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

if opt.validMode == 'additionalTester' then
   if size % 2 ~= 1 then
      error("validMode additionalTester requires size be an odd number")
   end
end

-- notice the rank starts from 0
local role = nil
if opt.testerfirst then
   table.insert(conf.cranks,0)
   if rank == 0 then
      role = 'pe'
   end
   for i = 1,size-1 do
      if math.fmod(i,opt.masterFreq) ~= 0 then
         table.insert(conf.cranks,i)
         if rank == i then
            role = 'pt'
         end
      else
         table.insert(conf.sranks,i)
         if rank == i then
            role = 'ps'
         end
      end
   end
end

if opt.testerlast then
   for i = 0,size-2 do
      if math.fmod(i+1,opt.masterFreq) ~= 0 then
         table.insert(conf.cranks,i)
         if rank == i then
            role = 'pt'
         end
      else
         table.insert(conf.sranks,i)
         if rank == i then
            role = 'ps'
         end
      end
   end
   table.insert(conf.cranks,size-1)
   if rank == size - 1 then
      role = 'pe'
   end
end


if opt.validMode == 'lastClient' then
    conf.tranks[size-1] = true
elseif opt.validMode == 'additionalTester' then
   -- set rank 0 as the additionalTester
    if opt.testerfirst then
       conf.tranks[0] = true
    elseif opt.testerlast then
       conf.tranks[size-1] = true
    else
       error("Incorrect configuration")
    end
end

if role == 'ps' then
   -- server   
--   if oncuda and true then
--      require 'cunn'
--      local gpus = cutorch.getDeviceCount()
--      gpu = AGPU[(rank%(size/2)) % gpus + 1]
--      cutorch.setDevice(gpu)
--      print('[server] rank',rank,'use gpu',gpu)
--      torch.setdefaulttensortype('torch.CudaTensor')
--   else
    --print('[server] rank ' .. rank .. ' use cpu on ' .. io.popen('hostname -s'):read())
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
      --print('[client] rank ' .. rank .. ' use cpu on ' .. io.popen('hostname -s'):read())
      torch.setdefaulttensortype('torch.FloatTensor')
   end

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
   if opt.preloadBinary == false then
      dofile('prepareData.lua')
   else
      mapWordIdx2Vector = torch.load("binary_mapWordIdx2Vector")
      mapWordStr2WordIdx = torch.load("binary_mapWordStr2WordIdx")
      mapWordIdx2WordStr = torch.load("binary_mapWordIdx2WordStr")
      mapLabel2AnswerIdx = torch.load("binary_mapLabel2AnswerIdx")
      trainDataSet = torch.load("binary_trainDataSet")
      validDataSet = torch.load("binary_validDataSet")
      testDataSet1 = torch.load("binary_testDataSet1")
      testDataSet2 = torch.load("binary_testDataSet2")
   end
   dofile('bicnn.lua')
end

mpiT.Finalize()
