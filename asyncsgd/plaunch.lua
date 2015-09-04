-- mpirun -n 4 luajit ptest.lua

local oncuda = true
local AGPU = {1,2} -- ,3,4,5,6,7,8}

require 'mpiT'
dofile('init.lua')
mpiT.Init()
local world = mpiT.COMM_WORLD
local rank = mpiT.get_rank(world)
local size = mpiT.get_size(world)
local gpu = nil

local conf = {}
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
conf.oncuda = oncuda

opt = {}
opt.lr = 1e-2
opt.rank = conf.rank 

if rank < size/2 then
   -- server   
   if oncuda and false then
      require 'cunn'
      local gpus = cutorch.getDeviceCount()
      gpu = AGPU[(rank%(size/2)) % gpus + 1]
      cutorch.setDevice(gpu)
      print('[server] rank',rank,'use gpu',gpu)
      torch.setdefaulttensortype('torch.CudaTensor')
   else
      print('[server] rank',rank,'use cpu')
      torch.setdefaulttensortype('torch.FloatTensor')
   end
   local ps = pServer(conf)
   ps:start()
else
   if oncuda then
      require 'cunn'
      local gpus = cutorch.getDeviceCount()
      gpu = AGPU[(rank%(size/2)) % gpus + 1]
      cutorch.setDevice(gpu)
      print('[client] rank',rank,'use gpu',gpu)
      torch.setdefaulttensortype('torch.CudaTensor')
   else
      print('[client] rank',rank,'use cpu')
      torch.setdefaulttensortype('torch.FloatTensor')
   end

   -- setup
   opt.device = gpu
   opt.pc = pClient(conf)
   -- go
   dofile('goot.lua')
end

mpiT.Finalize()