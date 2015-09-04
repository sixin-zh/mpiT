MPI for Torch library

-- Define the environment variable 
POME=Project home directory
Download mpiT to $POME/lib/mpiT with
git clone https://github.com/sixin-zh/mpiT $POME/lib/mpiT

-- Install MPI 
Dowload MPI for CPU: www.mpich.org, for GPU: mvapich.cse.ohio-state.edu, or
OPENMPI
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
mpirun -np 4 luajit ptest.lua
mpirun -np 4 luajit plaunch.lua

Important updates:
-- The starting offset in pclient.lua is set to 1 instead of 0, for current Torch7's support.
-- use mpiT.Cancel to release the buffer ownership on io stop in mpiT.aio_read and mpiT.aio_recv
-- add asyncsgd implementation which trains mnist in parallel
