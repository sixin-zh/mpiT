-- mpirun -n 2 luajit testreduceall.lua

local ssize = 3*4096*4096
local usecuda = false

require 'mpiT'
dofile('init.lua')
mpiT.Init()
local world = mpiT.COMM_WORLD
local rank = mpiT.get_rank(world)
local size = mpiT.get_size(world)

assert((size>0) and (size%2==0))

local conf = {}
conf.rank = rank
conf.world = world
conf.sranks = {}
conf.cranks = {}
for i = 0,size-1 do
   if i < size/2 then
      table.insert(conf.sranks,i) --as server
   else
      table.insert(conf.cranks,i) --as client
   end
end

if rank < size/2 then
   print('rank ' .. rank .. ' is server.')
   -- require 'cutorch' -- in case usecuda==true and your mpirun does not stop, try uncomment this out.
   torch.setdefaulttensortype('torch.FloatTensor')
   print(rank,'use cpu')
   -- server   
   local ps = pServer(conf)
   ps:start()
else
   print('rank ' .. rank .. ' is client.')

   -- use gpu?
   if usecuda then
      require 'cutorch'
      torch.setdefaulttensortype('torch.CudaTensor')
      local gpus = cutorch.getDeviceCount()
      local gpu =(rank%(size/2)) % gpus + 1
      cutorch.setDevice(gpu)
      print(rank,'use gpu',gpu)
   else
      torch.setdefaulttensortype('torch.FloatTensor')
      print(rank,'use cpu')
   end

   -- client
   local theta = torch.Tensor(ssize)
   local grad = torch.Tensor(ssize)
   local pc = pClient(conf)
   pc:start(theta,grad)

   local begin = os.time()
   for t=1,3 do
      print('rank' .. rank .. 'pingpong')
      pc:async_recv_param()
      pc:async_send_grad()
      pc:wait()
   end
   local now = os.time()
   print('rank ' .. rank .. ' bandwidth(bi-direction) is ' .. (2*ssize*4/(now-begin)/1024/1024) .. ' MBytes/sec')
   
   pc:stop()
   print('pc stopped')
end

   torch.manualSeed(123)
   a = torch.FloatTensor(3,2):uniform()
   b = torch.FloatTensor(3,2)
   print('a', a)
   mpiT.Allreduce(a:storage(), b:storage(), 6, mpiT.FLOAT, mpiT.SUM, mpiT.COMM_WORLD)
   print('b after a', b)

mpiT.Finalize()
