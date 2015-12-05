--  BiCNN Train and Testing
-- Author: Minwei Feng (mfeng@us.ibm.com)

dofile('utils.lua')

local opt = opt or {}
local state = {}
local conf = conf or {}
local twoone = torch.ones(2)
if opt.validMode == 'additionalTester' and conf.tranks[conf.rank] == true then
  print('Client ' .. tostring(conf.rank) ..' ready to run testing')
else
  print('Client ' .. tostring(conf.rank) ..' ready to run training')
end

require 'sys'
tm = {}
tm.sync = 0
tm.fprop = 0
tm.transfer = 0
tm.feval = 0
tm.bprop = 0
tm.cbprop = 0
tm.err = 0
tm.conf = 0
tm.params = 0
tm.loss = 0
tm.test = 0
-------------------------------------------------------------------
LookupTable_Q = nn.LookupTable(#mapWordIdx2Vector, opt.embeddingDim)()
LookupTable_Q2 = nn.LookupTable(#mapWordIdx2Vector, opt.embeddingDim)()
LookupTable_Apos = nn.LookupTable(#mapWordIdx2Vector, opt.embeddingDim)()
LookupTable_Aneg = nn.LookupTable(#mapWordIdx2Vector, opt.embeddingDim)()
LookupTable_Q.data.module.weight:set(torch.Tensor(mapWordIdx2Vector))
LookupTable_Q2.data.module.weight:set(LookupTable_Q.data.module.weight)
LookupTable_Apos.data.module.weight:set(LookupTable_Q.data.module.weight)
LookupTable_Aneg.data.module.weight:set(LookupTable_Q.data.module.weight)
LookupTable_Q2.data.module.gradWeight:set(LookupTable_Q.data.module.gradWeight)
LookupTable_Apos.data.module.gradWeight:set(LookupTable_Q.data.module.gradWeight)
LookupTable_Aneg.data.module.gradWeight:set(LookupTable_Q.data.module.gradWeight)

WordHiddenLayer_Q = nn.Linear(opt.embeddingDim, opt.wordHiddenDim)(LookupTable_Q)
WordHiddenLayer_Q2 = nn.Linear(opt.embeddingDim, opt.wordHiddenDim)(LookupTable_Q2)
WordHiddenLayer_Apos = nn.Linear(opt.embeddingDim, opt.wordHiddenDim)(LookupTable_Apos)
WordHiddenLayer_Aneg = nn.Linear(opt.embeddingDim, opt.wordHiddenDim)(LookupTable_Aneg)
WordHiddenLayer_Q2.data.module.weight:set(WordHiddenLayer_Q.data.module.weight)
WordHiddenLayer_Apos.data.module.weight:set(WordHiddenLayer_Q.data.module.weight)
WordHiddenLayer_Aneg.data.module.weight:set(WordHiddenLayer_Q.data.module.weight)
WordHiddenLayer_Q2.data.module.bias:set(WordHiddenLayer_Q.data.module.bias)
WordHiddenLayer_Apos.data.module.bias:set(WordHiddenLayer_Q.data.module.bias)
WordHiddenLayer_Aneg.data.module.bias:set(WordHiddenLayer_Q.data.module.bias)
WordHiddenLayer_Q2.data.module.gradWeight:set(WordHiddenLayer_Q.data.module.gradWeight)
WordHiddenLayer_Apos.data.module.gradWeight:set(WordHiddenLayer_Q.data.module.gradWeight)
WordHiddenLayer_Aneg.data.module.gradWeight:set(WordHiddenLayer_Q.data.module.gradWeight)
WordHiddenLayer_Q2.data.module.gradBias:set(WordHiddenLayer_Q.data.module.gradBias)
WordHiddenLayer_Apos.data.module.gradBias:set(WordHiddenLayer_Q.data.module.gradBias)
WordHiddenLayer_Aneg.data.module.gradBias:set(WordHiddenLayer_Q.data.module.gradBias)

CNN_Q = nn.TemporalConvolution(opt.wordHiddenDim, opt.numFilters, opt.contConvWidth)(nn.Tanh()(WordHiddenLayer_Q))
CNN_Q2 = nn.TemporalConvolution(opt.wordHiddenDim, opt.numFilters, opt.contConvWidth)(nn.Tanh()(WordHiddenLayer_Q2))
CNN_Apos = nn.TemporalConvolution(opt.wordHiddenDim, opt.numFilters, opt.contConvWidth)(nn.Tanh()(WordHiddenLayer_Apos))
CNN_Aneg = nn.TemporalConvolution(opt.wordHiddenDim, opt.numFilters, opt.contConvWidth)(nn.Tanh()(WordHiddenLayer_Aneg))
CNN_Q2.data.module.weight:set(CNN_Q.data.module.weight)
CNN_Apos.data.module.weight:set(CNN_Q.data.module.weight)
CNN_Aneg.data.module.weight:set(CNN_Q.data.module.weight)
CNN_Q2.data.module.bias:set(CNN_Q.data.module.bias)
CNN_Apos.data.module.bias:set(CNN_Q.data.module.bias)
CNN_Aneg.data.module.bias:set(CNN_Q.data.module.bias)
CNN_Q2.data.module.gradWeight:set(CNN_Q.data.module.gradWeight)
CNN_Apos.data.module.gradWeight:set(CNN_Q.data.module.gradWeight)
CNN_Aneg.data.module.gradWeight:set(CNN_Q.data.module.gradWeight)
CNN_Q2.data.module.gradBias:set(CNN_Q.data.module.gradBias)
CNN_Apos.data.module.gradBias:set(CNN_Q.data.module.gradBias)
CNN_Aneg.data.module.gradBias:set(CNN_Q.data.module.gradBias)

MaxPool_Q = nn.Max(1)(CNN_Q)
MaxPool_Q2 = nn.Max(1)(CNN_Q2)
MaxPool_Apos = nn.Max(1)(CNN_Apos)
MaxPool_Aneg = nn.Max(1)(CNN_Aneg)

Embedding_Q = nn.Normalize(2)(nn.ReLU()(MaxPool_Q))
Embedding_Q2 = nn.Normalize(2)(nn.ReLU()(MaxPool_Q2))
Embedding_Apos = nn.Normalize(2)(nn.ReLU()(MaxPool_Apos))
Embedding_Aneg = nn.Normalize(2)(nn.ReLU()(MaxPool_Aneg))


if opt.mmode == 1 then
  DotProduct_QApos = nn.DotProduct()({Embedding_Q, Embedding_Apos})
  DotProduct_QAneg = nn.DotProduct()({Embedding_Q, Embedding_Aneg})
  L2_QApos = nn.PairwiseDistance(2)({Embedding_Q, Embedding_Apos})
  L2_QAneg = nn.PairwiseDistance(2)({Embedding_Q, Embedding_Aneg})
else
  DotProduct_QApos = nn.DotProduct()({Embedding_Q, Embedding_Apos})
  DotProduct_QAneg = nn.DotProduct()({Embedding_Q2, Embedding_Aneg})
  L2_QApos = nn.PairwiseDistance(2)({Embedding_Q, Embedding_Apos})
  L2_QAneg = nn.PairwiseDistance(2)({Embedding_Q2, Embedding_Aneg})
end
require 'DivideConstant'
simi1_QApos = nn.DivideConstant(1)(nn.AddConstant(1)(L2_QApos))
simi1_QAneg = nn.DivideConstant(1)(nn.AddConstant(1)(L2_QAneg))
simi2_QApos = nn.DivideConstant(1)(nn.AddConstant(1)(nn.Exp()(nn.MulConstant(-1)(nn.AddConstant(1)(DotProduct_QApos)))))
simi2_QAneg = nn.DivideConstant(1)(nn.AddConstant(1)(nn.Exp()(nn.MulConstant(-1)(nn.AddConstant(1)(DotProduct_QAneg)))))

GESD_QApos = nn.CMulTable()({simi1_QApos, simi2_QApos}) 
GESD_QAneg = nn.CMulTable()({simi1_QAneg, simi2_QAneg})

model = nil
local model_QApos
local model_QAneg
local model_test
if opt.mmode == 1 then
    model = nn.gModule({LookupTable_Q, LookupTable_Apos, LookupTable_Aneg}, {GESD_QApos, GESD_QAneg})
else
    model_QApos = nn.gModule({LookupTable_Q, LookupTable_Apos}, {GESD_QApos})
    model_QAneg = nn.gModule({LookupTable_Q2, LookupTable_Aneg}, {GESD_QAneg})
end

--model_test = nn.gModule({LookupTable_QATest}, {Embedding_QATest})


local criterion = nn.MarginRankingCriterion(opt.margin)



-------------------------------------------------------------------
require 'optim'
local opti
if opt.optimization == 'sgd' then
   opti = optim.msgd
   state.optconf = {
      lr = opt.learningRate,
      lrd = opt.weightDecay,
      mommax = opt.momentum,      
   }
elseif opt.optimization == 'downpour' then
   opti = optim.downpour
   state.optconf = {
      lr = opt.learningRate,
      lrd = opt.weightDecay,
      pclient = pc,
      su = opt.commperiod,      
   }
elseif opt.optimization == 'eamsgd' then
   opti = optim.eamsgd
   state.optconf = {
      lr = opt.learningRate,
      lrd = opt.weightDecay,
      pclient = pc,
      su = opt.commperiod,
      mva = opt.movingrate,
      mom = opt.momentum,
   }
elseif opt.optimization == 'rmsprop' then
   opti = optim.rmsprop
   state.optconf = {
      mode = opt.modeRMSProp,
      decay = opt.decayRMSProp,
      lr = opt.lrRMSProp,
      momentum = opt.momentumRMSProp,
      epsilon = opt.epsilonRMSProp,
      pclient = pc,
      su = opt.commperiod      
   }
elseif opt.optimization == 'adam' then
   opti = optim.adam
   state.optconf = {
      mode = opt.modeAdam,
      lr = opt.lrAdam,
      beta1 = opt.beta1Adam,
      beta2 = opt.beta2Adam,
      epsilon = opt.epsilonAdam,
      pclient = pc,
      su = opt.commperiod      
   }
else
   os.error('unknown optimization method')
end

if opt.mmode == 1 then
    parameters,gradParameters = model:getParameters()
else
    parameters,gradParameters = model_QApos:getParameters()
end
if opt.loadmodel ~= 'none' then
    parameters:copy(torch.load(opt.loadmodel))
end
parametersClone = parameters:clone()
local classes = {'1','2','3','4','5','6','7','8','9','0'}
local confusion = optim.ConfusionMatrix(classes)

-------------------------------------------------------------------
local pclient = pc
if pclient then
   pclient:start(parameters,gradParameters)
   --print(opt.rank, 'pclient started', pclient.rank)
end
-------------------------------------------------------------------
local inputs_Q = nil
local inputs_Apos = nil
local targets = nil
local answ_space_size = #mapLabel2AnswerIdx
local loss = 0
local loss_times = 0
local feval = 
function(x)
   local time_feval = sys.clock()
   local time_params = sys.clock()
   
   -- get new parameters    
   if x ~= parameters then
      print('copy parameters!!')
      parameters:copy(x)
   end
   
   -- reset gradients
   gradParameters:zero()
   tm.params = tm.params + sys.clock() - time_params

   local f = 0
   for i = 1,#inputs_Q do
       local time_transfer = sys.clock()
       if opt.device then
           inputs_Q[i] = inputs_Q[i]:cuda()
           inputs_Apos[i] = inputs_Apos[i]:cuda()
           targets[i] = targets[i]:cuda()
       end
       tm.transfer = tm.transfer + (sys.clock() - time_transfer)

       --local time_fprop = sys.clock()
       local ansset = {}
       local neg = torch.Tensor(1)
       local sample = 0
       for s=1,targets[i]:storage():size() do
           ansset[targets[i][s]] = true
       end
       local output
       local out_QApos = nil
       local out_QAneg = nil
       local inputs_Aneg
       if opt.mmode ~= 1 then 
         out_QApos = model_QApos:updateOutput({inputs_Q[i], inputs_Apos[i]})
       end
       local simi_QApos = nil
       local simi_QAneg = nil
       local rerun = nil
       while true do
           if sample + 1 > opt.maxnegsample then
               break
           end

           while true do
               neg:random(1,answ_space_size)
               if ansset[neg[1]] == nil then
                   break
               end
           end
           sample = sample + 1
           inputs_Aneg = mapLabel2AnswerIdx[neg[1]]
           if opt.mmode == 1 then
               if simi_QApos == nil then
                 output = model:updateOutput({inputs_Q[i], inputs_Apos[i], inputs_Aneg})
                 simi_QApos = output[1][1]
                 simi_QAneg = output[2][1]
               else
                 output = model:updateOutput({inputs_Q[i], torch.ones(2), inputs_Aneg})
                 simi_QAneg = output[2][1]
                 rerun = true
               end
           else
               out_QAneg = model_QAneg:updateOutput({inputs_Q[i],  inputs_Aneg})
           end
           
           if opt.mmode == 1 then
           --    print("mode1", output[1][1], output[2][1])
               if simi_QApos - simi_QAneg < opt.margin then
                  break
               end
           else
            --   print("mode2",out_QApos[1], out_QAneg[1])
               if out_QApos[1] - out_QAneg[1] < opt.margin then
                   break
               end
           end
       end

       if opt.mmode == 1 then
          if simi_QApos - simi_QAneg >= opt.margin then
          --   print("goto", output[1][1], output[2][1])
             goto continue
          elseif rerun then
             output = model:updateOutput({inputs_Q[i], inputs_Apos[i], inputs_Aneg})
          end
       end
       if opt.mmode ~= 1 then
          if out_QApos[1] - out_QAneg[1] >= opt.margin then
          --  print("goto", out_QApos[1], out_QAneg[1])
            goto continue 
          end
       end
       --tm.fprop = tm.fprop + (sys.clock() - time_fprop)
       local currErr
       if opt.mmode == 1 then
           currErr = criterion:forward(output, 1)
       else
           currErr = criterion:forward({out_QApos, out_QAneg}, 1)
       end
       --print(currErr)
       local gradCriterion
       if opt.mmode == 1 then
           gradCriterion = criterion:backward(output, 1)
           model:updateGradInput({inputs_Q[i], inputs_Apos[i], inputs_Aneg}, gradCriterion)
           model:accGradParameters({inputs_Q[i], inputs_Apos[i], inputs_Aneg}, gradCriterion)          
       else
           gradCriterion = criterion:backward({out_QApos,out_QAneg}, 1)
           model_QApos:updateGradInput({inputs_Q[i], inputs_Apos[i]}, gradCriterion[1])
           model_QApos:accGradParameters({inputs_Q[i], inputs_Apos[i]}, gradCriterion[1])
           model_QAneg:updateGradInput({inputs_Q[i], inputs_Aneg}, gradCriterion[2])
           model_QAneg:accGradParameters({inputs_Q[i], inputs_Aneg}, gradCriterion[2])
       end
       --print(gradCriterion[1], gradCriterion[2])

       f = f + currErr
       if opt.L1reg ~= 0 then
           local norm, sign = torch.norm, torch.sign
           f = f + opt.L1reg * norm(parameters,1)
           gradParameters:add( sign(parameters):mul(opt.L1reg) )
       end
       if opt.L2reg ~= 0 then
           local norm, sign = torch.norm, torch.sign
           f = f + opt.L2reg * norm(parameters,2)^2/2
           parametersClone:copy(parameters)
           gradParameters:add( parametersClone:mul(opt.L2reg) )
       end
       gradParameters:clamp(-opt.gradClip, opt.gradClip)
       ::continue::
   end
   loss = loss + f
   loss_times = loss_times + 1
   if loss_times % 2000 == 0 then
     print(string.format("Client %s: curr time: %.2f, training loss avg. : %.5f ", conf.rank, sys.toc()+opt.prevtime,  loss/loss_times))
     loss = 0
     loss_times = 0
   end
   return f,gradParameters
end

local test = function(inputDataSet)
    local time_test = sys.clock()
    model:evaluate()
    local mapLabel2AnswerEmbedding={}
    for idx = 1,answ_space_size do
        model:updateOutput({twoone, mapLabel2AnswerIdx[idx], twoone})
        mapLabel2AnswerEmbedding[idx] = Embedding_Apos.data.module.output:resize(opt.numFilters):clone()
    end
    local correct = 0
    for t = 1,#inputDataSet do
        local input = torch.Tensor(inputDataSet[t][2])
        local target = inputDataSet[t][1]
        local pool = inputDataSet[t][3]
        model:updateOutput({input, twoone, twoone})
        local qvec = Embedding_Q.data.module.output:resize(opt.numFilters)
        local most_simi = -1
        local most_simi_label = 0
        for k,v in ipairs(pool) do
            local dd = torch.dot(qvec, mapLabel2AnswerEmbedding[v])
            local l2 = torch.dist(qvec, mapLabel2AnswerEmbedding[v])
            local simi = (1 /  ((1+l2) * (1 + math.exp(-(dd + 1))))  )
            if simi >= most_simi then
              most_simi = simi
              most_simi_label = v 
            end 
        end

        for k,v in ipairs(target) do
            if most_simi_label == v then
                correct = correct + 1
                break
            end
        end
    end
    bestAccuracy = bestAccuracy or 0
    bestEpoch = bestEpoch or 0
    local currAccuracy = correct/(#inputDataSet)
    if currAccuracy > bestAccuracy then bestAccuracy = currAccuracy; bestEpoch = epoch end
    print(string.format("Client %s: curr time: %s, Accuracy: %s, best Accuracy: %s ", conf.rank, sys.toc(),  currAccuracy, bestAccuracy))
    tm.test = tm.test + (sys.clock() - time_test)
end


local test3 = function(inputDataSet1, inputDataSet2, inputDataSet3)
    model:evaluate()
    local mapLabel2AnswerEmbedding={}
    for idx = 1,answ_space_size do
        model:updateOutput({twoone, mapLabel2AnswerIdx[idx], twoone})
        mapLabel2AnswerEmbedding[idx] = Embedding_Apos.data.module.output:resize(opt.numFilters):clone()
    end
    local correct = 0
    bestAccuracy1 = bestAccuracy1 or 0
    bestEpoch1 = bestEpoch1 or 0
    local currAccuracy = 0
    for t = 1,#inputDataSet1 do
        local input = torch.Tensor(inputDataSet1[t][2])
        local target = inputDataSet1[t][1]
        local pool = inputDataSet1[t][3]
        model:updateOutput({input, twoone, twoone})
        local qvec = Embedding_Q.data.module.output:resize(opt.numFilters)
        local most_simi = -1
        local most_simi_label = 0
        for k,v in ipairs(pool) do
            local dd = torch.dot(qvec, mapLabel2AnswerEmbedding[v])
            local l2 = torch.dist(qvec, mapLabel2AnswerEmbedding[v])
            local simi = (1 /  ((1+l2) * (1 + math.exp(-(dd + 1))))  )
            if simi >= most_simi then
              most_simi = simi
              most_simi_label = v 
            end 
        end

        for k,v in ipairs(target) do
            if most_simi_label == v then
                correct = correct + 1
                break
            end
        end
    end
    currAccuracy = correct/(#inputDataSet1)
    if currAccuracy > bestAccuracy1 then bestAccuracy1 = currAccuracy; bestEpoch1 = epoch end
    print(string.format("Client %s: curr time: %.2f, Accuracy: %.4f, best Accuracy: %.4f on file1 ", conf.rank, sys.toc()+opt.prevtime,  currAccuracy, bestAccuracy1))

    correct = 0
    bestAccuracy2 = bestAccuracy2 or 0
    bestEpoch2 = bestEpoch2 or 0
    currAccuracy = 0
    for t = 1,#inputDataSet2 do
        local input = torch.Tensor(inputDataSet2[t][2])
        local target = inputDataSet2[t][1]
        local pool = inputDataSet2[t][3]
        model:updateOutput({input, twoone, twoone})
        local qvec = Embedding_Q.data.module.output:resize(opt.numFilters)
        local most_simi = -1
        local most_simi_label = 0
        for k,v in ipairs(pool) do
            local dd = torch.dot(qvec, mapLabel2AnswerEmbedding[v])
            local l2 = torch.dist(qvec, mapLabel2AnswerEmbedding[v])
            local simi = (1 /  ((1+l2) * (1 + math.exp(-(dd + 1))))  )
            if simi >= most_simi then
              most_simi = simi
              most_simi_label = v 
            end 
        end

        for k,v in ipairs(target) do
            if most_simi_label == v then
                correct = correct + 1
                break
            end
        end
    end
    currAccuracy = correct/(#inputDataSet2)
    if currAccuracy > bestAccuracy2 then bestAccuracy2 = currAccuracy; bestEpoch2 = epoch end
    print(string.format("Client %s: curr time: %.2f, Accuracy: %.4f, best Accuracy: %.4f on file2 ", conf.rank, sys.toc()+opt.prevtime,  currAccuracy, bestAccuracy2))


    correct = 0
    bestAccuracy3 = bestAccuracy3 or 0
    bestEpoch3 = bestEpoch3 or 0
    currAccuracy = 0
    for t = 1,#inputDataSet3 do
        local input = torch.Tensor(inputDataSet3[t][2])
        local target = inputDataSet3[t][1]
        local pool = inputDataSet3[t][3]
        model:updateOutput({input, twoone, twoone})
        local qvec = Embedding_Q.data.module.output:resize(opt.numFilters)
        local most_simi = -1
        local most_simi_label = 0
        for k,v in ipairs(pool) do
            local dd = torch.dot(qvec, mapLabel2AnswerEmbedding[v])
            local l2 = torch.dist(qvec, mapLabel2AnswerEmbedding[v])
            local simi = (1 /  ((1+l2) * (1 + math.exp(-(dd + 1))))  )
            if simi >= most_simi then
              most_simi = simi
              most_simi_label = v 
            end 
        end

        for k,v in ipairs(target) do
            if most_simi_label == v then
                correct = correct + 1
                break
            end
        end
    end
    currAccuracy = correct/(#inputDataSet3)
    if currAccuracy > bestAccuracy3 then bestAccuracy3 = currAccuracy; bestEpoch3 = epoch end
    print(string.format("Client %s: curr time: %.2f, Accuracy: %.4f, best Accuracy: %.4f on file3 ", conf.rank, sys.toc()+opt.prevtime,  currAccuracy, bestAccuracy3))
end


-- train
sys.tic()
avg_err = 0
iter = 0
pversion = 0

if opt.validMode == 'additionalTester' and conf.tranks[conf.rank] == true then
   -- only test, TODO to stop when the others stop
   while true do
      local comm_time_4test = sys.clock()
      print(string.format("Client %s: before receive", conf.rank))
      pclient:async_recv_param()
      pclient:wait()
      print(string.format("Client %s: communication time: %.2f ",
			  conf.rank, sys.clock() - comm_time_4test))
      test3(validDataSet, testDataSet1, testDataSet2)
      if opt.outputprefix ~= 'none' then
         torch.save(opt.outputprefix ..
            string.format("_%010.2f_model",
                sys.toc()+opt.prevtime), parameters)
      end
      sys.sleep(opt.validSleepTime)      
   end
else
   -- train
   for epoch = 1,opt.epoch do
      local time_epoch = sys.clock()
      if opt.mmode == 1 then
	 model:training()
      else
	 model_QApos:training()
	 model_QAneg:training()
      end
      shuffle = torch.randperm(#trainDataSet)
      local cost = 0
      for t = 1,#trainDataSet,opt.batchSize do
	 inputs_Q = {}
	 inputs_Apos = {}
	 targets = {}
	 local last = 0
	 if t+opt.batchSize-1 > #trainDataSet then
	    last = #trainDataSet
	 else
	    last = t+opt.batchSize-1
	 end
	 for ii=t,last,1 do
	    table.insert(inputs_Q, trainDataSet[shuffle[ii]][2])
	    table.insert(inputs_Apos, trainDataSet[shuffle[ii]][3])
	    table.insert(targets, trainDataSet[shuffle[ii]][1])
	 end
	 x,fx = opti(feval, parameters, state.optconf)
	 if opt.validMode == 'lastClient' and
	    conf.tranks[conf.rank] == true and
	    pversion%opt.commperiod==0 then
	    print("Client " .. conf.rank .. " will also run testing")
	    test3(validDataSet, testDataSet1, testDataSet2)
	    torch.save(opt.outputprefix ..
		       string.format("_%010.2f_model",
				     sys.toc()+opt.prevtime), parameters)  
	 end
	 pversion = pversion + 1
      end
      print('client ' .. conf.rank .. ':' .. ' epoch ' .. epoch .. ' done, '
	    .. ' for ' .. (sys.clock() - time_epoch) .. ' seconds ')
   end
end

print("Before Stop !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")
if pclient then
   pclient:stop()
end

if state.optconf.dusync then
   tm.sync = state.optconf.dusync
end

print(conf.rank, 'total training time', sys.toc())
print(conf.rank, 'factor time', tm)
