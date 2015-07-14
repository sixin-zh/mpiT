require 'mpiT'

mpiT.Init()

--local world = mpiT.COMM_WORLD
--local rank = mpiT.get_rank(world)
--local size = mpiT.get_size(world)
local gpu = 1 -- rank+1

require 'cunn'
torch.setdefaulttensortype('torch.CudaTensor')
opt = {}
opt.device = gpu
print('[client] use gpu', opt.device)
cutorch.setDevice(opt.device)

dofile('goot.lua')

mpiT.Finalize()
