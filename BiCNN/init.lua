------ parameter server and client ------
require 'mpiT'
mpiT.tag_ps_recv_init  = 1
mpiT.tag_ps_recv_grad  = 2
mpiT.tag_ps_send_param = 3
mpiT.tag_ps_recv_param = 4
mpiT.tag_ps_recv_header = 5
mpiT.tag_ps_recv_stop = 6
mpiT.tag_ps_recv_param_tail = 7
mpiT.tag_ps_recv_grad_tail = 8

dofile('pserver.lua')
dofile('pclient.lua')

dofile('optim-msgd.lua')
dofile('optim-downpour.lua')
dofile('optim-eamsgd.lua')
dofile('optim-rmsprop.lua')
dofile('optim-rmsprop-single.lua')
dofile('optim-adam.lua')
dofile('optim-adam-single.lua')
dofile('optim-adamax.lua')
dofile('optim-adamax-single.lua')
dofile('optim-adagrad.lua')
dofile('optim-adagrad-single.lua')
dofile('optim-adadelta.lua')
dofile('optim-adadelta-single.lua')
require 'nn'
if nn.Normalize == nil then
   dofile('Normalize.lua')
end
