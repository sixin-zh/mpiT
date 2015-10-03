-- Data preparation for BiCNN
-- Author: Minwei Feng (mfeng@us.ibm.com)

require 'torch'
require 'nn'

if opt.trainFile ~= 'none' then
    trainFileHandle = assert(io.open(opt.trainFile, 'r'))
end
if opt.validFile ~= 'none' then
    validFileHandle = assert(io.open(opt.validFile, 'r'))
end
if opt.testFile1 ~= 'none' then
    testFile1Handle = assert(io.open(opt.testFile1, 'r'))
end
if opt.testFile2 ~= 'none' then
    testFile2Handle = assert(io.open(opt.testFile2, 'r'))
end
if opt.embeddingFile ~= 'none' then
    embeddingFileHandle = assert(io.open(opt.embeddingFile, 'r'))
end
if opt.label2answFile ~= 'none' then
    label2answFileHandle = assert(io.open(opt.label2answFile, 'r'))
end

function dictSize(T)
  local size = 0
  for k,v in pairs(T) do size = size + 1 end
  return size
end

local BUFSIZE = 2^13
local zeroEmbedding1 = {}
local zeroEmbedding2 = {}
local zeroEmbedding = {}
for i=1,opt.embeddingDim do zeroEmbedding1[i] = 0 ; zeroEmbedding2[i] = 0; zeroEmbedding[i] = 0; end
mapWordStr2WordIdx['SENTBEGIN'] = 1
mapWordStr2WordIdx['SENTEND'] = 2
mapWordIdx2Vector[1] = zeroEmbedding1
mapWordIdx2Vector[2] = zeroEmbedding2
mapWordIdx2WordStr[1] = 'SENTBEGIN'
mapWordIdx2WordStr[2] = 'SENTEND'

