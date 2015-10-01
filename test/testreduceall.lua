--Torch lib for mpi commnication

require 'mpiT'
require 'sys'

mpiT.Init()

megs = os.getenv('MEGS') or '10'
megs = tonumber(megs)

_rank = torch.IntStorage(1)
mpiT.Comm_rank(mpiT.COMM_WORLD,_rank)
rank = _rank[1]

_size = torch.IntStorage(1)
mpiT.Comm_size(mpiT.COMM_WORLD,_size)
size = _size[1]

if rank == 0 then print('num nodes: ' .. size) end

torch.manualSeed(123)
a = torch.FloatTensor(megs,1024,1024):uniform()
if rank == 0 then print('a:size()', a:size()) end
a_reduced = torch.FloatTensor(a:size()):zero()
if rank == 0 then print('a:storage()[1]', a:storage()[1]) end

sys.tic()
mpiT.Allreduce(a:storage(), a_reduced:storage(), a:numel(), mpiT.FLOAT, mpiT.SUM, mpiT.COMM_WORLD)
if rank == 0 then print('toc: ', sys.toc()) end

if rank == 0 then print('a after :storage()[1]', a_reduced:storage()[1]) end

mpiT.Finalize()

