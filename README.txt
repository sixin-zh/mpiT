MPI for Torch library

-- Define the environment variable 
POME=Project home directory
Download mpiT to $POME/lib/mpiT with
git clone https://github.com/sixin-zh/mpiT $POME/lib/mpiT

-- Install MPI 
Dowload MPI for CPU: www.mpich.org, for GPU: mvapich.cse.ohio-state.edu
You may install the MPI to ${POME}/exe/mpi, then
make sure ${POME}/exe/mpi/bin/mpicc and ${POME}/exe/mpi/bin/mpicxx work.

-- Install mpiT using luarocks
cd $POME/lib/mpiT
$POME/exe/luajit-rocks/bin/luarocks make mpit-1.0.0-0.rockspec

-- Test
mpirun -np 2 luajit test.lua

Important updates:
-- use mpiT.Cancel to release the buffer ownership on io stop in mpiT.aio_read and mpiT.aio_recv
-- add asyncsgd implementation which trains mnist in parallel, test it: mpirun -n 2 luajit ptest.lua
-- checkout the CMakeLists.txt.openmpi for openmpi support