idx=3
while true do
    local lines, rest = embeddingFileHandle:read(BUFSIZE, '*line')
    if not lines then break end
    if rest then lines = lines .. rest .. '\n'  end
    local b = 0
    local e = 0
    while true do
        b = e + 1
        e = string.find(lines, '\n', b)
        if e == nil then break end
        local line = string.sub(lines, b, e-1)
        local k = string.sub(line, 1, string.find(line, '\t')-1 )
        local v = string.sub(line, string.find(line, '\t')+1, -1 )
        local temptable = {}
        for elem in string.gmatch(v, "%S+") do
            temptable[#temptable+1] = tonumber(elem)
        end
        mapWordStr2WordIdx[k] = idx
        mapWordIdx2WordStr[idx] = k
        mapWordIdx2Vector[idx] = temptable
        idx = idx + 1
    end
end

while true do
    local lines, rest = trainFileHandle:read(BUFSIZE, '*line')
    if not lines then break end
    if rest then lines = lines .. rest .. '\n'  end
    local b = 0
    local e = 0
    while true do
        b = e + 1
        e = string.find(lines, '\n', b)
        if e == nil then break end
        local line = string.sub(lines, b, e-1)
        local tab1 = string.find(line, '\t')
        local tab2 = string.find(line, '\t', tab1+1)
        local tab3 = string.find(line, '\t', tab2+1)
        local k = string.sub(line, 1, tab1-1 )
        local q = string.sub(line, tab2+1, tab3-1 )
        local a = string.sub(line, tab3+1, -1 )
        local tempL, tempQ, tempA = {}, {}, {}
        for elem in string.gmatch(k, "%S+") do
            tempL[#tempL+1] = tonumber(elem)
        end
        for i=1,opt.contConvWidth  do tempQ[#tempQ+1] = mapWordStr2WordIdx['SENTBEGIN']  ; end
        for w in string.gmatch(q, "%S+") do
            if mapWordStr2WordIdx[w] == nil then
                mapWordStr2WordIdx[w] = idx
                mapWordIdx2WordStr[idx] = w
                local oovEmbedding = {}
                for i=1,opt.embeddingDim do oovEmbedding[i] = math.random(); end
                mapWordIdx2Vector[idx] = oovEmbedding
                idx = idx + 1
            end
            tempQ[#tempQ+1] = mapWordStr2WordIdx[w]
        end
        for i=1,opt.contConvWidth-1  do tempQ[#tempQ+1] = mapWordStr2WordIdx['SENTEND']  ; end

        for i=1,opt.contConvWidth  do tempA[#tempA+1] = mapWordStr2WordIdx['SENTBEGIN']  ; end
        for w in string.gmatch(a, "%S+") do
            if mapWordStr2WordIdx[w] == nil then
                mapWordStr2WordIdx[w] = idx
                mapWordIdx2WordStr[idx] = w
                local oovEmbedding = {}
                for i=1,opt.embeddingDim do oovEmbedding[i] = math.random(); end
                mapWordIdx2Vector[idx] = oovEmbedding
                idx = idx + 1
            end
            tempA[#tempA+1] = mapWordStr2WordIdx[w]
        end
        for i=1,opt.contConvWidth-1  do tempA[#tempA+1] = mapWordStr2WordIdx['SENTEND']  ; end

        local tempL_T, tempQ_T, tempA_T
        if opt.type == 'double' then  tempL_T = torch.Tensor(tempL):double(); tempQ_T = torch.Tensor(tempQ):double(); tempA_T = torch.Tensor(tempA):double();
        elseif opt.type == 'cuda' then tempL_T = torch.Tensor(tempL):cuda();  tempQ_T = torch.Tensor(tempQ):cuda();   tempA_T = torch.Tensor(tempA):cuda();
        elseif opt.type == 'float' then tempL_T = torch.Tensor(tempL):float();tempQ_T = torch.Tensor(tempQ):float();  tempA_T = torch.Tensor(tempA):float(); end
        table.insert(trainDataSet, {tempL_T, tempQ_T, tempA_T})
    end
end


while true do
    local lines, rest = validFileHandle:read(BUFSIZE, '*line')
    if not lines then break end
    if rest then lines = lines .. rest .. '\n'  end
    local b = 0
    local e = 0
    while true do
        b = e + 1
        e = string.find(lines, '\n', b)
        if e == nil then break end
        local line = string.sub(lines, b, e-1)
        local tab1 = string.find(line, '\t')
        local tab2 = string.find(line, '\t', tab1+1)
        local k = string.sub(line, 1, tab1-1 )
        local q = string.sub(line, tab1+1, tab2-1 )
        local a = string.sub(line, tab2+1, -1 )
        local tempL, tempQ, tempPool = {}, {}, {}
        for elem in string.gmatch(k, "%S+") do
            tempL[#tempL+1] = tonumber(elem)
        end
        for i=1,opt.contConvWidth  do tempQ[#tempQ+1] = mapWordStr2WordIdx['SENTBEGIN']  ; end
        for w in string.gmatch(q, "%S+") do
            if mapWordStr2WordIdx[w] == nil then
                mapWordStr2WordIdx[w] = idx
                mapWordIdx2WordStr[idx] = w
                local oovEmbedding = {}
                for i=1,opt.embeddingDim do oovEmbedding[i] = math.random(); end
                mapWordIdx2Vector[idx] = oovEmbedding
                idx = idx + 1
            end
            tempQ[#tempQ+1] = mapWordStr2WordIdx[w]
        end
        for i=1,opt.contConvWidth-1  do tempQ[#tempQ+1] = mapWordStr2WordIdx['SENTEND']  ; end
        for w in string.gmatch(a, "%S+") do --answer pool
            tempPool[#tempPool+1] = tonumber(w)
        end
        table.insert(validDataSet, {tempL, tempQ, tempPool})
    end
end

while true do
    local lines, rest = testFile1Handle:read(BUFSIZE, '*line')
    if not lines then break end
    if rest then lines = lines .. rest .. '\n'  end
    local b = 0
    local e = 0
    while true do
        b = e + 1
        e = string.find(lines, '\n', b)
        if e == nil then break end
        local line = string.sub(lines, b, e-1)
        local tab1 = string.find(line, '\t')
        local tab2 = string.find(line, '\t', tab1+1)
        local k = string.sub(line, 1, tab1-1 )
        local q = string.sub(line, tab1+1, tab2-1 )
        local a = string.sub(line, tab2+1, -1 )
        local tempL, tempQ, tempPool = {}, {}, {}
        for elem in string.gmatch(k, "%S+") do
            tempL[#tempL+1] = tonumber(elem)
        end
        for i=1,opt.contConvWidth  do tempQ[#tempQ+1] = mapWordStr2WordIdx['SENTBEGIN']  ; end
        for w in string.gmatch(q, "%S+") do
            if mapWordStr2WordIdx[w] == nil then
                mapWordStr2WordIdx[w] = idx
                mapWordIdx2WordStr[idx] = w
                local oovEmbedding = {}
                for i=1,opt.embeddingDim do oovEmbedding[i] = math.random(); end
                mapWordIdx2Vector[idx] = oovEmbedding
                idx = idx + 1
            end
            tempQ[#tempQ+1] = mapWordStr2WordIdx[w]
        end
        for i=1,opt.contConvWidth-1  do tempQ[#tempQ+1] = mapWordStr2WordIdx['SENTEND']  ; end
        for w in string.gmatch(a, "%S+") do
            tempPool[#tempPool+1] = tonumber(w)
        end
        table.insert(testDataSet1, {tempL, tempQ, tempPool})
    end
end

while true do
    local lines, rest = testFile2Handle:read(BUFSIZE, '*line')
    if not lines then break end
    if rest then lines = lines .. rest .. '\n'  end
    local b = 0
    local e = 0
    while true do
        b = e + 1
        e = string.find(lines, '\n', b)
        if e == nil then break end
        local line = string.sub(lines, b, e-1)
        local tab1 = string.find(line, '\t')
        local tab2 = string.find(line, '\t', tab1+1)
        local k = string.sub(line, 1, tab1-1 )
        local q = string.sub(line, tab1+1, tab2-1 )
        local a = string.sub(line, tab2+1, -1 )
        local tempL, tempQ, tempPool = {}, {}, {}
        for elem in string.gmatch(k, "%S+") do
            tempL[#tempL+1] = tonumber(elem)
        end
        for i=1,opt.contConvWidth  do tempQ[#tempQ+1] = mapWordStr2WordIdx['SENTBEGIN']  ; end
        for w in string.gmatch(q, "%S+") do
            if mapWordStr2WordIdx[w] == nil then
                mapWordStr2WordIdx[w] = idx
                mapWordIdx2WordStr[idx] = w
                local oovEmbedding = {}
                for i=1,opt.embeddingDim do oovEmbedding[i] = math.random(); end
                mapWordIdx2Vector[idx] = oovEmbedding
                idx = idx + 1
            end
            tempQ[#tempQ+1] = mapWordStr2WordIdx[w]
        end
        for i=1,opt.contConvWidth-1  do tempQ[#tempQ+1] = mapWordStr2WordIdx['SENTEND']  ; end
        for w in string.gmatch(a, "%S+") do
            tempPool[#tempPool+1] = tonumber(w)
        end
        table.insert(testDataSet2, {tempL, tempQ, tempPool})
    end
end

while true do
    local lines, rest = label2answFileHandle:read(BUFSIZE, '*line')
    if not lines then break end
    if rest then lines = lines .. rest .. '\n'  end
    local b = 0
    local e = 0
    while true do
        b = e + 1
        e = string.find(lines, '\n', b)
        if e == nil then break end
        local line = string.sub(lines, b, e-1)
        local tab1 = string.find(line, '\t')
        local k = string.sub(line, 1, tab1-1 )
        local a = string.sub(line, tab1+1, -1 )
        local tempL, tempA = {}, {}
        for elem in string.gmatch(k, "%S+") do
            tempL[#tempL+1] = tonumber(elem)
        end
        for i=1,opt.contConvWidth  do tempA[#tempA+1] = mapWordStr2WordIdx['SENTBEGIN']  ; end
        for w in string.gmatch(a, "%S+") do
            if mapWordStr2WordIdx[w] == nil then
                mapWordStr2WordIdx[w] = idx
                mapWordIdx2WordStr[idx] = w
                local oovEmbedding = {}
                for i=1,opt.embeddingDim do oovEmbedding[i] = math.random(); end
                mapWordIdx2Vector[idx] = oovEmbedding
                idx = idx + 1
            end
            tempA[#tempA+1] = mapWordStr2WordIdx[w]
        end
        for i=1,opt.contConvWidth-1  do tempA[#tempA+1] = mapWordStr2WordIdx['SENTEND']  ; end
    --    mapLabel2AnswerIdx[tempL[1]] = tempA
        if opt.type == 'double' then  mapLabel2AnswerIdx[tempL[1]] = torch.Tensor(tempA):double(); 
        elseif opt.type == 'cuda' then mapLabel2AnswerIdx[tempL[1]] = torch.Tensor(tempA):cuda();
        elseif opt.type == 'float' then mapLabel2AnswerIdx[tempL[1]] = torch.Tensor(tempA):float();  end
    end
end

--print(string.format('training data size: %s', #trainDataSet))
--print(string.format('valid data size: %s', #validDataSet))
--print(string.format('test data size: %s', #testDataSet1))
--print(string.format('test data size: %s', #testDataSet2))
--print(string.format('mapWordStr2WordIdx size: %s', dictSize(mapWordStr2WordIdx)))
--print(string.format('mapWordIdx2WordStr size: %s', #mapWordIdx2WordStr))
--print(string.format('mapWordIdx2Vector size: %s', #mapWordIdx2Vector))
--print(string.format('mapLabel2AnswerIdx size: %s', #mapLabel2AnswerIdx))
assert(trainFileHandle:close())
assert(validFileHandle:close())
assert(testFile1Handle:close())
assert(testFile2Handle:close())
assert(label2answFileHandle:close())
assert(embeddingFileHandle:close())

