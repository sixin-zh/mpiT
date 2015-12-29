-- gpu launch
-- Author: Sixin Zhang (zsx@cims.nyu.edu)
-- luajit glaunch.lua

dofile('init.lua')

opt = {}
opt.gpuid = 1

require 'cunn'
torch.setdefaulttensortype('torch.CudaTensor')
print('[client] use gpu', opt.gpuid)
cutorch.setDevice(opt.gpuid)

opt.name = 'sgd'
opt.lr = 1e-1
opt.mom = 0.99

dofile('goot.lua')
