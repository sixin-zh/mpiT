local ssize = 16*4096*4096
local usecuda = false

require 'mpiT'
dofile('init.lua')
mpiT.Init()
local world = mpiT.COMM_WORLD
local rank = mpiT.get_rank(world)
local size = mpiT.get_size(world)

assert((size>0) and (size%2==0))
sys.tic()
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

--if math.fmod(rank,2) ~= 0  then
if rank < size/2 then
   print('rank ' .. rank .. ' is server.')
   torch.setdefaulttensortype('torch.FloatTensor')
   print(rank,'use cpu')
   local ps = pServer(conf)
   ps:start()
else
   print('rank ' .. rank .. ' is client.')

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

   local theta = torch.Tensor(ssize)
   local grad = torch.Tensor(ssize)
   local pc = pClient(conf)
   pc:start(theta,grad)

   local begin = os.time()
   for t=1,30000000000 do
      pc:async_send_grad()
      pc:async_recv_param()
      if pc.rank == size/2 then
         comm_time_4test = sys.clock()
      end
      pc:wait()
      collectgarbage()
      if pc.rank == size/2 then
        print(string.format("Client %s: communication time: %.2f , curr time %.2f",
                          pc.rank, sys.clock() - comm_time_4test, sys.toc()/3600))
      end
      for o=1,(rank-47)*(rank-47)*(rank-47)*(rank-47)*(rank-47)*(rank-47)*(rank-47)*(rank-47)*(rank-47)  do
          grad:cmul(torch.Tensor(ssize))
          grad:cdiv(torch.Tensor(ssize))
          collectgarbage()
      end
   end
   local now = os.time()
   print('rank ' .. rank .. ' bandwidth(bi-direction) is ' .. (2*ssize*4/(now-begin)/1024/1024) .. ' MBytes/sec')
   pc:stop()
   print('pc stopped')
end

mpiT.Finalize()

