dofile('init.lua')

local oncuda = false
local AGPU = {1,2} -- ,3,4,5,6,7,8}

require 'mpiT'
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
conf.lr = opt.lr 
opt.rank = conf.rank 

if rank < size/2 then
   -- server   
   if oncuda and true then
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
   --opt.conf = 'in.lua'
   --opt.save = true
   --opt.device = gpu
   --opt.nodisp = true
   --opt.resume = false
   --opt.noprogress = true
   --opt.data_root = '/home/zsx/data/torch7/mnist10'

   -- pclient   
   opt.pc = pClient(conf)
   -- go
   dofile('goot.lua')
end

mpiT.Finalize()
