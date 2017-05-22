--Torch lib for mpi commnication
local ffi = require("ffi")
ffi.load("libmpi",true)

require 'mpiT'

mpiT.Init()

print('init')

_rank = torch.IntStorage(1)
mpiT.Comm_rank(mpiT.COMM_WORLD,_rank)
rank = _rank[1]

_size = torch.IntStorage(1)
mpiT.Comm_size(mpiT.COMM_WORLD,_size)
size = _size[1]

assert(size>1)

print('size')

_sdata = torch.FloatTensor(1):storage()
_sdata:fill(rank)
_rdata = torch.FloatTensor(1):storage()
_rdata:fill(rank)

src = (rank-1)%size
dest = (rank+1)%size
tag = 0
status = mpiT.Status(1)

print('[' .. rank .. '/' .. size .. ']' .. 's=' .. _sdata[1] .. 'r=' .. _rdata[1] )
if (rank == 0) then
   mpiT.Send(_sdata,1,mpiT.FLOAT,dest,tag,mpiT.COMM_WORLD)
   mpiT.Recv(_rdata,1,mpiT.FLOAT,src,tag,mpiT.COMM_WORLD,status)
else
   mpiT.Recv(_rdata,1,mpiT.FLOAT,src,tag,mpiT.COMM_WORLD,status)
   mpiT.Send(_sdata,1,mpiT.FLOAT,dest,tag,mpiT.COMM_WORLD)
end
print('[' .. rank .. '/' .. size .. ']' .. 's=' .. _sdata[1] .. 'r=' .. _rdata[1] )

mpiT.Finalize()

