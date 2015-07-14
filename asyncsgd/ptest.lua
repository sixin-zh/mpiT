-- mpirun -n 2 $POME/exe/torch/bin/torch ptest.lua

local ssize = 3*4096*4096 -- 20000*4096+4096*4096+4096*1000
local maxsec = 60
local usecuda = true -- false

require 'mpiT'
mpiT.Init()
local world = mpiT.COMM_WORLD
local rank = mpiT.get_rank(world)
local size = mpiT.get_size(world)

assert((size>0) and (size%2==0))

if usecuda then
require 'cunn'
torch.setdefaulttensortype('torch.CudaTensor')
local gpus = cutorch.getDeviceCount()
local gpu =(rank%(size/2)) % gpus + 1
cutorch.setDevice(gpu)
print(rank,'use gpu',gpu)
else
torch.setdefaulttensortype('torch.FloatTensor')
end

local conf = {}
conf.maxsec = maxsec
conf.rank = rank
conf.world = world
conf.sranks = {}
conf.cranks = {}
for i = 0,size-1 do
   if i < size/2 then
      table.insert(conf.sranks,i)
   else
      table.insert(conf.cranks,i)
   end
end

if rank < size/2 then
   -- server   
   local ps = pServer(conf)
   ps:start()
else
   -- client
   conf.pstorage = torch.Storage(ssize)
   conf.plong = conf.pstorage:size()
   local pc = pClient(conf)
   pc:start()
end

mpiT.Finalize()
