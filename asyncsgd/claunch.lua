-- cpu launch
-- Author: Sixin Zhang (zsx@cims.nyu.edu)
-- luajit claunch.lua
dofile('init.lua')

opt = {}
opt.gpuid = -1
torch.setdefaulttensortype('torch.FloatTensor')

opt.name = 'sgd'
opt.lr = 1e-1
opt.mom = 0.99

dofile('goot.lua')
