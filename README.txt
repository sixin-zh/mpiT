MPI for Torch library (Apache License, Version 2.0)

-- Define the environment variable 
POME=Project home directory
Download mpiT to $POME/lib/mpiT with
git clone https://github.com/sixin-zh/mpiT $POME/lib/mpiT

-- Install MPI 
MPICH: www.mpich.org, mvapich.cse.ohio-state.edu, 
OPENMPI: www.open-mpi.org

You may install the MPI to ${POME}/exe/mpi, then
make sure ${POME}/exe/mpi/bin/mpicc and ${POME}/exe/mpi/bin/mpicxx work.

-- Install mpiT using luarocks
cd $POME/lib/mpiT
-- For mpich and mvapich
$POME/exe/luajit-rocks/bin/luarocks make mpit-mvapich-1.rockspec
-- For openmpi (differ in the .so to link)
$POME/exe/luajit-rocks/bin/luarocks make mpit-openmpi-1.rockspec

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
-- The implementation of msgd, downpour, easgd and eamsgd is added.
-- The starting offset in pclient.lua is set to 1 rather than 0, for current Torch7's support.
-- Use mpiT.Cancel to release the buffer ownership on io stop in mpiT.aio_read
and mpiT.aio_recv.
