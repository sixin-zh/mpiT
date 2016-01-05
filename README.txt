MPI for Torch library (Apache License, Version 2.0)

-- Install MPI 
MPICH: www.mpich.org, mvapich.cse.ohio-state.edu, 
OPENMPI: www.open-mpi.org

You should install the MPI to MPI_PREFIX (redefine it), and
make sure ${MPI_PREFIX}/bin/mpicc and ${MPI_PREFIX}/bin/mpicxx work.

-- Install mpiT using luarocks
git clone https://github.com/sixin-zh/mpiT
-- For mpich and mvapich
luarocks make mpit-mvapich-1.rockspec
-- For openmpi (differ in the .so to link)
luarocks make mpit-openmpi-1.rockspec

-- Test mpiT
mpirun -np 2 luajit test.lua

-- Test asyncsgd
cd asyncsgd
-- test Torch on cpu
luajit claunch.lua
-- test Torch on gpu
luajit glaunch.lua
-- test the bandwidth
mpirun -np 4 luajit ptest.lua 
-- the parallel mnist training using downpour/easgd on 6 cpus and 6 gpus
mpirun -np 12 luajit mlaunch.lua

Important updates:
-- Correct off-by-one error in pClient_init due to Zheng Xu
(xuzhustc@gmail.com). See https://github.com/sixin-zh/mpiT/pull/16
-- BiCNN is supported by Minwei Feng (mfeng@us.ibm.com).
-- The implementation of msgd, downpour, easgd and eamsgd is added.
-- The starting offset in pclient.lua is set to 1 rather than 0, for current Torch7's support.
-- Use mpiT.Cancel to release the buffer ownership on io stop in mpiT.aio_read
and mpiT.aio_recv.
