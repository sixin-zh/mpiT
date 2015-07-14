------ parameter server and client ------
mpiT.tag_ps_recv_init  = 1
mpiT.tag_ps_recv_grad  = 2
mpiT.tag_ps_send_param = 3
mpiT.tag_ps_recv_param = 4
mpiT.tag_ps_recv_header = 5
mpiT.tag_ps_recv_stop = 6

dofile('pserver.lua')
dofile('pclient.lua')