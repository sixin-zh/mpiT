#MPI for Torch

## Install MPI 
MPICH: [www.mpich.org](http://www.mpich.org), [mvapich.cse.ohio-state.edu](http://mvapich.cse.ohio-state.edu),   
OPENMPI: [www.open-mpi.org](http://www.open-mpi.org)

You should install the MPI to `MPI_PREFIX` (redefine it), and make sure `${MPI_PREFIX}/bin/mpicc` and `${MPI_PREFIX}/bin/mpicxx` work.

## Install mpiT using luarocks

```
git clone https://github.com/sixin-zh/mpiT
cd mpiT
```

For MPICH and MVAPICH

```
luarocks make mpit-mvapich-1.rockspec
```

For OPENMPI (differ in the .so to link)

```
luarocks make mpit-openmpi-1.rockspec
```

## Test mpiT
```
mpirun -np 2 th test.lua
```

## Test asyncsgd

```
cd asyncsgd
```

test Torch on CPU

```
th claunch.lua
```

test Torch on GPU

```
th glaunch.lua
```

test the bandwidth

```
mpirun -np 4 th ptest.lua 
```

the parallel mnist training using *downpour* or *easgd* on 6 CPUs and 6 GPUs

```
mpirun -np 12 th mlaunch.lua
```


## Important updates:
- Set usec default to be 0 in `mpiT.co_wait` to improve IO throughput.
- Correct off-by-one error in pClient_init, thanks to Zheng Xu
(xuzhustc@gmail.com). See https://github.com/sixin-zh/mpiT/pull/16.
- BiCNN is supported by Minwei Feng (mfeng@us.ibm.com).
- The implementation of *msgd*, *downpour*, *easgd* and *eamsgd* is added.
- The starting offset in pclient.lua is set to 1 rather than 0, for current Torch7's support.
- Use `mpiT.Cancel` to release the buffer ownership on io stop in `mpiT.aio_read` and `mpiT.aio_recv`.
- To run mpiT with cuda support, configure and install MPI with cuda support and add MPI library path to environment variable `LD_LIBRARY_PATH=${MPI_PREFIX}/lib:$LD_LIBRARY_PATH`

## Reference

Sixin Zhang, Anna Choromanska, Yann LeCun. [Deep learning with Elastic Averaging SGD](https://cs.nyu.edu/~zsx/nips2015.pdf). In Neural Information Processing Systems, 2015

## License

Releasing under an Apache-2.0 license.
