-- mpi launch
-- Author: Sixin Zhang (zsx@cims.nyu.edu)
-- mpirun -n 12 luajit mlaunch.lua
local oncuda = false
local ffi = require("ffi")
ffi.load("libmpi",true)
local AGPU = nil
if oncuda then
   require 'cutorch'
   AGPU = {1,2,3,4,5,6} -- use the first 6 gpus on each machine
end

dofile('init.lua')
mpiT.Init()

local world = mpiT.COMM_WORLD
local rank = mpiT.get_rank(world)
local size = mpiT.get_size(world)
local gpuid = -1

local conf = {}
conf.rank = rank
conf.world = world
conf.sranks = {}
conf.cranks = {}
for i = 0,size-1 do
   if math.fmod(i,2)==0 then
      table.insert(conf.sranks,i)
   else
      table.insert(conf.cranks,i)
   end
end

opt = {}
opt.name = 'downpour'
opt.lr = 1e-4
opt.su = 1
--[[
opt.name = 'eamsgd'
opt.lr = 1e-1
opt.su = 100
opt.mva = 0.9/6 -- this is \beta/p when p=6

opt.lr = 1e-2
opt.mom = 0.99
--]]
opt.maxepoch = 10000

if math.fmod(rank,2)==0 then
   -- server
   print('[server] rank',rank,'use cpu')
   torch.setdefaulttensortype('torch.FloatTensor')  
   local ps = pServer(conf)
   ps:start()
else
   if AGPU then
      require 'cunn'
      local gpus = cutorch.getDeviceCount()
      gpuid = AGPU[(rank%(size/2)) % gpus + 1]
      cutorch.setDevice(gpuid)
      print('[client] rank ' .. rank .. ' use gpu ' .. gpuid)
      torch.setdefaulttensortype('torch.CudaTensor')
   else
      print('[client] rank ' .. rank .. ' use cpu')
      torch.setdefaulttensortype('torch.FloatTensor')
   end
   -- setup
   opt.gpuid = gpuid
   opt.pc = pClient(conf)
   opt.rank = rank
   -- go
   dofile('goot.lua')
end

mpiT.Finalize()
