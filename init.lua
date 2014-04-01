-- Torch lib for mpi commnication
-- Author: Sixin Zhang (zsx@cims.nyu.edu)

require 'libmpiT'

------ lua coroutine comm ------
mpiT.signal_INIT = 1
mpiT.signal_EXEC = 2
mpiT.signal_OK = 3 
mpiT.signal_ERR = 4
mpiT.signal_DONE = 5

------ mpi i/o ------
function mpiT.get_rank(www)
   local _rank = torch.IntStorage(1)
   mpiT.Comm_rank(www,_rank)
   return _rank[1]
end

function mpiT.get_size(www)
   local _size = torch.IntStorage(1)
   mpiT.Comm_size(www,_size)
   return _size[1]
end

function mpiT.aio_send(storage_th,size_long,type_mpi,
		       dest_int,tag_int,comm_mpi,state,cb)
   local req = mpiT.Request(1)
   local status = mpiT.Status(1)
   local finished = torch.IntStorage(1):fill(0)
   local state = state or {io=true}
   -- print('aio_send',state.io)
   mpiT.Isend(storage_th,size_long,type_mpi,dest_int,tag_int,comm_mpi,req)
   while finished[1]==0 and state.io do
      mpiT.Test(req,finished,status)
      coroutine.yield(mpiT.signal_EXEC)
   end
   if cb then
      cb(state)
   end
   coroutine.yield(mpiT.signal_OK) -- TODO check status
end

function mpiT.aio_recv(storage_th,size_long,type_mpi,
		       src_int,tag_int,comm_mpi,state,cb)
   local req = mpiT.Request(1)
   local status = mpiT.Status(1)
   local finished = torch.IntStorage(1)
   local state = state or {io=true}
   finished[1]=0
   -- print('aio_recv',state.io)
   while finished[1]==0 and state.io do
      mpiT.Iprobe(src_int,tag_int,comm_mpi,finished,status)
      coroutine.yield(mpiT.signal_EXEC)
   end
   finished[1]=0
   mpiT.Irecv(storage_th,size_long,type_mpi,src_int,tag_int,comm_mpi,req)
   while finished[1]==0 and state.io do
      mpiT.Test(req,finished,status)
      coroutine.yield(mpiT.signal_EXEC)
   end
   if cb then
      cb(state)
   end
   coroutine.yield(mpiT.signal_OK) -- TODO check status
end

-- torch object -> torch.CharStorage
function mpiT.serialize(o)
   local f = torch.MemoryFile()
   f:binary()
   f:writeObject(o)
   s = f:storage()
   f:close()   
   return s
end

-- torch storage type -> mpi type
function mpiT.type(s)
   -- TODO maybe change api of aio as well
end

-- torch.CharStorage -> torch object
function mpiT.deserialize(s)
   local f = torch.MemoryFile(s)
   f:binary()
   o = f:readObject()
   f:close()
   return o
end

------ lua coroutine helper ------
require 'sys'
include('queue.lua')

function mpiT.co_execute(exec,pack)
   local co = coroutine.create(
      function()
	 exec(unpack(pack))
      end
   )
   assert(co ~= nil)
   local ok,status = coroutine.resume(co) -- execute
   -- print('mpiT.co_execute',ok,status)
   assert(ok == true)
   return co
end

-- check if any co done, otherwise resume some co in coq
function mpiT.co_ping(coq)
   if not coq:empty() then
      local co = coq:pop()
      if coroutine.status(co) ~= 'dead' then
	 local ok,status = coroutine.resume(co)
	 if (ok == true) then
	    if (status == mpiT.signal_DONE) then
	       local ok = coroutine.resume(co)
	       --print('co_wait done',co,ok)
	       assert(ok == true)
	       co = nil
	    else
	       coq:push(co) -- not done yet
	    end
	 else
	    print('mpiT.co_wait err',status)
	    co = nil
	    assert(false)
	 end
      else
	 print('mpiT.co_wait co dead, skip')
	 co = nil
      end
   else
      return false -- false if queue is empty
   end
   return true
end

-- wait until all the coroutines (threads) in the queue coq
-- issue mpiT.signal_DONE
function mpiT.co_wait(coq)
   while (mpiT.co_ping(coq)) do
      sys.usleep(1)
   end
end
