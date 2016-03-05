static int _MPI_Abort(lua_State *L)
{
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 1, "MPI::Comm"));
  int errorcode = luaL_checkint(L, 2);
  int res = MPI_Abort(comm, errorcode);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Accumulate(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); void* origin_addr = (void*) _storage1->data;
  int origin_count = luaL_checkint(L, 2);
  MPI_Datatype origin_datatype = *((MPI_Datatype*) luaL_checkudata(L, 3, "MPI::Datatype"));
  int target_rank = luaL_checkint(L, 4);
  MPI_Aint target_disp = *((MPI_Aint*) luaL_checkudata(L, 5, "MPI::Aint"));
  int target_count = luaL_checkint(L, 6);
  MPI_Datatype target_datatype = *((MPI_Datatype*) luaL_checkudata(L, 7, "MPI::Datatype"));
  MPI_Op op = *((MPI_Op*) luaL_checkudata(L, 8, "MPI::Op"));
  MPI_Win win = *((MPI_Win*) luaL_checkudata(L, 9, "MPI::Win"));
  int res = MPI_Accumulate(origin_addr, origin_count, origin_datatype, target_rank, target_disp, target_count, target_datatype, op, win);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Add_error_class(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); int* errorclass = (int*) _storage1->data;
  int res = MPI_Add_error_class(errorclass);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Add_error_code(lua_State *L)
{
  int errorclass = luaL_checkint(L, 1);
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); int* errorcode = (int*) _storage2->data;
  int res = MPI_Add_error_code(errorclass, errorcode);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Add_error_string(lua_State *L)
{
  int errorcode = luaL_checkint(L, 1);
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); char* string = (char*) _storage2->data;
  int res = MPI_Add_error_string(errorcode, string);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Allgather(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); void* sendbuf = (void*) _storage1->data;
  int sendcount = luaL_checkint(L, 2);
  MPI_Datatype sendtype = *((MPI_Datatype*) luaL_checkudata(L, 3, "MPI::Datatype"));
  const char *_type4 = luaT_typename(L,4); MPI_THStorage *_storage4 = luaT_toudata(L,4,_type4); void* recvbuf = (void*) _storage4->data;
  int recvcount = luaL_checkint(L, 5);
  MPI_Datatype recvtype = *((MPI_Datatype*) luaL_checkudata(L, 6, "MPI::Datatype"));
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 7, "MPI::Comm"));
  int res = MPI_Allgather(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Allgatherv(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); void* sendbuf = (void*) _storage1->data;
  int sendcount = luaL_checkint(L, 2);
  MPI_Datatype sendtype = *((MPI_Datatype*) luaL_checkudata(L, 3, "MPI::Datatype"));
  const char *_type4 = luaT_typename(L,4); MPI_THStorage *_storage4 = luaT_toudata(L,4,_type4); void* recvbuf = (void*) _storage4->data;
  const char *_type5 = luaT_typename(L,5); MPI_THStorage *_storage5 = luaT_toudata(L,5,_type5); int* recvcounts = (int*) _storage5->data;
  const char *_type6 = luaT_typename(L,6); MPI_THStorage *_storage6 = luaT_toudata(L,6,_type6); int* displs = (int*) _storage6->data;
  MPI_Datatype recvtype = *((MPI_Datatype*) luaL_checkudata(L, 7, "MPI::Datatype"));
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 8, "MPI::Comm"));
  int res = MPI_Allgatherv(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, comm);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Alloc_mem(lua_State *L)
{
  MPI_Aint size = *((MPI_Aint*) luaL_checkudata(L, 1, "MPI::Aint"));
  MPI_Info info = *((MPI_Info*) luaL_checkudata(L, 2, "MPI::Info"));
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); void* baseptr = (void*) _storage3->data;
  int res = MPI_Alloc_mem(size, info, baseptr);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Allreduce(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); void* sendbuf = (void*) _storage1->data;
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); void* recvbuf = (void*) _storage2->data;
  int count = luaL_checkint(L, 3);
  MPI_Datatype datatype = *((MPI_Datatype*) luaL_checkudata(L, 4, "MPI::Datatype"));
  MPI_Op op = *((MPI_Op*) luaL_checkudata(L, 5, "MPI::Op"));
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 6, "MPI::Comm"));
  int res = MPI_Allreduce(sendbuf, recvbuf, count, datatype, op, comm);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Alltoall(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); void* sendbuf = (void*) _storage1->data;
  int sendcount = luaL_checkint(L, 2);
  MPI_Datatype sendtype = *((MPI_Datatype*) luaL_checkudata(L, 3, "MPI::Datatype"));
  const char *_type4 = luaT_typename(L,4); MPI_THStorage *_storage4 = luaT_toudata(L,4,_type4); void* recvbuf = (void*) _storage4->data;
  int recvcount = luaL_checkint(L, 5);
  MPI_Datatype recvtype = *((MPI_Datatype*) luaL_checkudata(L, 6, "MPI::Datatype"));
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 7, "MPI::Comm"));
  int res = MPI_Alltoall(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Alltoallv(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); void* sendbuf = (void*) _storage1->data;
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); int* sendcounts = (int*) _storage2->data;
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); int* sdispls = (int*) _storage3->data;
  MPI_Datatype sendtype = *((MPI_Datatype*) luaL_checkudata(L, 4, "MPI::Datatype"));
  const char *_type5 = luaT_typename(L,5); MPI_THStorage *_storage5 = luaT_toudata(L,5,_type5); void* recvbuf = (void*) _storage5->data;
  const char *_type6 = luaT_typename(L,6); MPI_THStorage *_storage6 = luaT_toudata(L,6,_type6); int* recvcounts = (int*) _storage6->data;
  const char *_type7 = luaT_typename(L,7); MPI_THStorage *_storage7 = luaT_toudata(L,7,_type7); int* rdispls = (int*) _storage7->data;
  MPI_Datatype recvtype = *((MPI_Datatype*) luaL_checkudata(L, 8, "MPI::Datatype"));
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 9, "MPI::Comm"));
  int res = MPI_Alltoallv(sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Alltoallw(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); void* sendbuf = (void*) _storage1->data;
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); int* sendcounts = (int*) _storage2->data;
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); int* sdispls = (int*) _storage3->data;
  MPI_Datatype* sendtypes = (MPI_Datatype*) luaL_checkudata(L, 4, "MPI::Datatype");
  const char *_type5 = luaT_typename(L,5); MPI_THStorage *_storage5 = luaT_toudata(L,5,_type5); void* recvbuf = (void*) _storage5->data;
  const char *_type6 = luaT_typename(L,6); MPI_THStorage *_storage6 = luaT_toudata(L,6,_type6); int* recvcounts = (int*) _storage6->data;
  const char *_type7 = luaT_typename(L,7); MPI_THStorage *_storage7 = luaT_toudata(L,7,_type7); int* rdispls = (int*) _storage7->data;
  MPI_Datatype* recvtypes = (MPI_Datatype*) luaL_checkudata(L, 8, "MPI::Datatype");
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 9, "MPI::Comm"));
  int res = MPI_Alltoallw(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes, comm);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Barrier(lua_State *L)
{
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 1, "MPI::Comm"));
  int res = MPI_Barrier(comm);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Bcast(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); void* buffer = (void*) _storage1->data;
  int count = luaL_checkint(L, 2);
  MPI_Datatype datatype = *((MPI_Datatype*) luaL_checkudata(L, 3, "MPI::Datatype"));
  int root = luaL_checkint(L, 4);
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 5, "MPI::Comm"));
  int res = MPI_Bcast(buffer, count, datatype, root, comm);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Bsend(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); void* buf = (void*) _storage1->data;
  int count = luaL_checkint(L, 2);
  MPI_Datatype type = *((MPI_Datatype*) luaL_checkudata(L, 3, "MPI::Datatype"));
  int dest = luaL_checkint(L, 4);
  int tag = luaL_checkint(L, 5);
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 6, "MPI::Comm"));
  int res = MPI_Bsend(buf, count, type, dest, tag, comm);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Bsend_init(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); void* buf = (void*) _storage1->data;
  int count = luaL_checkint(L, 2);
  MPI_Datatype type = *((MPI_Datatype*) luaL_checkudata(L, 3, "MPI::Datatype"));
  int dest = luaL_checkint(L, 4);
  int tag = luaL_checkint(L, 5);
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 6, "MPI::Comm"));
  MPI_Request* request = (MPI_Request*) luaL_checkudata(L, 7, "MPI::Request");
  int res = MPI_Bsend_init(buf, count, type, dest, tag, comm, request);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Buffer_attach(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); void* buffer = (void*) _storage1->data;
  int size = luaL_checkint(L, 2);
  int res = MPI_Buffer_attach(buffer, size);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Buffer_detach(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); void* buffer = (void*) _storage1->data;
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); int* size = (int*) _storage2->data;
  int res = MPI_Buffer_detach(buffer, size);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Cancel(lua_State *L)
{
  MPI_Request* request = (MPI_Request*) luaL_checkudata(L, 1, "MPI::Request");
  int res = MPI_Cancel(request);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Cart_coords(lua_State *L)
{
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 1, "MPI::Comm"));
  int rank = luaL_checkint(L, 2);
  int maxdims = luaL_checkint(L, 3);
  const char *_type4 = luaT_typename(L,4); MPI_THStorage *_storage4 = luaT_toudata(L,4,_type4); int* coords = (int*) _storage4->data;
  int res = MPI_Cart_coords(comm, rank, maxdims, coords);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Cart_create(lua_State *L)
{
  MPI_Comm old_comm = *((MPI_Comm*) luaL_checkudata(L, 1, "MPI::Comm"));
  int ndims = luaL_checkint(L, 2);
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); int* dims = (int*) _storage3->data;
  const char *_type4 = luaT_typename(L,4); MPI_THStorage *_storage4 = luaT_toudata(L,4,_type4); int* periods = (int*) _storage4->data;
  int reorder = luaL_checkint(L, 5);
  MPI_Comm* comm_cart = (MPI_Comm*) luaL_checkudata(L, 6, "MPI::Comm");
  int res = MPI_Cart_create(old_comm, ndims, dims, periods, reorder, comm_cart);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Cart_get(lua_State *L)
{
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 1, "MPI::Comm"));
  int maxdims = luaL_checkint(L, 2);
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); int* dims = (int*) _storage3->data;
  const char *_type4 = luaT_typename(L,4); MPI_THStorage *_storage4 = luaT_toudata(L,4,_type4); int* periods = (int*) _storage4->data;
  const char *_type5 = luaT_typename(L,5); MPI_THStorage *_storage5 = luaT_toudata(L,5,_type5); int* coords = (int*) _storage5->data;
  int res = MPI_Cart_get(comm, maxdims, dims, periods, coords);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Cart_map(lua_State *L)
{
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 1, "MPI::Comm"));
  int ndims = luaL_checkint(L, 2);
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); int* dims = (int*) _storage3->data;
  const char *_type4 = luaT_typename(L,4); MPI_THStorage *_storage4 = luaT_toudata(L,4,_type4); int* periods = (int*) _storage4->data;
  const char *_type5 = luaT_typename(L,5); MPI_THStorage *_storage5 = luaT_toudata(L,5,_type5); int* newrank = (int*) _storage5->data;
  int res = MPI_Cart_map(comm, ndims, dims, periods, newrank);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Cart_rank(lua_State *L)
{
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 1, "MPI::Comm"));
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); int* coords = (int*) _storage2->data;
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); int* rank = (int*) _storage3->data;
  int res = MPI_Cart_rank(comm, coords, rank);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Cart_shift(lua_State *L)
{
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 1, "MPI::Comm"));
  int direction = luaL_checkint(L, 2);
  int disp = luaL_checkint(L, 3);
  const char *_type4 = luaT_typename(L,4); MPI_THStorage *_storage4 = luaT_toudata(L,4,_type4); int* rank_source = (int*) _storage4->data;
  const char *_type5 = luaT_typename(L,5); MPI_THStorage *_storage5 = luaT_toudata(L,5,_type5); int* rank_dest = (int*) _storage5->data;
  int res = MPI_Cart_shift(comm, direction, disp, rank_source, rank_dest);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Cart_sub(lua_State *L)
{
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 1, "MPI::Comm"));
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); int* remain_dims = (int*) _storage2->data;
  MPI_Comm* new_comm = (MPI_Comm*) luaL_checkudata(L, 3, "MPI::Comm");
  int res = MPI_Cart_sub(comm, remain_dims, new_comm);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Cartdim_get(lua_State *L)
{
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 1, "MPI::Comm"));
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); int* ndims = (int*) _storage2->data;
  int res = MPI_Cartdim_get(comm, ndims);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Close_port(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); char* port_name = (char*) _storage1->data;
  int res = MPI_Close_port(port_name);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Comm_accept(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); char* port_name = (char*) _storage1->data;
  MPI_Info info = *((MPI_Info*) luaL_checkudata(L, 2, "MPI::Info"));
  int root = luaL_checkint(L, 3);
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 4, "MPI::Comm"));
  MPI_Comm* newcomm = (MPI_Comm*) luaL_checkudata(L, 5, "MPI::Comm");
  int res = MPI_Comm_accept(port_name, info, root, comm, newcomm);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Comm_call_errhandler(lua_State *L)
{
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 1, "MPI::Comm"));
  int errorcode = luaL_checkint(L, 2);
  int res = MPI_Comm_call_errhandler(comm, errorcode);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Comm_compare(lua_State *L)
{
  MPI_Comm comm1 = *((MPI_Comm*) luaL_checkudata(L, 1, "MPI::Comm"));
  MPI_Comm comm2 = *((MPI_Comm*) luaL_checkudata(L, 2, "MPI::Comm"));
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); int* result = (int*) _storage3->data;
  int res = MPI_Comm_compare(comm1, comm2, result);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Comm_connect(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); char* port_name = (char*) _storage1->data;
  MPI_Info info = *((MPI_Info*) luaL_checkudata(L, 2, "MPI::Info"));
  int root = luaL_checkint(L, 3);
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 4, "MPI::Comm"));
  MPI_Comm* newcomm = (MPI_Comm*) luaL_checkudata(L, 5, "MPI::Comm");
  int res = MPI_Comm_connect(port_name, info, root, comm, newcomm);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Comm_create(lua_State *L)
{
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 1, "MPI::Comm"));
  MPI_Group group = *((MPI_Group*) luaL_checkudata(L, 2, "MPI::Group"));
  MPI_Comm* newcomm = (MPI_Comm*) luaL_checkudata(L, 3, "MPI::Comm");
  int res = MPI_Comm_create(comm, group, newcomm);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Comm_create_keyval(lua_State *L)
{
  MPI_Comm_copy_attr_function* comm_copy_attr_fn = (MPI_Comm_copy_attr_function*) luaL_checkudata(L, 1, "MPI::Comm_copy_attr_function");
  MPI_Comm_delete_attr_function* comm_delete_attr_fn = (MPI_Comm_delete_attr_function*) luaL_checkudata(L, 2, "MPI::Comm_delete_attr_function");
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); int* comm_keyval = (int*) _storage3->data;
  const char *_type4 = luaT_typename(L,4); MPI_THStorage *_storage4 = luaT_toudata(L,4,_type4); void* extra_state = (void*) _storage4->data;
  int res = MPI_Comm_create_keyval(comm_copy_attr_fn, comm_delete_attr_fn, comm_keyval, extra_state);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Comm_delete_attr(lua_State *L)
{
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 1, "MPI::Comm"));
  int comm_keyval = luaL_checkint(L, 2);
  int res = MPI_Comm_delete_attr(comm, comm_keyval);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Comm_disconnect(lua_State *L)
{
  MPI_Comm* comm = (MPI_Comm*) luaL_checkudata(L, 1, "MPI::Comm");
  int res = MPI_Comm_disconnect(comm);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Comm_dup(lua_State *L)
{
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 1, "MPI::Comm"));
  MPI_Comm* newcomm = (MPI_Comm*) luaL_checkudata(L, 2, "MPI::Comm");
  int res = MPI_Comm_dup(comm, newcomm);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Comm_free(lua_State *L)
{
  MPI_Comm* comm = (MPI_Comm*) luaL_checkudata(L, 1, "MPI::Comm");
  int res = MPI_Comm_free(comm);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Comm_free_keyval(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); int* comm_keyval = (int*) _storage1->data;
  int res = MPI_Comm_free_keyval(comm_keyval);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Comm_get_attr(lua_State *L)
{
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 1, "MPI::Comm"));
  int comm_keyval = luaL_checkint(L, 2);
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); void* attribute_val = (void*) _storage3->data;
  const char *_type4 = luaT_typename(L,4); MPI_THStorage *_storage4 = luaT_toudata(L,4,_type4); int* flag = (int*) _storage4->data;
  int res = MPI_Comm_get_attr(comm, comm_keyval, attribute_val, flag);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Comm_get_errhandler(lua_State *L)
{
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 1, "MPI::Comm"));
  MPI_Errhandler* errhandler = (MPI_Errhandler*) luaL_checkudata(L, 2, "MPI::Errhandler");
  int res = MPI_Comm_get_errhandler(comm, errhandler);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Comm_get_name(lua_State *L)
{
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 1, "MPI::Comm"));
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); char* name = (char*) _storage2->data;
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); int* length = (int*) _storage3->data;
  int res = MPI_Comm_get_name(comm, name, length);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Comm_get_parent(lua_State *L)
{
  MPI_Comm* parent = (MPI_Comm*) luaL_checkudata(L, 1, "MPI::Comm");
  int res = MPI_Comm_get_parent(parent);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Comm_group(lua_State *L)
{
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 1, "MPI::Comm"));
  MPI_Group* group = (MPI_Group*) luaL_checkudata(L, 2, "MPI::Group");
  int res = MPI_Comm_group(comm, group);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Comm_join(lua_State *L)
{
  int fd = luaL_checkint(L, 1);
  MPI_Comm* intercomm = (MPI_Comm*) luaL_checkudata(L, 2, "MPI::Comm");
  int res = MPI_Comm_join(fd, intercomm);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Comm_rank(lua_State *L)
{
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 1, "MPI::Comm"));
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); int* rank = (int*) _storage2->data;
  int res = MPI_Comm_rank(comm, rank);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Comm_remote_group(lua_State *L)
{
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 1, "MPI::Comm"));
  MPI_Group* group = (MPI_Group*) luaL_checkudata(L, 2, "MPI::Group");
  int res = MPI_Comm_remote_group(comm, group);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Comm_remote_size(lua_State *L)
{
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 1, "MPI::Comm"));
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); int* size = (int*) _storage2->data;
  int res = MPI_Comm_remote_size(comm, size);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Comm_set_attr(lua_State *L)
{
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 1, "MPI::Comm"));
  int comm_keyval = luaL_checkint(L, 2);
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); void* attribute_val = (void*) _storage3->data;
  int res = MPI_Comm_set_attr(comm, comm_keyval, attribute_val);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Comm_set_errhandler(lua_State *L)
{
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 1, "MPI::Comm"));
  MPI_Errhandler errhandler = *((MPI_Errhandler*) luaL_checkudata(L, 2, "MPI::Errhandler"));
  int res = MPI_Comm_set_errhandler(comm, errhandler);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Comm_set_name(lua_State *L)
{
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 1, "MPI::Comm"));
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); char* name = (char*) _storage2->data;
  int res = MPI_Comm_set_name(comm, name);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Comm_size(lua_State *L)
{
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 1, "MPI::Comm"));
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); int* size = (int*) _storage2->data;
  int res = MPI_Comm_size(comm, size);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Comm_split(lua_State *L)
{
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 1, "MPI::Comm"));
  int color = luaL_checkint(L, 2);
  int key = luaL_checkint(L, 3);
  MPI_Comm* newcomm = (MPI_Comm*) luaL_checkudata(L, 4, "MPI::Comm");
  int res = MPI_Comm_split(comm, color, key, newcomm);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Comm_test_inter(lua_State *L)
{
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 1, "MPI::Comm"));
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); int* flag = (int*) _storage2->data;
  int res = MPI_Comm_test_inter(comm, flag);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Dims_create(lua_State *L)
{
  int nnodes = luaL_checkint(L, 1);
  int ndims = luaL_checkint(L, 2);
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); int* dims = (int*) _storage3->data;
  int res = MPI_Dims_create(nnodes, ndims, dims);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Errhandler_free(lua_State *L)
{
  MPI_Errhandler* errhandler = (MPI_Errhandler*) luaL_checkudata(L, 1, "MPI::Errhandler");
  int res = MPI_Errhandler_free(errhandler);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Error_class(lua_State *L)
{
  int errorcode = luaL_checkint(L, 1);
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); int* errorclass = (int*) _storage2->data;
  int res = MPI_Error_class(errorcode, errorclass);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Error_string(lua_State *L)
{
  int errorcode = luaL_checkint(L, 1);
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); char* string = (char*) _storage2->data;
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); int* resultlen = (int*) _storage3->data;
  int res = MPI_Error_string(errorcode, string, resultlen);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Exscan(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); void* sendbuf = (void*) _storage1->data;
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); void* recvbuf = (void*) _storage2->data;
  int count = luaL_checkint(L, 3);
  MPI_Datatype datatype = *((MPI_Datatype*) luaL_checkudata(L, 4, "MPI::Datatype"));
  MPI_Op op = *((MPI_Op*) luaL_checkudata(L, 5, "MPI::Op"));
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 6, "MPI::Comm"));
  int res = MPI_Exscan(sendbuf, recvbuf, count, datatype, op, comm);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_call_errhandler(lua_State *L)
{
  MPI_File fh = *((MPI_File*) luaL_checkudata(L, 1, "MPI::File"));
  int errorcode = luaL_checkint(L, 2);
  int res = MPI_File_call_errhandler(fh, errorcode);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_close(lua_State *L)
{
  MPI_File* fh = (MPI_File*) luaL_checkudata(L, 1, "MPI::File");
  int res = MPI_File_close(fh);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_delete(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); char* filename = (char*) _storage1->data;
  MPI_Info info = *((MPI_Info*) luaL_checkudata(L, 2, "MPI::Info"));
  int res = MPI_File_delete(filename, info);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_get_amode(lua_State *L)
{
  MPI_File fh = *((MPI_File*) luaL_checkudata(L, 1, "MPI::File"));
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); int* amode = (int*) _storage2->data;
  int res = MPI_File_get_amode(fh, amode);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_get_atomicity(lua_State *L)
{
  MPI_File fh = *((MPI_File*) luaL_checkudata(L, 1, "MPI::File"));
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); int* flag = (int*) _storage2->data;
  int res = MPI_File_get_atomicity(fh, flag);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_get_byte_offset(lua_State *L)
{
  MPI_File fh = *((MPI_File*) luaL_checkudata(L, 1, "MPI::File"));
  MPI_Offset offset = *((MPI_Offset*) luaL_checkudata(L, 2, "MPI::Offset"));
  MPI_Offset* disp = (MPI_Offset*) luaL_checkudata(L, 3, "MPI::Offset");
  int res = MPI_File_get_byte_offset(fh, offset, disp);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_get_errhandler(lua_State *L)
{
  MPI_File file = *((MPI_File*) luaL_checkudata(L, 1, "MPI::File"));
  MPI_Errhandler* errhandler = (MPI_Errhandler*) luaL_checkudata(L, 2, "MPI::Errhandler");
  int res = MPI_File_get_errhandler(file, errhandler);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_get_group(lua_State *L)
{
  MPI_File fh = *((MPI_File*) luaL_checkudata(L, 1, "MPI::File"));
  MPI_Group* group = (MPI_Group*) luaL_checkudata(L, 2, "MPI::Group");
  int res = MPI_File_get_group(fh, group);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_get_info(lua_State *L)
{
  MPI_File fh = *((MPI_File*) luaL_checkudata(L, 1, "MPI::File"));
  MPI_Info* info_used = (MPI_Info*) luaL_checkudata(L, 2, "MPI::Info");
  int res = MPI_File_get_info(fh, info_used);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_get_position(lua_State *L)
{
  MPI_File fh = *((MPI_File*) luaL_checkudata(L, 1, "MPI::File"));
  MPI_Offset* offset = (MPI_Offset*) luaL_checkudata(L, 2, "MPI::Offset");
  int res = MPI_File_get_position(fh, offset);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_get_position_shared(lua_State *L)
{
  MPI_File fh = *((MPI_File*) luaL_checkudata(L, 1, "MPI::File"));
  MPI_Offset* offset = (MPI_Offset*) luaL_checkudata(L, 2, "MPI::Offset");
  int res = MPI_File_get_position_shared(fh, offset);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_get_size(lua_State *L)
{
  MPI_File fh = *((MPI_File*) luaL_checkudata(L, 1, "MPI::File"));
  MPI_Offset* size = (MPI_Offset*) luaL_checkudata(L, 2, "MPI::Offset");
  int res = MPI_File_get_size(fh, size);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_get_type_extent(lua_State *L)
{
  MPI_File fh = *((MPI_File*) luaL_checkudata(L, 1, "MPI::File"));
  MPI_Datatype datatype = *((MPI_Datatype*) luaL_checkudata(L, 2, "MPI::Datatype"));
  MPI_Aint* extent = (MPI_Aint*) luaL_checkudata(L, 3, "MPI::Aint");
  int res = MPI_File_get_type_extent(fh, datatype, extent);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_get_view(lua_State *L)
{
  MPI_File fh = *((MPI_File*) luaL_checkudata(L, 1, "MPI::File"));
  MPI_Offset* disp = (MPI_Offset*) luaL_checkudata(L, 2, "MPI::Offset");
  MPI_Datatype* etype = (MPI_Datatype*) luaL_checkudata(L, 3, "MPI::Datatype");
  MPI_Datatype* filetype = (MPI_Datatype*) luaL_checkudata(L, 4, "MPI::Datatype");
  const char *_type5 = luaT_typename(L,5); MPI_THStorage *_storage5 = luaT_toudata(L,5,_type5); char* datarep = (char*) _storage5->data;
  int res = MPI_File_get_view(fh, disp, etype, filetype, datarep);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_iread(lua_State *L)
{
  MPI_File fh = *((MPI_File*) luaL_checkudata(L, 1, "MPI::File"));
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); void* buf = (void*) _storage2->data;
  int count = luaL_checkint(L, 3);
  MPI_Datatype datatype = *((MPI_Datatype*) luaL_checkudata(L, 4, "MPI::Datatype"));
  MPI_Request* request = (MPI_Request*) luaL_checkudata(L, 5, "MPI::Request");
  int res = MPI_File_iread(fh, buf, count, datatype, request);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_iread_at(lua_State *L)
{
  MPI_File fh = *((MPI_File*) luaL_checkudata(L, 1, "MPI::File"));
  MPI_Offset offset = *((MPI_Offset*) luaL_checkudata(L, 2, "MPI::Offset"));
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); void* buf = (void*) _storage3->data;
  int count = luaL_checkint(L, 4);
  MPI_Datatype datatype = *((MPI_Datatype*) luaL_checkudata(L, 5, "MPI::Datatype"));
  MPI_Request* request = (MPI_Request*) luaL_checkudata(L, 6, "MPI::Request");
  int res = MPI_File_iread_at(fh, offset, buf, count, datatype, request);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_iread_shared(lua_State *L)
{
  MPI_File fh = *((MPI_File*) luaL_checkudata(L, 1, "MPI::File"));
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); void* buf = (void*) _storage2->data;
  int count = luaL_checkint(L, 3);
  MPI_Datatype datatype = *((MPI_Datatype*) luaL_checkudata(L, 4, "MPI::Datatype"));
  MPI_Request* request = (MPI_Request*) luaL_checkudata(L, 5, "MPI::Request");
  int res = MPI_File_iread_shared(fh, buf, count, datatype, request);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_iwrite(lua_State *L)
{
  MPI_File fh = *((MPI_File*) luaL_checkudata(L, 1, "MPI::File"));
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); void* buf = (void*) _storage2->data;
  int count = luaL_checkint(L, 3);
  MPI_Datatype datatype = *((MPI_Datatype*) luaL_checkudata(L, 4, "MPI::Datatype"));
  MPI_Request* request = (MPI_Request*) luaL_checkudata(L, 5, "MPI::Request");
  int res = MPI_File_iwrite(fh, buf, count, datatype, request);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_iwrite_at(lua_State *L)
{
  MPI_File fh = *((MPI_File*) luaL_checkudata(L, 1, "MPI::File"));
  MPI_Offset offset = *((MPI_Offset*) luaL_checkudata(L, 2, "MPI::Offset"));
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); void* buf = (void*) _storage3->data;
  int count = luaL_checkint(L, 4);
  MPI_Datatype datatype = *((MPI_Datatype*) luaL_checkudata(L, 5, "MPI::Datatype"));
  MPI_Request* request = (MPI_Request*) luaL_checkudata(L, 6, "MPI::Request");
  int res = MPI_File_iwrite_at(fh, offset, buf, count, datatype, request);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_iwrite_shared(lua_State *L)
{
  MPI_File fh = *((MPI_File*) luaL_checkudata(L, 1, "MPI::File"));
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); void* buf = (void*) _storage2->data;
  int count = luaL_checkint(L, 3);
  MPI_Datatype datatype = *((MPI_Datatype*) luaL_checkudata(L, 4, "MPI::Datatype"));
  MPI_Request* request = (MPI_Request*) luaL_checkudata(L, 5, "MPI::Request");
  int res = MPI_File_iwrite_shared(fh, buf, count, datatype, request);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_open(lua_State *L)
{
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 1, "MPI::Comm"));
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); char* filename = (char*) _storage2->data;
  int amode = luaL_checkint(L, 3);
  MPI_Info info = *((MPI_Info*) luaL_checkudata(L, 4, "MPI::Info"));
  MPI_File* fh = (MPI_File*) luaL_checkudata(L, 5, "MPI::File");
  int res = MPI_File_open(comm, filename, amode, info, fh);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_preallocate(lua_State *L)
{
  MPI_File fh = *((MPI_File*) luaL_checkudata(L, 1, "MPI::File"));
  MPI_Offset size = *((MPI_Offset*) luaL_checkudata(L, 2, "MPI::Offset"));
  int res = MPI_File_preallocate(fh, size);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_read(lua_State *L)
{
  MPI_File fh = *((MPI_File*) luaL_checkudata(L, 1, "MPI::File"));
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); void* buf = (void*) _storage2->data;
  int count = luaL_checkint(L, 3);
  MPI_Datatype datatype = *((MPI_Datatype*) luaL_checkudata(L, 4, "MPI::Datatype"));
  MPI_Status* status = (MPI_Status*) luaL_checkudata(L, 5, "MPI::Status");
  int res = MPI_File_read(fh, buf, count, datatype, status);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_read_all(lua_State *L)
{
  MPI_File fh = *((MPI_File*) luaL_checkudata(L, 1, "MPI::File"));
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); void* buf = (void*) _storage2->data;
  int count = luaL_checkint(L, 3);
  MPI_Datatype datatype = *((MPI_Datatype*) luaL_checkudata(L, 4, "MPI::Datatype"));
  MPI_Status* status = (MPI_Status*) luaL_checkudata(L, 5, "MPI::Status");
  int res = MPI_File_read_all(fh, buf, count, datatype, status);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_read_all_begin(lua_State *L)
{
  MPI_File fh = *((MPI_File*) luaL_checkudata(L, 1, "MPI::File"));
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); void* buf = (void*) _storage2->data;
  int count = luaL_checkint(L, 3);
  MPI_Datatype datatype = *((MPI_Datatype*) luaL_checkudata(L, 4, "MPI::Datatype"));
  int res = MPI_File_read_all_begin(fh, buf, count, datatype);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_read_all_end(lua_State *L)
{
  MPI_File fh = *((MPI_File*) luaL_checkudata(L, 1, "MPI::File"));
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); void* buf = (void*) _storage2->data;
  MPI_Status* status = (MPI_Status*) luaL_checkudata(L, 3, "MPI::Status");
  int res = MPI_File_read_all_end(fh, buf, status);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_read_at(lua_State *L)
{
  MPI_File fh = *((MPI_File*) luaL_checkudata(L, 1, "MPI::File"));
  MPI_Offset offset = *((MPI_Offset*) luaL_checkudata(L, 2, "MPI::Offset"));
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); void* buf = (void*) _storage3->data;
  int count = luaL_checkint(L, 4);
  MPI_Datatype datatype = *((MPI_Datatype*) luaL_checkudata(L, 5, "MPI::Datatype"));
  MPI_Status* status = (MPI_Status*) luaL_checkudata(L, 6, "MPI::Status");
  int res = MPI_File_read_at(fh, offset, buf, count, datatype, status);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_read_at_all(lua_State *L)
{
  MPI_File fh = *((MPI_File*) luaL_checkudata(L, 1, "MPI::File"));
  MPI_Offset offset = *((MPI_Offset*) luaL_checkudata(L, 2, "MPI::Offset"));
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); void* buf = (void*) _storage3->data;
  int count = luaL_checkint(L, 4);
  MPI_Datatype datatype = *((MPI_Datatype*) luaL_checkudata(L, 5, "MPI::Datatype"));
  MPI_Status* status = (MPI_Status*) luaL_checkudata(L, 6, "MPI::Status");
  int res = MPI_File_read_at_all(fh, offset, buf, count, datatype, status);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_read_at_all_begin(lua_State *L)
{
  MPI_File fh = *((MPI_File*) luaL_checkudata(L, 1, "MPI::File"));
  MPI_Offset offset = *((MPI_Offset*) luaL_checkudata(L, 2, "MPI::Offset"));
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); void* buf = (void*) _storage3->data;
  int count = luaL_checkint(L, 4);
  MPI_Datatype datatype = *((MPI_Datatype*) luaL_checkudata(L, 5, "MPI::Datatype"));
  int res = MPI_File_read_at_all_begin(fh, offset, buf, count, datatype);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_read_at_all_end(lua_State *L)
{
  MPI_File fh = *((MPI_File*) luaL_checkudata(L, 1, "MPI::File"));
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); void* buf = (void*) _storage2->data;
  MPI_Status* status = (MPI_Status*) luaL_checkudata(L, 3, "MPI::Status");
  int res = MPI_File_read_at_all_end(fh, buf, status);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_read_ordered(lua_State *L)
{
  MPI_File fh = *((MPI_File*) luaL_checkudata(L, 1, "MPI::File"));
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); void* buf = (void*) _storage2->data;
  int count = luaL_checkint(L, 3);
  MPI_Datatype datatype = *((MPI_Datatype*) luaL_checkudata(L, 4, "MPI::Datatype"));
  MPI_Status* status = (MPI_Status*) luaL_checkudata(L, 5, "MPI::Status");
  int res = MPI_File_read_ordered(fh, buf, count, datatype, status);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_read_ordered_begin(lua_State *L)
{
  MPI_File fh = *((MPI_File*) luaL_checkudata(L, 1, "MPI::File"));
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); void* buf = (void*) _storage2->data;
  int count = luaL_checkint(L, 3);
  MPI_Datatype datatype = *((MPI_Datatype*) luaL_checkudata(L, 4, "MPI::Datatype"));
  int res = MPI_File_read_ordered_begin(fh, buf, count, datatype);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_read_ordered_end(lua_State *L)
{
  MPI_File fh = *((MPI_File*) luaL_checkudata(L, 1, "MPI::File"));
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); void* buf = (void*) _storage2->data;
  MPI_Status* status = (MPI_Status*) luaL_checkudata(L, 3, "MPI::Status");
  int res = MPI_File_read_ordered_end(fh, buf, status);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_read_shared(lua_State *L)
{
  MPI_File fh = *((MPI_File*) luaL_checkudata(L, 1, "MPI::File"));
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); void* buf = (void*) _storage2->data;
  int count = luaL_checkint(L, 3);
  MPI_Datatype datatype = *((MPI_Datatype*) luaL_checkudata(L, 4, "MPI::Datatype"));
  MPI_Status* status = (MPI_Status*) luaL_checkudata(L, 5, "MPI::Status");
  int res = MPI_File_read_shared(fh, buf, count, datatype, status);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_seek(lua_State *L)
{
  MPI_File fh = *((MPI_File*) luaL_checkudata(L, 1, "MPI::File"));
  MPI_Offset offset = *((MPI_Offset*) luaL_checkudata(L, 2, "MPI::Offset"));
  int whence = luaL_checkint(L, 3);
  int res = MPI_File_seek(fh, offset, whence);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_seek_shared(lua_State *L)
{
  MPI_File fh = *((MPI_File*) luaL_checkudata(L, 1, "MPI::File"));
  MPI_Offset offset = *((MPI_Offset*) luaL_checkudata(L, 2, "MPI::Offset"));
  int whence = luaL_checkint(L, 3);
  int res = MPI_File_seek_shared(fh, offset, whence);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_set_atomicity(lua_State *L)
{
  MPI_File fh = *((MPI_File*) luaL_checkudata(L, 1, "MPI::File"));
  int flag = luaL_checkint(L, 2);
  int res = MPI_File_set_atomicity(fh, flag);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_set_errhandler(lua_State *L)
{
  MPI_File file = *((MPI_File*) luaL_checkudata(L, 1, "MPI::File"));
  MPI_Errhandler errhandler = *((MPI_Errhandler*) luaL_checkudata(L, 2, "MPI::Errhandler"));
  int res = MPI_File_set_errhandler(file, errhandler);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_set_info(lua_State *L)
{
  MPI_File fh = *((MPI_File*) luaL_checkudata(L, 1, "MPI::File"));
  MPI_Info info = *((MPI_Info*) luaL_checkudata(L, 2, "MPI::Info"));
  int res = MPI_File_set_info(fh, info);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_set_size(lua_State *L)
{
  MPI_File fh = *((MPI_File*) luaL_checkudata(L, 1, "MPI::File"));
  MPI_Offset size = *((MPI_Offset*) luaL_checkudata(L, 2, "MPI::Offset"));
  int res = MPI_File_set_size(fh, size);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_set_view(lua_State *L)
{
  MPI_File fh = *((MPI_File*) luaL_checkudata(L, 1, "MPI::File"));
  MPI_Offset disp = *((MPI_Offset*) luaL_checkudata(L, 2, "MPI::Offset"));
  MPI_Datatype etype = *((MPI_Datatype*) luaL_checkudata(L, 3, "MPI::Datatype"));
  MPI_Datatype filetype = *((MPI_Datatype*) luaL_checkudata(L, 4, "MPI::Datatype"));
  const char *_type5 = luaT_typename(L,5); MPI_THStorage *_storage5 = luaT_toudata(L,5,_type5); char* datarep = (char*) _storage5->data;
  MPI_Info info = *((MPI_Info*) luaL_checkudata(L, 6, "MPI::Info"));
  int res = MPI_File_set_view(fh, disp, etype, filetype, datarep, info);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_sync(lua_State *L)
{
  MPI_File fh = *((MPI_File*) luaL_checkudata(L, 1, "MPI::File"));
  int res = MPI_File_sync(fh);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_write(lua_State *L)
{
  MPI_File fh = *((MPI_File*) luaL_checkudata(L, 1, "MPI::File"));
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); void* buf = (void*) _storage2->data;
  int count = luaL_checkint(L, 3);
  MPI_Datatype datatype = *((MPI_Datatype*) luaL_checkudata(L, 4, "MPI::Datatype"));
  MPI_Status* status = (MPI_Status*) luaL_checkudata(L, 5, "MPI::Status");
  int res = MPI_File_write(fh, buf, count, datatype, status);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_write_all(lua_State *L)
{
  MPI_File fh = *((MPI_File*) luaL_checkudata(L, 1, "MPI::File"));
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); void* buf = (void*) _storage2->data;
  int count = luaL_checkint(L, 3);
  MPI_Datatype datatype = *((MPI_Datatype*) luaL_checkudata(L, 4, "MPI::Datatype"));
  MPI_Status* status = (MPI_Status*) luaL_checkudata(L, 5, "MPI::Status");
  int res = MPI_File_write_all(fh, buf, count, datatype, status);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_write_all_begin(lua_State *L)
{
  MPI_File fh = *((MPI_File*) luaL_checkudata(L, 1, "MPI::File"));
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); void* buf = (void*) _storage2->data;
  int count = luaL_checkint(L, 3);
  MPI_Datatype datatype = *((MPI_Datatype*) luaL_checkudata(L, 4, "MPI::Datatype"));
  int res = MPI_File_write_all_begin(fh, buf, count, datatype);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_write_all_end(lua_State *L)
{
  MPI_File fh = *((MPI_File*) luaL_checkudata(L, 1, "MPI::File"));
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); void* buf = (void*) _storage2->data;
  MPI_Status* status = (MPI_Status*) luaL_checkudata(L, 3, "MPI::Status");
  int res = MPI_File_write_all_end(fh, buf, status);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_write_at(lua_State *L)
{
  MPI_File fh = *((MPI_File*) luaL_checkudata(L, 1, "MPI::File"));
  MPI_Offset offset = *((MPI_Offset*) luaL_checkudata(L, 2, "MPI::Offset"));
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); void* buf = (void*) _storage3->data;
  int count = luaL_checkint(L, 4);
  MPI_Datatype datatype = *((MPI_Datatype*) luaL_checkudata(L, 5, "MPI::Datatype"));
  MPI_Status* status = (MPI_Status*) luaL_checkudata(L, 6, "MPI::Status");
  int res = MPI_File_write_at(fh, offset, buf, count, datatype, status);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_write_at_all(lua_State *L)
{
  MPI_File fh = *((MPI_File*) luaL_checkudata(L, 1, "MPI::File"));
  MPI_Offset offset = *((MPI_Offset*) luaL_checkudata(L, 2, "MPI::Offset"));
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); void* buf = (void*) _storage3->data;
  int count = luaL_checkint(L, 4);
  MPI_Datatype datatype = *((MPI_Datatype*) luaL_checkudata(L, 5, "MPI::Datatype"));
  MPI_Status* status = (MPI_Status*) luaL_checkudata(L, 6, "MPI::Status");
  int res = MPI_File_write_at_all(fh, offset, buf, count, datatype, status);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_write_at_all_begin(lua_State *L)
{
  MPI_File fh = *((MPI_File*) luaL_checkudata(L, 1, "MPI::File"));
  MPI_Offset offset = *((MPI_Offset*) luaL_checkudata(L, 2, "MPI::Offset"));
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); void* buf = (void*) _storage3->data;
  int count = luaL_checkint(L, 4);
  MPI_Datatype datatype = *((MPI_Datatype*) luaL_checkudata(L, 5, "MPI::Datatype"));
  int res = MPI_File_write_at_all_begin(fh, offset, buf, count, datatype);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_write_at_all_end(lua_State *L)
{
  MPI_File fh = *((MPI_File*) luaL_checkudata(L, 1, "MPI::File"));
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); void* buf = (void*) _storage2->data;
  MPI_Status* status = (MPI_Status*) luaL_checkudata(L, 3, "MPI::Status");
  int res = MPI_File_write_at_all_end(fh, buf, status);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_write_ordered(lua_State *L)
{
  MPI_File fh = *((MPI_File*) luaL_checkudata(L, 1, "MPI::File"));
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); void* buf = (void*) _storage2->data;
  int count = luaL_checkint(L, 3);
  MPI_Datatype datatype = *((MPI_Datatype*) luaL_checkudata(L, 4, "MPI::Datatype"));
  MPI_Status* status = (MPI_Status*) luaL_checkudata(L, 5, "MPI::Status");
  int res = MPI_File_write_ordered(fh, buf, count, datatype, status);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_write_ordered_begin(lua_State *L)
{
  MPI_File fh = *((MPI_File*) luaL_checkudata(L, 1, "MPI::File"));
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); void* buf = (void*) _storage2->data;
  int count = luaL_checkint(L, 3);
  MPI_Datatype datatype = *((MPI_Datatype*) luaL_checkudata(L, 4, "MPI::Datatype"));
  int res = MPI_File_write_ordered_begin(fh, buf, count, datatype);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_write_ordered_end(lua_State *L)
{
  MPI_File fh = *((MPI_File*) luaL_checkudata(L, 1, "MPI::File"));
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); void* buf = (void*) _storage2->data;
  MPI_Status* status = (MPI_Status*) luaL_checkudata(L, 3, "MPI::Status");
  int res = MPI_File_write_ordered_end(fh, buf, status);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_File_write_shared(lua_State *L)
{
  MPI_File fh = *((MPI_File*) luaL_checkudata(L, 1, "MPI::File"));
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); void* buf = (void*) _storage2->data;
  int count = luaL_checkint(L, 3);
  MPI_Datatype datatype = *((MPI_Datatype*) luaL_checkudata(L, 4, "MPI::Datatype"));
  MPI_Status* status = (MPI_Status*) luaL_checkudata(L, 5, "MPI::Status");
  int res = MPI_File_write_shared(fh, buf, count, datatype, status);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Finalize(lua_State *L)
{
  // no Lua args
  int res = MPI_Finalize();
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Finalized(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); int* flag = (int*) _storage1->data;
  int res = MPI_Finalized(flag);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Free_mem(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); void* baseptr = (void*) _storage1->data;
  int res = MPI_Free_mem(baseptr);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Gather(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); void* sendbuf = (void*) _storage1->data;
  int sendcount = luaL_checkint(L, 2);
  MPI_Datatype sendtype = *((MPI_Datatype*) luaL_checkudata(L, 3, "MPI::Datatype"));
  const char *_type4 = luaT_typename(L,4); MPI_THStorage *_storage4 = luaT_toudata(L,4,_type4); void* recvbuf = (void*) _storage4->data;
  int recvcount = luaL_checkint(L, 5);
  MPI_Datatype recvtype = *((MPI_Datatype*) luaL_checkudata(L, 6, "MPI::Datatype"));
  int root = luaL_checkint(L, 7);
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 8, "MPI::Comm"));
  int res = MPI_Gather(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Gatherv(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); void* sendbuf = (void*) _storage1->data;
  int sendcount = luaL_checkint(L, 2);
  MPI_Datatype sendtype = *((MPI_Datatype*) luaL_checkudata(L, 3, "MPI::Datatype"));
  const char *_type4 = luaT_typename(L,4); MPI_THStorage *_storage4 = luaT_toudata(L,4,_type4); void* recvbuf = (void*) _storage4->data;
  const char *_type5 = luaT_typename(L,5); MPI_THStorage *_storage5 = luaT_toudata(L,5,_type5); int* recvcounts = (int*) _storage5->data;
  const char *_type6 = luaT_typename(L,6); MPI_THStorage *_storage6 = luaT_toudata(L,6,_type6); int* displs = (int*) _storage6->data;
  MPI_Datatype recvtype = *((MPI_Datatype*) luaL_checkudata(L, 7, "MPI::Datatype"));
  int root = luaL_checkint(L, 8);
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 9, "MPI::Comm"));
  int res = MPI_Gatherv(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, root, comm);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Get(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); void* origin_addr = (void*) _storage1->data;
  int origin_count = luaL_checkint(L, 2);
  MPI_Datatype origin_datatype = *((MPI_Datatype*) luaL_checkudata(L, 3, "MPI::Datatype"));
  int target_rank = luaL_checkint(L, 4);
  MPI_Aint target_disp = *((MPI_Aint*) luaL_checkudata(L, 5, "MPI::Aint"));
  int target_count = luaL_checkint(L, 6);
  MPI_Datatype target_datatype = *((MPI_Datatype*) luaL_checkudata(L, 7, "MPI::Datatype"));
  MPI_Win win = *((MPI_Win*) luaL_checkudata(L, 8, "MPI::Win"));
  int res = MPI_Get(origin_addr, origin_count, origin_datatype, target_rank, target_disp, target_count, target_datatype, win);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Get_address(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); void* location = (void*) _storage1->data;
  MPI_Aint* address = (MPI_Aint*) luaL_checkudata(L, 2, "MPI::Aint");
  int res = MPI_Get_address(location, address);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Get_count(lua_State *L)
{
  MPI_Status* status = (MPI_Status*) luaL_checkudata(L, 1, "MPI::Status");
  MPI_Datatype datatype = *((MPI_Datatype*) luaL_checkudata(L, 2, "MPI::Datatype"));
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); int* count = (int*) _storage3->data;
  int res = MPI_Get_count(status, datatype, count);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Get_elements(lua_State *L)
{
  MPI_Status* status = (MPI_Status*) luaL_checkudata(L, 1, "MPI::Status");
  MPI_Datatype datatype = *((MPI_Datatype*) luaL_checkudata(L, 2, "MPI::Datatype"));
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); int* count = (int*) _storage3->data;
  int res = MPI_Get_elements(status, datatype, count);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Get_processor_name(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); char* name = (char*) _storage1->data;
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); int* resultlen = (int*) _storage2->data;
  int res = MPI_Get_processor_name(name, resultlen);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Get_version(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); int* version = (int*) _storage1->data;
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); int* subversion = (int*) _storage2->data;
  int res = MPI_Get_version(version, subversion);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Graph_create(lua_State *L)
{
  MPI_Comm old_comm = *((MPI_Comm*) luaL_checkudata(L, 1, "MPI::Comm"));
  int nnodes = luaL_checkint(L, 2);
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); int* index = (int*) _storage3->data;
  const char *_type4 = luaT_typename(L,4); MPI_THStorage *_storage4 = luaT_toudata(L,4,_type4); int* edges = (int*) _storage4->data;
  int reorder = luaL_checkint(L, 5);
  MPI_Comm* comm_graph = (MPI_Comm*) luaL_checkudata(L, 6, "MPI::Comm");
  int res = MPI_Graph_create(old_comm, nnodes, index, edges, reorder, comm_graph);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Graph_get(lua_State *L)
{
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 1, "MPI::Comm"));
  int maxindex = luaL_checkint(L, 2);
  int maxedges = luaL_checkint(L, 3);
  const char *_type4 = luaT_typename(L,4); MPI_THStorage *_storage4 = luaT_toudata(L,4,_type4); int* index = (int*) _storage4->data;
  const char *_type5 = luaT_typename(L,5); MPI_THStorage *_storage5 = luaT_toudata(L,5,_type5); int* edges = (int*) _storage5->data;
  int res = MPI_Graph_get(comm, maxindex, maxedges, index, edges);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Graph_map(lua_State *L)
{
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 1, "MPI::Comm"));
  int nnodes = luaL_checkint(L, 2);
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); int* index = (int*) _storage3->data;
  const char *_type4 = luaT_typename(L,4); MPI_THStorage *_storage4 = luaT_toudata(L,4,_type4); int* edges = (int*) _storage4->data;
  const char *_type5 = luaT_typename(L,5); MPI_THStorage *_storage5 = luaT_toudata(L,5,_type5); int* newrank = (int*) _storage5->data;
  int res = MPI_Graph_map(comm, nnodes, index, edges, newrank);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Graph_neighbors(lua_State *L)
{
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 1, "MPI::Comm"));
  int rank = luaL_checkint(L, 2);
  int maxneighbors = luaL_checkint(L, 3);
  const char *_type4 = luaT_typename(L,4); MPI_THStorage *_storage4 = luaT_toudata(L,4,_type4); int* neighbors = (int*) _storage4->data;
  int res = MPI_Graph_neighbors(comm, rank, maxneighbors, neighbors);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Graph_neighbors_count(lua_State *L)
{
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 1, "MPI::Comm"));
  int rank = luaL_checkint(L, 2);
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); int* nneighbors = (int*) _storage3->data;
  int res = MPI_Graph_neighbors_count(comm, rank, nneighbors);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Graphdims_get(lua_State *L)
{
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 1, "MPI::Comm"));
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); int* nnodes = (int*) _storage2->data;
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); int* nedges = (int*) _storage3->data;
  int res = MPI_Graphdims_get(comm, nnodes, nedges);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Grequest_complete(lua_State *L)
{
  MPI_Request request = *((MPI_Request*) luaL_checkudata(L, 1, "MPI::Request"));
  int res = MPI_Grequest_complete(request);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Grequest_start(lua_State *L)
{
  MPI_Grequest_query_function* query_fn = (MPI_Grequest_query_function*) luaL_checkudata(L, 1, "MPI::Grequest_query_function");
  MPI_Grequest_free_function* free_fn = (MPI_Grequest_free_function*) luaL_checkudata(L, 2, "MPI::Grequest_free_function");
  MPI_Grequest_cancel_function* cancel_fn = (MPI_Grequest_cancel_function*) luaL_checkudata(L, 3, "MPI::Grequest_cancel_function");
  const char *_type4 = luaT_typename(L,4); MPI_THStorage *_storage4 = luaT_toudata(L,4,_type4); void* extra_state = (void*) _storage4->data;
  MPI_Request* request = (MPI_Request*) luaL_checkudata(L, 5, "MPI::Request");
  int res = MPI_Grequest_start(query_fn, free_fn, cancel_fn, extra_state, request);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Group_compare(lua_State *L)
{
  MPI_Group group1 = *((MPI_Group*) luaL_checkudata(L, 1, "MPI::Group"));
  MPI_Group group2 = *((MPI_Group*) luaL_checkudata(L, 2, "MPI::Group"));
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); int* result = (int*) _storage3->data;
  int res = MPI_Group_compare(group1, group2, result);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Group_difference(lua_State *L)
{
  MPI_Group group1 = *((MPI_Group*) luaL_checkudata(L, 1, "MPI::Group"));
  MPI_Group group2 = *((MPI_Group*) luaL_checkudata(L, 2, "MPI::Group"));
  MPI_Group* new_group = (MPI_Group*) luaL_checkudata(L, 3, "MPI::Group");
  int res = MPI_Group_difference(group1, group2, new_group);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Group_excl(lua_State *L)
{
  MPI_Group group = *((MPI_Group*) luaL_checkudata(L, 1, "MPI::Group"));
  int n = luaL_checkint(L, 2);
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); int* ranks = (int*) _storage3->data;
  MPI_Group* new_group = (MPI_Group*) luaL_checkudata(L, 4, "MPI::Group");
  int res = MPI_Group_excl(group, n, ranks, new_group);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Group_free(lua_State *L)
{
  MPI_Group* group = (MPI_Group*) luaL_checkudata(L, 1, "MPI::Group");
  int res = MPI_Group_free(group);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Group_incl(lua_State *L)
{
  MPI_Group group = *((MPI_Group*) luaL_checkudata(L, 1, "MPI::Group"));
  int n = luaL_checkint(L, 2);
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); int* ranks = (int*) _storage3->data;
  MPI_Group* new_group = (MPI_Group*) luaL_checkudata(L, 4, "MPI::Group");
  int res = MPI_Group_incl(group, n, ranks, new_group);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Group_intersection(lua_State *L)
{
  MPI_Group group1 = *((MPI_Group*) luaL_checkudata(L, 1, "MPI::Group"));
  MPI_Group group2 = *((MPI_Group*) luaL_checkudata(L, 2, "MPI::Group"));
  MPI_Group* new_group = (MPI_Group*) luaL_checkudata(L, 3, "MPI::Group");
  int res = MPI_Group_intersection(group1, group2, new_group);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Group_rank(lua_State *L)
{
  MPI_Group group = *((MPI_Group*) luaL_checkudata(L, 1, "MPI::Group"));
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); int* rank = (int*) _storage2->data;
  int res = MPI_Group_rank(group, rank);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Group_size(lua_State *L)
{
  MPI_Group group = *((MPI_Group*) luaL_checkudata(L, 1, "MPI::Group"));
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); int* size = (int*) _storage2->data;
  int res = MPI_Group_size(group, size);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Group_translate_ranks(lua_State *L)
{
  MPI_Group group1 = *((MPI_Group*) luaL_checkudata(L, 1, "MPI::Group"));
  int n_ranks = luaL_checkint(L, 2);
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); int* ranks1 = (int*) _storage3->data;
  MPI_Group group2 = *((MPI_Group*) luaL_checkudata(L, 4, "MPI::Group"));
  const char *_type5 = luaT_typename(L,5); MPI_THStorage *_storage5 = luaT_toudata(L,5,_type5); int* ranks2 = (int*) _storage5->data;
  int res = MPI_Group_translate_ranks(group1, n_ranks, ranks1, group2, ranks2);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Group_union(lua_State *L)
{
  MPI_Group group1 = *((MPI_Group*) luaL_checkudata(L, 1, "MPI::Group"));
  MPI_Group group2 = *((MPI_Group*) luaL_checkudata(L, 2, "MPI::Group"));
  MPI_Group* new_group = (MPI_Group*) luaL_checkudata(L, 3, "MPI::Group");
  int res = MPI_Group_union(group1, group2, new_group);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Iallreduce(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); void* sendbuf = (void*) _storage1->data;
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); void* recvbuf = (void*) _storage2->data;
  int count = luaL_checkint(L, 3);
  MPI_Datatype datatype = *((MPI_Datatype*) luaL_checkudata(L, 4, "MPI::Datatype"));
  MPI_Op op = *((MPI_Op*) luaL_checkudata(L, 5, "MPI::Op"));
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 6, "MPI::Comm"));
  MPI_Request* request = (MPI_Request*) luaL_checkudata(L, 7, "MPI::Request");
  int res = MPI_Iallreduce(sendbuf, recvbuf, count, datatype, op, comm, request);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Ibsend(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); void* buf = (void*) _storage1->data;
  int count = luaL_checkint(L, 2);
  MPI_Datatype type = *((MPI_Datatype*) luaL_checkudata(L, 3, "MPI::Datatype"));
  int dest = luaL_checkint(L, 4);
  int tag = luaL_checkint(L, 5);
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 6, "MPI::Comm"));
  MPI_Request* request = (MPI_Request*) luaL_checkudata(L, 7, "MPI::Request");
  int res = MPI_Ibsend(buf, count, type, dest, tag, comm, request);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Info_create(lua_State *L)
{
  MPI_Info* info = (MPI_Info*) luaL_checkudata(L, 1, "MPI::Info");
  int res = MPI_Info_create(info);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Info_delete(lua_State *L)
{
  MPI_Info info = *((MPI_Info*) luaL_checkudata(L, 1, "MPI::Info"));
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); char* key = (char*) _storage2->data;
  int res = MPI_Info_delete(info, key);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Info_dup(lua_State *L)
{
  MPI_Info info = *((MPI_Info*) luaL_checkudata(L, 1, "MPI::Info"));
  MPI_Info* newinfo = (MPI_Info*) luaL_checkudata(L, 2, "MPI::Info");
  int res = MPI_Info_dup(info, newinfo);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Info_free(lua_State *L)
{
  MPI_Info* info = (MPI_Info*) luaL_checkudata(L, 1, "MPI::Info");
  int res = MPI_Info_free(info);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Info_get(lua_State *L)
{
  MPI_Info info = *((MPI_Info*) luaL_checkudata(L, 1, "MPI::Info"));
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); char* key = (char*) _storage2->data;
  int valuelen = luaL_checkint(L, 3);
  const char *_type4 = luaT_typename(L,4); MPI_THStorage *_storage4 = luaT_toudata(L,4,_type4); char* value = (char*) _storage4->data;
  const char *_type5 = luaT_typename(L,5); MPI_THStorage *_storage5 = luaT_toudata(L,5,_type5); int* flag = (int*) _storage5->data;
  int res = MPI_Info_get(info, key, valuelen, value, flag);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Info_get_nkeys(lua_State *L)
{
  MPI_Info info = *((MPI_Info*) luaL_checkudata(L, 1, "MPI::Info"));
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); int* nkeys = (int*) _storage2->data;
  int res = MPI_Info_get_nkeys(info, nkeys);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Info_get_nthkey(lua_State *L)
{
  MPI_Info info = *((MPI_Info*) luaL_checkudata(L, 1, "MPI::Info"));
  int n = luaL_checkint(L, 2);
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); char* key = (char*) _storage3->data;
  int res = MPI_Info_get_nthkey(info, n, key);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Info_get_valuelen(lua_State *L)
{
  MPI_Info info = *((MPI_Info*) luaL_checkudata(L, 1, "MPI::Info"));
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); char* key = (char*) _storage2->data;
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); int* valuelen = (int*) _storage3->data;
  const char *_type4 = luaT_typename(L,4); MPI_THStorage *_storage4 = luaT_toudata(L,4,_type4); int* flag = (int*) _storage4->data;
  int res = MPI_Info_get_valuelen(info, key, valuelen, flag);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Info_set(lua_State *L)
{
  MPI_Info info = *((MPI_Info*) luaL_checkudata(L, 1, "MPI::Info"));
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); char* key = (char*) _storage2->data;
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); char* value = (char*) _storage3->data;
  int res = MPI_Info_set(info, key, value);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Initialized(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); int* flag = (int*) _storage1->data;
  int res = MPI_Initialized(flag);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Intercomm_create(lua_State *L)
{
  MPI_Comm local_comm = *((MPI_Comm*) luaL_checkudata(L, 1, "MPI::Comm"));
  int local_leader = luaL_checkint(L, 2);
  MPI_Comm bridge_comm = *((MPI_Comm*) luaL_checkudata(L, 3, "MPI::Comm"));
  int remote_leader = luaL_checkint(L, 4);
  int tag = luaL_checkint(L, 5);
  MPI_Comm* newintercomm = (MPI_Comm*) luaL_checkudata(L, 6, "MPI::Comm");
  int res = MPI_Intercomm_create(local_comm, local_leader, bridge_comm, remote_leader, tag, newintercomm);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Intercomm_merge(lua_State *L)
{
  MPI_Comm intercomm = *((MPI_Comm*) luaL_checkudata(L, 1, "MPI::Comm"));
  int high = luaL_checkint(L, 2);
  MPI_Comm* newcomm = (MPI_Comm*) luaL_checkudata(L, 3, "MPI::Comm");
  int res = MPI_Intercomm_merge(intercomm, high, newcomm);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Iprobe(lua_State *L)
{
  int source = luaL_checkint(L, 1);
  int tag = luaL_checkint(L, 2);
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 3, "MPI::Comm"));
  const char *_type4 = luaT_typename(L,4); MPI_THStorage *_storage4 = luaT_toudata(L,4,_type4); int* flag = (int*) _storage4->data;
  MPI_Status* status = (MPI_Status*) luaL_checkudata(L, 5, "MPI::Status");
  int res = MPI_Iprobe(source, tag, comm, flag, status);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Irecv(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); void* buf = (void*) _storage1->data;
  int count = luaL_checkint(L, 2);
  MPI_Datatype type = *((MPI_Datatype*) luaL_checkudata(L, 3, "MPI::Datatype"));
  int source = luaL_checkint(L, 4);
  int tag = luaL_checkint(L, 5);
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 6, "MPI::Comm"));
  MPI_Request* request = (MPI_Request*) luaL_checkudata(L, 7, "MPI::Request");
  int res = MPI_Irecv(buf, count, type, source, tag, comm, request);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Irsend(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); void* buf = (void*) _storage1->data;
  int count = luaL_checkint(L, 2);
  MPI_Datatype type = *((MPI_Datatype*) luaL_checkudata(L, 3, "MPI::Datatype"));
  int dest = luaL_checkint(L, 4);
  int tag = luaL_checkint(L, 5);
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 6, "MPI::Comm"));
  MPI_Request* request = (MPI_Request*) luaL_checkudata(L, 7, "MPI::Request");
  int res = MPI_Irsend(buf, count, type, dest, tag, comm, request);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Is_thread_main(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); int* flag = (int*) _storage1->data;
  int res = MPI_Is_thread_main(flag);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Isend(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); void* buf = (void*) _storage1->data;
  int count = luaL_checkint(L, 2);
  MPI_Datatype type = *((MPI_Datatype*) luaL_checkudata(L, 3, "MPI::Datatype"));
  int dest = luaL_checkint(L, 4);
  int tag = luaL_checkint(L, 5);
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 6, "MPI::Comm"));
  MPI_Request* request = (MPI_Request*) luaL_checkudata(L, 7, "MPI::Request");
  int res = MPI_Isend(buf, count, type, dest, tag, comm, request);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Issend(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); void* buf = (void*) _storage1->data;
  int count = luaL_checkint(L, 2);
  MPI_Datatype type = *((MPI_Datatype*) luaL_checkudata(L, 3, "MPI::Datatype"));
  int dest = luaL_checkint(L, 4);
  int tag = luaL_checkint(L, 5);
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 6, "MPI::Comm"));
  MPI_Request* request = (MPI_Request*) luaL_checkudata(L, 7, "MPI::Request");
  int res = MPI_Issend(buf, count, type, dest, tag, comm, request);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Lookup_name(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); char* service_name = (char*) _storage1->data;
  MPI_Info info = *((MPI_Info*) luaL_checkudata(L, 2, "MPI::Info"));
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); char* port_name = (char*) _storage3->data;
  int res = MPI_Lookup_name(service_name, info, port_name);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Op_create(lua_State *L)
{
  MPI_User_function* function = (MPI_User_function*) luaL_checkudata(L, 1, "MPI::User_function");
  int commute = luaL_checkint(L, 2);
  MPI_Op* op = (MPI_Op*) luaL_checkudata(L, 3, "MPI::Op");
  int res = MPI_Op_create(function, commute, op);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Op_free(lua_State *L)
{
  MPI_Op* op = (MPI_Op*) luaL_checkudata(L, 1, "MPI::Op");
  int res = MPI_Op_free(op);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Open_port(lua_State *L)
{
  MPI_Info info = *((MPI_Info*) luaL_checkudata(L, 1, "MPI::Info"));
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); char* port_name = (char*) _storage2->data;
  int res = MPI_Open_port(info, port_name);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Pack(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); void* inbuf = (void*) _storage1->data;
  int incount = luaL_checkint(L, 2);
  MPI_Datatype datatype = *((MPI_Datatype*) luaL_checkudata(L, 3, "MPI::Datatype"));
  const char *_type4 = luaT_typename(L,4); MPI_THStorage *_storage4 = luaT_toudata(L,4,_type4); void* outbuf = (void*) _storage4->data;
  int outsize = luaL_checkint(L, 5);
  const char *_type6 = luaT_typename(L,6); MPI_THStorage *_storage6 = luaT_toudata(L,6,_type6); int* position = (int*) _storage6->data;
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 7, "MPI::Comm"));
  int res = MPI_Pack(inbuf, incount, datatype, outbuf, outsize, position, comm);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Pack_external(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); char* datarep = (char*) _storage1->data;
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); void* inbuf = (void*) _storage2->data;
  int incount = luaL_checkint(L, 3);
  MPI_Datatype datatype = *((MPI_Datatype*) luaL_checkudata(L, 4, "MPI::Datatype"));
  const char *_type5 = luaT_typename(L,5); MPI_THStorage *_storage5 = luaT_toudata(L,5,_type5); void* outbuf = (void*) _storage5->data;
  MPI_Aint outsize = *((MPI_Aint*) luaL_checkudata(L, 6, "MPI::Aint"));
  MPI_Aint* position = (MPI_Aint*) luaL_checkudata(L, 7, "MPI::Aint");
  int res = MPI_Pack_external(datarep, inbuf, incount, datatype, outbuf, outsize, position);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Pack_external_size(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); char* datarep = (char*) _storage1->data;
  int incount = luaL_checkint(L, 2);
  MPI_Datatype datatype = *((MPI_Datatype*) luaL_checkudata(L, 3, "MPI::Datatype"));
  MPI_Aint* size = (MPI_Aint*) luaL_checkudata(L, 4, "MPI::Aint");
  int res = MPI_Pack_external_size(datarep, incount, datatype, size);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Pack_size(lua_State *L)
{
  int incount = luaL_checkint(L, 1);
  MPI_Datatype datatype = *((MPI_Datatype*) luaL_checkudata(L, 2, "MPI::Datatype"));
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 3, "MPI::Comm"));
  const char *_type4 = luaT_typename(L,4); MPI_THStorage *_storage4 = luaT_toudata(L,4,_type4); int* size = (int*) _storage4->data;
  int res = MPI_Pack_size(incount, datatype, comm, size);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Probe(lua_State *L)
{
  int source = luaL_checkint(L, 1);
  int tag = luaL_checkint(L, 2);
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 3, "MPI::Comm"));
  MPI_Status* status = (MPI_Status*) luaL_checkudata(L, 4, "MPI::Status");
  int res = MPI_Probe(source, tag, comm, status);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Publish_name(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); char* service_name = (char*) _storage1->data;
  MPI_Info info = *((MPI_Info*) luaL_checkudata(L, 2, "MPI::Info"));
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); char* port_name = (char*) _storage3->data;
  int res = MPI_Publish_name(service_name, info, port_name);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Put(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); void* origin_addr = (void*) _storage1->data;
  int origin_count = luaL_checkint(L, 2);
  MPI_Datatype origin_datatype = *((MPI_Datatype*) luaL_checkudata(L, 3, "MPI::Datatype"));
  int target_rank = luaL_checkint(L, 4);
  MPI_Aint target_disp = *((MPI_Aint*) luaL_checkudata(L, 5, "MPI::Aint"));
  int target_count = luaL_checkint(L, 6);
  MPI_Datatype target_datatype = *((MPI_Datatype*) luaL_checkudata(L, 7, "MPI::Datatype"));
  MPI_Win win = *((MPI_Win*) luaL_checkudata(L, 8, "MPI::Win"));
  int res = MPI_Put(origin_addr, origin_count, origin_datatype, target_rank, target_disp, target_count, target_datatype, win);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Query_thread(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); int* provided = (int*) _storage1->data;
  int res = MPI_Query_thread(provided);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Recv(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); void* buf = (void*) _storage1->data;
  int count = luaL_checkint(L, 2);
  MPI_Datatype type = *((MPI_Datatype*) luaL_checkudata(L, 3, "MPI::Datatype"));
  int source = luaL_checkint(L, 4);
  int tag = luaL_checkint(L, 5);
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 6, "MPI::Comm"));
  MPI_Status* status = (MPI_Status*) luaL_checkudata(L, 7, "MPI::Status");
  int res = MPI_Recv(buf, count, type, source, tag, comm, status);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Recv_init(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); void* buf = (void*) _storage1->data;
  int count = luaL_checkint(L, 2);
  MPI_Datatype type = *((MPI_Datatype*) luaL_checkudata(L, 3, "MPI::Datatype"));
  int source = luaL_checkint(L, 4);
  int tag = luaL_checkint(L, 5);
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 6, "MPI::Comm"));
  MPI_Request* request = (MPI_Request*) luaL_checkudata(L, 7, "MPI::Request");
  int res = MPI_Recv_init(buf, count, type, source, tag, comm, request);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Reduce(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); void* sendbuf = (void*) _storage1->data;
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); void* recvbuf = (void*) _storage2->data;
  int count = luaL_checkint(L, 3);
  MPI_Datatype datatype = *((MPI_Datatype*) luaL_checkudata(L, 4, "MPI::Datatype"));
  MPI_Op op = *((MPI_Op*) luaL_checkudata(L, 5, "MPI::Op"));
  int root = luaL_checkint(L, 6);
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 7, "MPI::Comm"));
  int res = MPI_Reduce(sendbuf, recvbuf, count, datatype, op, root, comm);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Reduce_scatter(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); void* sendbuf = (void*) _storage1->data;
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); void* recvbuf = (void*) _storage2->data;
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); int* recvcounts = (int*) _storage3->data;
  MPI_Datatype datatype = *((MPI_Datatype*) luaL_checkudata(L, 4, "MPI::Datatype"));
  MPI_Op op = *((MPI_Op*) luaL_checkudata(L, 5, "MPI::Op"));
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 6, "MPI::Comm"));
  int res = MPI_Reduce_scatter(sendbuf, recvbuf, recvcounts, datatype, op, comm);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Register_datarep(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); char* datarep = (char*) _storage1->data;
  MPI_Datarep_conversion_function* read_conversion_fn = (MPI_Datarep_conversion_function*) luaL_checkudata(L, 2, "MPI::Datarep_conversion_function");
  MPI_Datarep_conversion_function* write_conversion_fn = (MPI_Datarep_conversion_function*) luaL_checkudata(L, 3, "MPI::Datarep_conversion_function");
  MPI_Datarep_extent_function* dtype_file_extent_fn = (MPI_Datarep_extent_function*) luaL_checkudata(L, 4, "MPI::Datarep_extent_function");
  const char *_type5 = luaT_typename(L,5); MPI_THStorage *_storage5 = luaT_toudata(L,5,_type5); void* extra_state = (void*) _storage5->data;
  int res = MPI_Register_datarep(datarep, read_conversion_fn, write_conversion_fn, dtype_file_extent_fn, extra_state);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Request_free(lua_State *L)
{
  MPI_Request* request = (MPI_Request*) luaL_checkudata(L, 1, "MPI::Request");
  int res = MPI_Request_free(request);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Request_get_status(lua_State *L)
{
  MPI_Request request = *((MPI_Request*) luaL_checkudata(L, 1, "MPI::Request"));
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); int* flag = (int*) _storage2->data;
  MPI_Status* status = (MPI_Status*) luaL_checkudata(L, 3, "MPI::Status");
  int res = MPI_Request_get_status(request, flag, status);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Rsend(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); void* buf = (void*) _storage1->data;
  int count = luaL_checkint(L, 2);
  MPI_Datatype type = *((MPI_Datatype*) luaL_checkudata(L, 3, "MPI::Datatype"));
  int dest = luaL_checkint(L, 4);
  int tag = luaL_checkint(L, 5);
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 6, "MPI::Comm"));
  int res = MPI_Rsend(buf, count, type, dest, tag, comm);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Rsend_init(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); void* buf = (void*) _storage1->data;
  int count = luaL_checkint(L, 2);
  MPI_Datatype type = *((MPI_Datatype*) luaL_checkudata(L, 3, "MPI::Datatype"));
  int dest = luaL_checkint(L, 4);
  int tag = luaL_checkint(L, 5);
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 6, "MPI::Comm"));
  MPI_Request* request = (MPI_Request*) luaL_checkudata(L, 7, "MPI::Request");
  int res = MPI_Rsend_init(buf, count, type, dest, tag, comm, request);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Scan(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); void* sendbuf = (void*) _storage1->data;
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); void* recvbuf = (void*) _storage2->data;
  int count = luaL_checkint(L, 3);
  MPI_Datatype datatype = *((MPI_Datatype*) luaL_checkudata(L, 4, "MPI::Datatype"));
  MPI_Op op = *((MPI_Op*) luaL_checkudata(L, 5, "MPI::Op"));
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 6, "MPI::Comm"));
  int res = MPI_Scan(sendbuf, recvbuf, count, datatype, op, comm);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Scatter(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); void* sendbuf = (void*) _storage1->data;
  int sendcount = luaL_checkint(L, 2);
  MPI_Datatype sendtype = *((MPI_Datatype*) luaL_checkudata(L, 3, "MPI::Datatype"));
  const char *_type4 = luaT_typename(L,4); MPI_THStorage *_storage4 = luaT_toudata(L,4,_type4); void* recvbuf = (void*) _storage4->data;
  int recvcount = luaL_checkint(L, 5);
  MPI_Datatype recvtype = *((MPI_Datatype*) luaL_checkudata(L, 6, "MPI::Datatype"));
  int root = luaL_checkint(L, 7);
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 8, "MPI::Comm"));
  int res = MPI_Scatter(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Scatterv(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); void* sendbuf = (void*) _storage1->data;
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); int* sendcounts = (int*) _storage2->data;
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); int* displs = (int*) _storage3->data;
  MPI_Datatype sendtype = *((MPI_Datatype*) luaL_checkudata(L, 4, "MPI::Datatype"));
  const char *_type5 = luaT_typename(L,5); MPI_THStorage *_storage5 = luaT_toudata(L,5,_type5); void* recvbuf = (void*) _storage5->data;
  int recvcount = luaL_checkint(L, 6);
  MPI_Datatype recvtype = *((MPI_Datatype*) luaL_checkudata(L, 7, "MPI::Datatype"));
  int root = luaL_checkint(L, 8);
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 9, "MPI::Comm"));
  int res = MPI_Scatterv(sendbuf, sendcounts, displs, sendtype, recvbuf, recvcount, recvtype, root, comm);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Send(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); void* buf = (void*) _storage1->data;
  int count = luaL_checkint(L, 2);
  MPI_Datatype type = *((MPI_Datatype*) luaL_checkudata(L, 3, "MPI::Datatype"));
  int dest = luaL_checkint(L, 4);
  int tag = luaL_checkint(L, 5);
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 6, "MPI::Comm"));
  int res = MPI_Send(buf, count, type, dest, tag, comm);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Send_init(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); void* buf = (void*) _storage1->data;
  int count = luaL_checkint(L, 2);
  MPI_Datatype type = *((MPI_Datatype*) luaL_checkudata(L, 3, "MPI::Datatype"));
  int dest = luaL_checkint(L, 4);
  int tag = luaL_checkint(L, 5);
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 6, "MPI::Comm"));
  MPI_Request* request = (MPI_Request*) luaL_checkudata(L, 7, "MPI::Request");
  int res = MPI_Send_init(buf, count, type, dest, tag, comm, request);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Sendrecv(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); void* sendbuf = (void*) _storage1->data;
  int sendcount = luaL_checkint(L, 2);
  MPI_Datatype sendtype = *((MPI_Datatype*) luaL_checkudata(L, 3, "MPI::Datatype"));
  int dest = luaL_checkint(L, 4);
  int sendtag = luaL_checkint(L, 5);
  const char *_type6 = luaT_typename(L,6); MPI_THStorage *_storage6 = luaT_toudata(L,6,_type6); void* recvbuf = (void*) _storage6->data;
  int recvcount = luaL_checkint(L, 7);
  MPI_Datatype recvtype = *((MPI_Datatype*) luaL_checkudata(L, 8, "MPI::Datatype"));
  int source = luaL_checkint(L, 9);
  int recvtag = luaL_checkint(L, 10);
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 11, "MPI::Comm"));
  MPI_Status* status = (MPI_Status*) luaL_checkudata(L, 12, "MPI::Status");
  int res = MPI_Sendrecv(sendbuf, sendcount, sendtype, dest, sendtag, recvbuf, recvcount, recvtype, source, recvtag, comm, status);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Sendrecv_replace(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); void* buf = (void*) _storage1->data;
  int count = luaL_checkint(L, 2);
  MPI_Datatype datatype = *((MPI_Datatype*) luaL_checkudata(L, 3, "MPI::Datatype"));
  int dest = luaL_checkint(L, 4);
  int sendtag = luaL_checkint(L, 5);
  int source = luaL_checkint(L, 6);
  int recvtag = luaL_checkint(L, 7);
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 8, "MPI::Comm"));
  MPI_Status* status = (MPI_Status*) luaL_checkudata(L, 9, "MPI::Status");
  int res = MPI_Sendrecv_replace(buf, count, datatype, dest, sendtag, source, recvtag, comm, status);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Ssend(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); void* buf = (void*) _storage1->data;
  int count = luaL_checkint(L, 2);
  MPI_Datatype type = *((MPI_Datatype*) luaL_checkudata(L, 3, "MPI::Datatype"));
  int dest = luaL_checkint(L, 4);
  int tag = luaL_checkint(L, 5);
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 6, "MPI::Comm"));
  int res = MPI_Ssend(buf, count, type, dest, tag, comm);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Ssend_init(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); void* buf = (void*) _storage1->data;
  int count = luaL_checkint(L, 2);
  MPI_Datatype type = *((MPI_Datatype*) luaL_checkudata(L, 3, "MPI::Datatype"));
  int dest = luaL_checkint(L, 4);
  int tag = luaL_checkint(L, 5);
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 6, "MPI::Comm"));
  MPI_Request* request = (MPI_Request*) luaL_checkudata(L, 7, "MPI::Request");
  int res = MPI_Ssend_init(buf, count, type, dest, tag, comm, request);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Start(lua_State *L)
{
  MPI_Request* request = (MPI_Request*) luaL_checkudata(L, 1, "MPI::Request");
  int res = MPI_Start(request);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Startall(lua_State *L)
{
  int count = luaL_checkint(L, 1);
  MPI_Request* requests = (MPI_Request*) luaL_checkudata(L, 2, "MPI::Request");
  int res = MPI_Startall(count, requests);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Status_set_cancelled(lua_State *L)
{
  MPI_Status* status = (MPI_Status*) luaL_checkudata(L, 1, "MPI::Status");
  int flag = luaL_checkint(L, 2);
  int res = MPI_Status_set_cancelled(status, flag);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Status_set_elements(lua_State *L)
{
  MPI_Status* status = (MPI_Status*) luaL_checkudata(L, 1, "MPI::Status");
  MPI_Datatype datatype = *((MPI_Datatype*) luaL_checkudata(L, 2, "MPI::Datatype"));
  int count = luaL_checkint(L, 3);
  int res = MPI_Status_set_elements(status, datatype, count);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Test(lua_State *L)
{
  MPI_Request* request = (MPI_Request*) luaL_checkudata(L, 1, "MPI::Request");
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); int* completed = (int*) _storage2->data;
  MPI_Status* status = (MPI_Status*) luaL_checkudata(L, 3, "MPI::Status");
  int res = MPI_Test(request, completed, status);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Test_cancelled(lua_State *L)
{
  MPI_Status* status = (MPI_Status*) luaL_checkudata(L, 1, "MPI::Status");
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); int* flag = (int*) _storage2->data;
  int res = MPI_Test_cancelled(status, flag);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Testall(lua_State *L)
{
  int count = luaL_checkint(L, 1);
  MPI_Request* requests = (MPI_Request*) luaL_checkudata(L, 2, "MPI::Request");
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); int* flag = (int*) _storage3->data;
  MPI_Status* statuses = (MPI_Status*) luaL_checkudata(L, 4, "MPI::Status");
  int res = MPI_Testall(count, requests, flag, statuses);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Testany(lua_State *L)
{
  int count = luaL_checkint(L, 1);
  MPI_Request* requests = (MPI_Request*) luaL_checkudata(L, 2, "MPI::Request");
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); int* indx = (int*) _storage3->data;
  const char *_type4 = luaT_typename(L,4); MPI_THStorage *_storage4 = luaT_toudata(L,4,_type4); int* completed = (int*) _storage4->data;
  MPI_Status* status = (MPI_Status*) luaL_checkudata(L, 5, "MPI::Status");
  int res = MPI_Testany(count, requests, indx, completed, status);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Testsome(lua_State *L)
{
  int incount = luaL_checkint(L, 1);
  MPI_Request* requests = (MPI_Request*) luaL_checkudata(L, 2, "MPI::Request");
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); int* outcount = (int*) _storage3->data;
  const char *_type4 = luaT_typename(L,4); MPI_THStorage *_storage4 = luaT_toudata(L,4,_type4); int* indices = (int*) _storage4->data;
  MPI_Status* statuses = (MPI_Status*) luaL_checkudata(L, 5, "MPI::Status");
  int res = MPI_Testsome(incount, requests, outcount, indices, statuses);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Topo_test(lua_State *L)
{
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 1, "MPI::Comm"));
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); int* status = (int*) _storage2->data;
  int res = MPI_Topo_test(comm, status);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Type_commit(lua_State *L)
{
  MPI_Datatype* type = (MPI_Datatype*) luaL_checkudata(L, 1, "MPI::Datatype");
  int res = MPI_Type_commit(type);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Type_contiguous(lua_State *L)
{
  int count = luaL_checkint(L, 1);
  MPI_Datatype oldtype = *((MPI_Datatype*) luaL_checkudata(L, 2, "MPI::Datatype"));
  MPI_Datatype* newtype = (MPI_Datatype*) luaL_checkudata(L, 3, "MPI::Datatype");
  int res = MPI_Type_contiguous(count, oldtype, newtype);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Type_create_darray(lua_State *L)
{
  int size = luaL_checkint(L, 1);
  int rank = luaL_checkint(L, 2);
  int ndims = luaL_checkint(L, 3);
  const char *_type4 = luaT_typename(L,4); MPI_THStorage *_storage4 = luaT_toudata(L,4,_type4); int* gsize_array = (int*) _storage4->data;
  const char *_type5 = luaT_typename(L,5); MPI_THStorage *_storage5 = luaT_toudata(L,5,_type5); int* distrib_array = (int*) _storage5->data;
  const char *_type6 = luaT_typename(L,6); MPI_THStorage *_storage6 = luaT_toudata(L,6,_type6); int* darg_array = (int*) _storage6->data;
  const char *_type7 = luaT_typename(L,7); MPI_THStorage *_storage7 = luaT_toudata(L,7,_type7); int* psize_array = (int*) _storage7->data;
  int order = luaL_checkint(L, 8);
  MPI_Datatype oldtype = *((MPI_Datatype*) luaL_checkudata(L, 9, "MPI::Datatype"));
  MPI_Datatype* newtype = (MPI_Datatype*) luaL_checkudata(L, 10, "MPI::Datatype");
  int res = MPI_Type_create_darray(size, rank, ndims, gsize_array, distrib_array, darg_array, psize_array, order, oldtype, newtype);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Type_create_hindexed(lua_State *L)
{
  int count = luaL_checkint(L, 1);
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); int* array_of_blocklengths = (int*) _storage2->data;
  MPI_Aint* array_of_displacements = (MPI_Aint*) luaL_checkudata(L, 3, "MPI::Aint");
  MPI_Datatype oldtype = *((MPI_Datatype*) luaL_checkudata(L, 4, "MPI::Datatype"));
  MPI_Datatype* newtype = (MPI_Datatype*) luaL_checkudata(L, 5, "MPI::Datatype");
  int res = MPI_Type_create_hindexed(count, array_of_blocklengths, array_of_displacements, oldtype, newtype);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Type_create_hvector(lua_State *L)
{
  int count = luaL_checkint(L, 1);
  int blocklength = luaL_checkint(L, 2);
  MPI_Aint stride = *((MPI_Aint*) luaL_checkudata(L, 3, "MPI::Aint"));
  MPI_Datatype oldtype = *((MPI_Datatype*) luaL_checkudata(L, 4, "MPI::Datatype"));
  MPI_Datatype* newtype = (MPI_Datatype*) luaL_checkudata(L, 5, "MPI::Datatype");
  int res = MPI_Type_create_hvector(count, blocklength, stride, oldtype, newtype);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Type_create_indexed_block(lua_State *L)
{
  int count = luaL_checkint(L, 1);
  int blocklength = luaL_checkint(L, 2);
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); int* array_of_displacements = (int*) _storage3->data;
  MPI_Datatype oldtype = *((MPI_Datatype*) luaL_checkudata(L, 4, "MPI::Datatype"));
  MPI_Datatype* newtype = (MPI_Datatype*) luaL_checkudata(L, 5, "MPI::Datatype");
  int res = MPI_Type_create_indexed_block(count, blocklength, array_of_displacements, oldtype, newtype);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Type_create_keyval(lua_State *L)
{
  MPI_Type_copy_attr_function* type_copy_attr_fn = (MPI_Type_copy_attr_function*) luaL_checkudata(L, 1, "MPI::Type_copy_attr_function");
  MPI_Type_delete_attr_function* type_delete_attr_fn = (MPI_Type_delete_attr_function*) luaL_checkudata(L, 2, "MPI::Type_delete_attr_function");
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); int* type_keyval = (int*) _storage3->data;
  const char *_type4 = luaT_typename(L,4); MPI_THStorage *_storage4 = luaT_toudata(L,4,_type4); void* extra_state = (void*) _storage4->data;
  int res = MPI_Type_create_keyval(type_copy_attr_fn, type_delete_attr_fn, type_keyval, extra_state);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Type_create_resized(lua_State *L)
{
  MPI_Datatype oldtype = *((MPI_Datatype*) luaL_checkudata(L, 1, "MPI::Datatype"));
  MPI_Aint lb = *((MPI_Aint*) luaL_checkudata(L, 2, "MPI::Aint"));
  MPI_Aint extent = *((MPI_Aint*) luaL_checkudata(L, 3, "MPI::Aint"));
  MPI_Datatype* newtype = (MPI_Datatype*) luaL_checkudata(L, 4, "MPI::Datatype");
  int res = MPI_Type_create_resized(oldtype, lb, extent, newtype);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Type_create_struct(lua_State *L)
{
  int count = luaL_checkint(L, 1);
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); int* array_of_blocklengths = (int*) _storage2->data;
  MPI_Aint* array_of_displacements = (MPI_Aint*) luaL_checkudata(L, 3, "MPI::Aint");
  MPI_Datatype* array_of_types = (MPI_Datatype*) luaL_checkudata(L, 4, "MPI::Datatype");
  MPI_Datatype* newtype = (MPI_Datatype*) luaL_checkudata(L, 5, "MPI::Datatype");
  int res = MPI_Type_create_struct(count, array_of_blocklengths, array_of_displacements, array_of_types, newtype);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Type_create_subarray(lua_State *L)
{
  int ndims = luaL_checkint(L, 1);
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); int* size_array = (int*) _storage2->data;
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); int* subsize_array = (int*) _storage3->data;
  const char *_type4 = luaT_typename(L,4); MPI_THStorage *_storage4 = luaT_toudata(L,4,_type4); int* start_array = (int*) _storage4->data;
  int order = luaL_checkint(L, 5);
  MPI_Datatype oldtype = *((MPI_Datatype*) luaL_checkudata(L, 6, "MPI::Datatype"));
  MPI_Datatype* newtype = (MPI_Datatype*) luaL_checkudata(L, 7, "MPI::Datatype");
  int res = MPI_Type_create_subarray(ndims, size_array, subsize_array, start_array, order, oldtype, newtype);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Type_delete_attr(lua_State *L)
{
  MPI_Datatype type = *((MPI_Datatype*) luaL_checkudata(L, 1, "MPI::Datatype"));
  int type_keyval = luaL_checkint(L, 2);
  int res = MPI_Type_delete_attr(type, type_keyval);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Type_dup(lua_State *L)
{
  MPI_Datatype type = *((MPI_Datatype*) luaL_checkudata(L, 1, "MPI::Datatype"));
  MPI_Datatype* newtype = (MPI_Datatype*) luaL_checkudata(L, 2, "MPI::Datatype");
  int res = MPI_Type_dup(type, newtype);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Type_free(lua_State *L)
{
  MPI_Datatype* type = (MPI_Datatype*) luaL_checkudata(L, 1, "MPI::Datatype");
  int res = MPI_Type_free(type);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Type_free_keyval(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); int* type_keyval = (int*) _storage1->data;
  int res = MPI_Type_free_keyval(type_keyval);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Type_get_attr(lua_State *L)
{
  MPI_Datatype type = *((MPI_Datatype*) luaL_checkudata(L, 1, "MPI::Datatype"));
  int type_keyval = luaL_checkint(L, 2);
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); void* attribute_val = (void*) _storage3->data;
  const char *_type4 = luaT_typename(L,4); MPI_THStorage *_storage4 = luaT_toudata(L,4,_type4); int* flag = (int*) _storage4->data;
  int res = MPI_Type_get_attr(type, type_keyval, attribute_val, flag);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Type_get_contents(lua_State *L)
{
  MPI_Datatype mtype = *((MPI_Datatype*) luaL_checkudata(L, 1, "MPI::Datatype"));
  int max_integers = luaL_checkint(L, 2);
  int max_addresses = luaL_checkint(L, 3);
  int max_datatypes = luaL_checkint(L, 4);
  const char *_type5 = luaT_typename(L,5); MPI_THStorage *_storage5 = luaT_toudata(L,5,_type5); int* array_of_integers = (int*) _storage5->data;
  MPI_Aint* array_of_addresses = (MPI_Aint*) luaL_checkudata(L, 6, "MPI::Aint");
  MPI_Datatype* array_of_datatypes = (MPI_Datatype*) luaL_checkudata(L, 7, "MPI::Datatype");
  int res = MPI_Type_get_contents(mtype, max_integers, max_addresses, max_datatypes, array_of_integers, array_of_addresses, array_of_datatypes);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Type_get_envelope(lua_State *L)
{
  MPI_Datatype type = *((MPI_Datatype*) luaL_checkudata(L, 1, "MPI::Datatype"));
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); int* num_integers = (int*) _storage2->data;
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); int* num_addresses = (int*) _storage3->data;
  const char *_type4 = luaT_typename(L,4); MPI_THStorage *_storage4 = luaT_toudata(L,4,_type4); int* num_datatypes = (int*) _storage4->data;
  const char *_type5 = luaT_typename(L,5); MPI_THStorage *_storage5 = luaT_toudata(L,5,_type5); int* combiner = (int*) _storage5->data;
  int res = MPI_Type_get_envelope(type, num_integers, num_addresses, num_datatypes, combiner);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Type_get_extent(lua_State *L)
{
  MPI_Datatype type = *((MPI_Datatype*) luaL_checkudata(L, 1, "MPI::Datatype"));
  MPI_Aint* lb = (MPI_Aint*) luaL_checkudata(L, 2, "MPI::Aint");
  MPI_Aint* extent = (MPI_Aint*) luaL_checkudata(L, 3, "MPI::Aint");
  int res = MPI_Type_get_extent(type, lb, extent);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Type_get_name(lua_State *L)
{
  MPI_Datatype type = *((MPI_Datatype*) luaL_checkudata(L, 1, "MPI::Datatype"));
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); char* type_name = (char*) _storage2->data;
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); int* resultlen = (int*) _storage3->data;
  int res = MPI_Type_get_name(type, type_name, resultlen);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Type_get_true_extent(lua_State *L)
{
  MPI_Datatype datatype = *((MPI_Datatype*) luaL_checkudata(L, 1, "MPI::Datatype"));
  MPI_Aint* true_lb = (MPI_Aint*) luaL_checkudata(L, 2, "MPI::Aint");
  MPI_Aint* true_extent = (MPI_Aint*) luaL_checkudata(L, 3, "MPI::Aint");
  int res = MPI_Type_get_true_extent(datatype, true_lb, true_extent);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Type_indexed(lua_State *L)
{
  int count = luaL_checkint(L, 1);
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); int* array_of_blocklengths = (int*) _storage2->data;
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); int* array_of_displacements = (int*) _storage3->data;
  MPI_Datatype oldtype = *((MPI_Datatype*) luaL_checkudata(L, 4, "MPI::Datatype"));
  MPI_Datatype* newtype = (MPI_Datatype*) luaL_checkudata(L, 5, "MPI::Datatype");
  int res = MPI_Type_indexed(count, array_of_blocklengths, array_of_displacements, oldtype, newtype);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Type_match_size(lua_State *L)
{
  int typeclass = luaL_checkint(L, 1);
  int size = luaL_checkint(L, 2);
  MPI_Datatype* type = (MPI_Datatype*) luaL_checkudata(L, 3, "MPI::Datatype");
  int res = MPI_Type_match_size(typeclass, size, type);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Type_set_attr(lua_State *L)
{
  MPI_Datatype type = *((MPI_Datatype*) luaL_checkudata(L, 1, "MPI::Datatype"));
  int type_keyval = luaL_checkint(L, 2);
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); void* attribute_val = (void*) _storage3->data;
  int res = MPI_Type_set_attr(type, type_keyval, attribute_val);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Type_set_name(lua_State *L)
{
  MPI_Datatype type = *((MPI_Datatype*) luaL_checkudata(L, 1, "MPI::Datatype"));
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); char* type_name = (char*) _storage2->data;
  int res = MPI_Type_set_name(type, type_name);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Type_size(lua_State *L)
{
  MPI_Datatype type = *((MPI_Datatype*) luaL_checkudata(L, 1, "MPI::Datatype"));
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); int* size = (int*) _storage2->data;
  int res = MPI_Type_size(type, size);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Type_vector(lua_State *L)
{
  int count = luaL_checkint(L, 1);
  int blocklength = luaL_checkint(L, 2);
  int stride = luaL_checkint(L, 3);
  MPI_Datatype oldtype = *((MPI_Datatype*) luaL_checkudata(L, 4, "MPI::Datatype"));
  MPI_Datatype* newtype = (MPI_Datatype*) luaL_checkudata(L, 5, "MPI::Datatype");
  int res = MPI_Type_vector(count, blocklength, stride, oldtype, newtype);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Unpack(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); void* inbuf = (void*) _storage1->data;
  int insize = luaL_checkint(L, 2);
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); int* position = (int*) _storage3->data;
  const char *_type4 = luaT_typename(L,4); MPI_THStorage *_storage4 = luaT_toudata(L,4,_type4); void* outbuf = (void*) _storage4->data;
  int outcount = luaL_checkint(L, 5);
  MPI_Datatype datatype = *((MPI_Datatype*) luaL_checkudata(L, 6, "MPI::Datatype"));
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 7, "MPI::Comm"));
  int res = MPI_Unpack(inbuf, insize, position, outbuf, outcount, datatype, comm);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Unpack_external(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); char* datarep = (char*) _storage1->data;
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); void* inbuf = (void*) _storage2->data;
  MPI_Aint insize = *((MPI_Aint*) luaL_checkudata(L, 3, "MPI::Aint"));
  MPI_Aint* position = (MPI_Aint*) luaL_checkudata(L, 4, "MPI::Aint");
  const char *_type5 = luaT_typename(L,5); MPI_THStorage *_storage5 = luaT_toudata(L,5,_type5); void* outbuf = (void*) _storage5->data;
  int outcount = luaL_checkint(L, 6);
  MPI_Datatype datatype = *((MPI_Datatype*) luaL_checkudata(L, 7, "MPI::Datatype"));
  int res = MPI_Unpack_external(datarep, inbuf, insize, position, outbuf, outcount, datatype);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Unpublish_name(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); char* service_name = (char*) _storage1->data;
  MPI_Info info = *((MPI_Info*) luaL_checkudata(L, 2, "MPI::Info"));
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); char* port_name = (char*) _storage3->data;
  int res = MPI_Unpublish_name(service_name, info, port_name);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Wait(lua_State *L)
{
  MPI_Request* request = (MPI_Request*) luaL_checkudata(L, 1, "MPI::Request");
  MPI_Status* status = (MPI_Status*) luaL_checkudata(L, 2, "MPI::Status");
  int res = MPI_Wait(request, status);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Waitall(lua_State *L)
{
  int count = luaL_checkint(L, 1);
  MPI_Request* requests = (MPI_Request*) luaL_checkudata(L, 2, "MPI::Request");
  MPI_Status* statuses = (MPI_Status*) luaL_checkudata(L, 3, "MPI::Status");
  int res = MPI_Waitall(count, requests, statuses);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Waitany(lua_State *L)
{
  int count = luaL_checkint(L, 1);
  MPI_Request* requests = (MPI_Request*) luaL_checkudata(L, 2, "MPI::Request");
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); int* indx = (int*) _storage3->data;
  MPI_Status* status = (MPI_Status*) luaL_checkudata(L, 4, "MPI::Status");
  int res = MPI_Waitany(count, requests, indx, status);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Waitsome(lua_State *L)
{
  int incount = luaL_checkint(L, 1);
  MPI_Request* requests = (MPI_Request*) luaL_checkudata(L, 2, "MPI::Request");
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); int* outcount = (int*) _storage3->data;
  const char *_type4 = luaT_typename(L,4); MPI_THStorage *_storage4 = luaT_toudata(L,4,_type4); int* indices = (int*) _storage4->data;
  MPI_Status* statuses = (MPI_Status*) luaL_checkudata(L, 5, "MPI::Status");
  int res = MPI_Waitsome(incount, requests, outcount, indices, statuses);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Win_call_errhandler(lua_State *L)
{
  MPI_Win win = *((MPI_Win*) luaL_checkudata(L, 1, "MPI::Win"));
  int errorcode = luaL_checkint(L, 2);
  int res = MPI_Win_call_errhandler(win, errorcode);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Win_complete(lua_State *L)
{
  MPI_Win win = *((MPI_Win*) luaL_checkudata(L, 1, "MPI::Win"));
  int res = MPI_Win_complete(win);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Win_create(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); void* base = (void*) _storage1->data;
  MPI_Aint size = *((MPI_Aint*) luaL_checkudata(L, 2, "MPI::Aint"));
  int disp_unit = luaL_checkint(L, 3);
  MPI_Info info = *((MPI_Info*) luaL_checkudata(L, 4, "MPI::Info"));
  MPI_Comm comm = *((MPI_Comm*) luaL_checkudata(L, 5, "MPI::Comm"));
  MPI_Win* win = (MPI_Win*) luaL_checkudata(L, 6, "MPI::Win");
  int res = MPI_Win_create(base, size, disp_unit, info, comm, win);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Win_create_keyval(lua_State *L)
{
  MPI_Win_copy_attr_function* win_copy_attr_fn = (MPI_Win_copy_attr_function*) luaL_checkudata(L, 1, "MPI::Win_copy_attr_function");
  MPI_Win_delete_attr_function* win_delete_attr_fn = (MPI_Win_delete_attr_function*) luaL_checkudata(L, 2, "MPI::Win_delete_attr_function");
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); int* win_keyval = (int*) _storage3->data;
  const char *_type4 = luaT_typename(L,4); MPI_THStorage *_storage4 = luaT_toudata(L,4,_type4); void* extra_state = (void*) _storage4->data;
  int res = MPI_Win_create_keyval(win_copy_attr_fn, win_delete_attr_fn, win_keyval, extra_state);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Win_delete_attr(lua_State *L)
{
  MPI_Win win = *((MPI_Win*) luaL_checkudata(L, 1, "MPI::Win"));
  int win_keyval = luaL_checkint(L, 2);
  int res = MPI_Win_delete_attr(win, win_keyval);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Win_fence(lua_State *L)
{
  int assert = luaL_checkint(L, 1);
  MPI_Win win = *((MPI_Win*) luaL_checkudata(L, 2, "MPI::Win"));
  int res = MPI_Win_fence(assert, win);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Win_free(lua_State *L)
{
  MPI_Win* win = (MPI_Win*) luaL_checkudata(L, 1, "MPI::Win");
  int res = MPI_Win_free(win);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Win_free_keyval(lua_State *L)
{
  const char *_type1 = luaT_typename(L,1); MPI_THStorage *_storage1 = luaT_toudata(L,1,_type1); int* win_keyval = (int*) _storage1->data;
  int res = MPI_Win_free_keyval(win_keyval);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Win_get_attr(lua_State *L)
{
  MPI_Win win = *((MPI_Win*) luaL_checkudata(L, 1, "MPI::Win"));
  int win_keyval = luaL_checkint(L, 2);
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); void* attribute_val = (void*) _storage3->data;
  const char *_type4 = luaT_typename(L,4); MPI_THStorage *_storage4 = luaT_toudata(L,4,_type4); int* flag = (int*) _storage4->data;
  int res = MPI_Win_get_attr(win, win_keyval, attribute_val, flag);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Win_get_errhandler(lua_State *L)
{
  MPI_Win win = *((MPI_Win*) luaL_checkudata(L, 1, "MPI::Win"));
  MPI_Errhandler* errhandler = (MPI_Errhandler*) luaL_checkudata(L, 2, "MPI::Errhandler");
  int res = MPI_Win_get_errhandler(win, errhandler);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Win_get_group(lua_State *L)
{
  MPI_Win win = *((MPI_Win*) luaL_checkudata(L, 1, "MPI::Win"));
  MPI_Group* group = (MPI_Group*) luaL_checkudata(L, 2, "MPI::Group");
  int res = MPI_Win_get_group(win, group);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Win_get_name(lua_State *L)
{
  MPI_Win win = *((MPI_Win*) luaL_checkudata(L, 1, "MPI::Win"));
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); char* win_name = (char*) _storage2->data;
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); int* resultlen = (int*) _storage3->data;
  int res = MPI_Win_get_name(win, win_name, resultlen);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Win_lock(lua_State *L)
{
  int lock_type = luaL_checkint(L, 1);
  int rank = luaL_checkint(L, 2);
  int assert = luaL_checkint(L, 3);
  MPI_Win win = *((MPI_Win*) luaL_checkudata(L, 4, "MPI::Win"));
  int res = MPI_Win_lock(lock_type, rank, assert, win);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Win_post(lua_State *L)
{
  MPI_Group group = *((MPI_Group*) luaL_checkudata(L, 1, "MPI::Group"));
  int assert = luaL_checkint(L, 2);
  MPI_Win win = *((MPI_Win*) luaL_checkudata(L, 3, "MPI::Win"));
  int res = MPI_Win_post(group, assert, win);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Win_set_attr(lua_State *L)
{
  MPI_Win win = *((MPI_Win*) luaL_checkudata(L, 1, "MPI::Win"));
  int win_keyval = luaL_checkint(L, 2);
  const char *_type3 = luaT_typename(L,3); MPI_THStorage *_storage3 = luaT_toudata(L,3,_type3); void* attribute_val = (void*) _storage3->data;
  int res = MPI_Win_set_attr(win, win_keyval, attribute_val);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Win_set_errhandler(lua_State *L)
{
  MPI_Win win = *((MPI_Win*) luaL_checkudata(L, 1, "MPI::Win"));
  MPI_Errhandler errhandler = *((MPI_Errhandler*) luaL_checkudata(L, 2, "MPI::Errhandler"));
  int res = MPI_Win_set_errhandler(win, errhandler);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Win_set_name(lua_State *L)
{
  MPI_Win win = *((MPI_Win*) luaL_checkudata(L, 1, "MPI::Win"));
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); char* win_name = (char*) _storage2->data;
  int res = MPI_Win_set_name(win, win_name);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Win_start(lua_State *L)
{
  MPI_Group group = *((MPI_Group*) luaL_checkudata(L, 1, "MPI::Group"));
  int assert = luaL_checkint(L, 2);
  MPI_Win win = *((MPI_Win*) luaL_checkudata(L, 3, "MPI::Win"));
  int res = MPI_Win_start(group, assert, win);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Win_test(lua_State *L)
{
  MPI_Win win = *((MPI_Win*) luaL_checkudata(L, 1, "MPI::Win"));
  const char *_type2 = luaT_typename(L,2); MPI_THStorage *_storage2 = luaT_toudata(L,2,_type2); int* flag = (int*) _storage2->data;
  int res = MPI_Win_test(win, flag);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Win_unlock(lua_State *L)
{
  int rank = luaL_checkint(L, 1);
  MPI_Win win = *((MPI_Win*) luaL_checkudata(L, 2, "MPI::Win"));
  int res = MPI_Win_unlock(rank, win);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Win_wait(lua_State *L)
{
  MPI_Win win = *((MPI_Win*) luaL_checkudata(L, 1, "MPI::Win"));
  int res = MPI_Win_wait(win);
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Wtick(lua_State *L)
{
  // no Lua args
  double res = MPI_Wtick();
  lua_pushnumber(L, res);
  return 1;
}
static int _MPI_Wtime(lua_State *L)
{
  // no Lua args
  double res = MPI_Wtime();
  lua_pushnumber(L, res);
  return 1;
}
luaL_Reg MPI_module_funcs[] = {
  { "Abort", _MPI_Abort},
  { "Accumulate", _MPI_Accumulate},
  { "Add_error_class", _MPI_Add_error_class},
  { "Add_error_code", _MPI_Add_error_code},
  { "Add_error_string", _MPI_Add_error_string},
  { "Allgather", _MPI_Allgather},
  { "Allgatherv", _MPI_Allgatherv},
  { "Alloc_mem", _MPI_Alloc_mem},
  { "Allreduce", _MPI_Allreduce},
  { "Alltoall", _MPI_Alltoall},
  { "Alltoallv", _MPI_Alltoallv},
  { "Alltoallw", _MPI_Alltoallw},
  { "Barrier", _MPI_Barrier},
  { "Bcast", _MPI_Bcast},
  { "Bsend", _MPI_Bsend},
  { "Bsend_init", _MPI_Bsend_init},
  { "Buffer_attach", _MPI_Buffer_attach},
  { "Buffer_detach", _MPI_Buffer_detach},
  { "Cancel", _MPI_Cancel},
  { "Cart_coords", _MPI_Cart_coords},
  { "Cart_create", _MPI_Cart_create},
  { "Cart_get", _MPI_Cart_get},
  { "Cart_map", _MPI_Cart_map},
  { "Cart_rank", _MPI_Cart_rank},
  { "Cart_shift", _MPI_Cart_shift},
  { "Cart_sub", _MPI_Cart_sub},
  { "Cartdim_get", _MPI_Cartdim_get},
  { "Close_port", _MPI_Close_port},
  { "Comm_accept", _MPI_Comm_accept},
  { "Comm_call_errhandler", _MPI_Comm_call_errhandler},
  { "Comm_compare", _MPI_Comm_compare},
  { "Comm_connect", _MPI_Comm_connect},
  { "Comm_create", _MPI_Comm_create},
  { "Comm_create_keyval", _MPI_Comm_create_keyval},
  { "Comm_delete_attr", _MPI_Comm_delete_attr},
  { "Comm_disconnect", _MPI_Comm_disconnect},
  { "Comm_dup", _MPI_Comm_dup},
  { "Comm_free", _MPI_Comm_free},
  { "Comm_free_keyval", _MPI_Comm_free_keyval},
  { "Comm_get_attr", _MPI_Comm_get_attr},
  { "Comm_get_errhandler", _MPI_Comm_get_errhandler},
  { "Comm_get_name", _MPI_Comm_get_name},
  { "Comm_get_parent", _MPI_Comm_get_parent},
  { "Comm_group", _MPI_Comm_group},
  { "Comm_join", _MPI_Comm_join},
  { "Comm_rank", _MPI_Comm_rank},
  { "Comm_remote_group", _MPI_Comm_remote_group},
  { "Comm_remote_size", _MPI_Comm_remote_size},
  { "Comm_set_attr", _MPI_Comm_set_attr},
  { "Comm_set_errhandler", _MPI_Comm_set_errhandler},
  { "Comm_set_name", _MPI_Comm_set_name},
  { "Comm_size", _MPI_Comm_size},
  { "Comm_split", _MPI_Comm_split},
  { "Comm_test_inter", _MPI_Comm_test_inter},
  { "Dims_create", _MPI_Dims_create},
  { "Errhandler_free", _MPI_Errhandler_free},
  { "Error_class", _MPI_Error_class},
  { "Error_string", _MPI_Error_string},
  { "Exscan", _MPI_Exscan},
  { "File_call_errhandler", _MPI_File_call_errhandler},
  { "File_close", _MPI_File_close},
  { "File_delete", _MPI_File_delete},
  { "File_get_amode", _MPI_File_get_amode},
  { "File_get_atomicity", _MPI_File_get_atomicity},
  { "File_get_byte_offset", _MPI_File_get_byte_offset},
  { "File_get_errhandler", _MPI_File_get_errhandler},
  { "File_get_group", _MPI_File_get_group},
  { "File_get_info", _MPI_File_get_info},
  { "File_get_position", _MPI_File_get_position},
  { "File_get_position_shared", _MPI_File_get_position_shared},
  { "File_get_size", _MPI_File_get_size},
  { "File_get_type_extent", _MPI_File_get_type_extent},
  { "File_get_view", _MPI_File_get_view},
  { "File_iread", _MPI_File_iread},
  { "File_iread_at", _MPI_File_iread_at},
  { "File_iread_shared", _MPI_File_iread_shared},
  { "File_iwrite", _MPI_File_iwrite},
  { "File_iwrite_at", _MPI_File_iwrite_at},
  { "File_iwrite_shared", _MPI_File_iwrite_shared},
  { "File_open", _MPI_File_open},
  { "File_preallocate", _MPI_File_preallocate},
  { "File_read", _MPI_File_read},
  { "File_read_all", _MPI_File_read_all},
  { "File_read_all_begin", _MPI_File_read_all_begin},
  { "File_read_all_end", _MPI_File_read_all_end},
  { "File_read_at", _MPI_File_read_at},
  { "File_read_at_all", _MPI_File_read_at_all},
  { "File_read_at_all_begin", _MPI_File_read_at_all_begin},
  { "File_read_at_all_end", _MPI_File_read_at_all_end},
  { "File_read_ordered", _MPI_File_read_ordered},
  { "File_read_ordered_begin", _MPI_File_read_ordered_begin},
  { "File_read_ordered_end", _MPI_File_read_ordered_end},
  { "File_read_shared", _MPI_File_read_shared},
  { "File_seek", _MPI_File_seek},
  { "File_seek_shared", _MPI_File_seek_shared},
  { "File_set_atomicity", _MPI_File_set_atomicity},
  { "File_set_errhandler", _MPI_File_set_errhandler},
  { "File_set_info", _MPI_File_set_info},
  { "File_set_size", _MPI_File_set_size},
  { "File_set_view", _MPI_File_set_view},
  { "File_sync", _MPI_File_sync},
  { "File_write", _MPI_File_write},
  { "File_write_all", _MPI_File_write_all},
  { "File_write_all_begin", _MPI_File_write_all_begin},
  { "File_write_all_end", _MPI_File_write_all_end},
  { "File_write_at", _MPI_File_write_at},
  { "File_write_at_all", _MPI_File_write_at_all},
  { "File_write_at_all_begin", _MPI_File_write_at_all_begin},
  { "File_write_at_all_end", _MPI_File_write_at_all_end},
  { "File_write_ordered", _MPI_File_write_ordered},
  { "File_write_ordered_begin", _MPI_File_write_ordered_begin},
  { "File_write_ordered_end", _MPI_File_write_ordered_end},
  { "File_write_shared", _MPI_File_write_shared},
  { "Finalize", _MPI_Finalize},
  { "Finalized", _MPI_Finalized},
  { "Free_mem", _MPI_Free_mem},
  { "Gather", _MPI_Gather},
  { "Gatherv", _MPI_Gatherv},
  { "Get", _MPI_Get},
  { "Get_address", _MPI_Get_address},
  { "Get_count", _MPI_Get_count},
  { "Get_elements", _MPI_Get_elements},
  { "Get_processor_name", _MPI_Get_processor_name},
  { "Get_version", _MPI_Get_version},
  { "Graph_create", _MPI_Graph_create},
  { "Graph_get", _MPI_Graph_get},
  { "Graph_map", _MPI_Graph_map},
  { "Graph_neighbors", _MPI_Graph_neighbors},
  { "Graph_neighbors_count", _MPI_Graph_neighbors_count},
  { "Graphdims_get", _MPI_Graphdims_get},
  { "Grequest_complete", _MPI_Grequest_complete},
  { "Grequest_start", _MPI_Grequest_start},
  { "Group_compare", _MPI_Group_compare},
  { "Group_difference", _MPI_Group_difference},
  { "Group_excl", _MPI_Group_excl},
  { "Group_free", _MPI_Group_free},
  { "Group_incl", _MPI_Group_incl},
  { "Group_intersection", _MPI_Group_intersection},
  { "Group_rank", _MPI_Group_rank},
  { "Group_size", _MPI_Group_size},
  { "Group_translate_ranks", _MPI_Group_translate_ranks},
  { "Group_union", _MPI_Group_union},
  { "Iallreduce", _MPI_Iallreduce},
  { "Ibsend", _MPI_Ibsend},
  { "Info_create", _MPI_Info_create},
  { "Info_delete", _MPI_Info_delete},
  { "Info_dup", _MPI_Info_dup},
  { "Info_free", _MPI_Info_free},
  { "Info_get", _MPI_Info_get},
  { "Info_get_nkeys", _MPI_Info_get_nkeys},
  { "Info_get_nthkey", _MPI_Info_get_nthkey},
  { "Info_get_valuelen", _MPI_Info_get_valuelen},
  { "Info_set", _MPI_Info_set},
  { "Initialized", _MPI_Initialized},
  { "Intercomm_create", _MPI_Intercomm_create},
  { "Intercomm_merge", _MPI_Intercomm_merge},
  { "Iprobe", _MPI_Iprobe},
  { "Irecv", _MPI_Irecv},
  { "Irsend", _MPI_Irsend},
  { "Is_thread_main", _MPI_Is_thread_main},
  { "Isend", _MPI_Isend},
  { "Issend", _MPI_Issend},
  { "Lookup_name", _MPI_Lookup_name},
  { "Op_create", _MPI_Op_create},
  { "Op_free", _MPI_Op_free},
  { "Open_port", _MPI_Open_port},
  { "Pack", _MPI_Pack},
  { "Pack_external", _MPI_Pack_external},
  { "Pack_external_size", _MPI_Pack_external_size},
  { "Pack_size", _MPI_Pack_size},
  { "Probe", _MPI_Probe},
  { "Publish_name", _MPI_Publish_name},
  { "Put", _MPI_Put},
  { "Query_thread", _MPI_Query_thread},
  { "Recv", _MPI_Recv},
  { "Recv_init", _MPI_Recv_init},
  { "Reduce", _MPI_Reduce},
  { "Reduce_scatter", _MPI_Reduce_scatter},
  { "Register_datarep", _MPI_Register_datarep},
  { "Request_free", _MPI_Request_free},
  { "Request_get_status", _MPI_Request_get_status},
  { "Rsend", _MPI_Rsend},
  { "Rsend_init", _MPI_Rsend_init},
  { "Scan", _MPI_Scan},
  { "Scatter", _MPI_Scatter},
  { "Scatterv", _MPI_Scatterv},
  { "Send", _MPI_Send},
  { "Send_init", _MPI_Send_init},
  { "Sendrecv", _MPI_Sendrecv},
  { "Sendrecv_replace", _MPI_Sendrecv_replace},
  { "Ssend", _MPI_Ssend},
  { "Ssend_init", _MPI_Ssend_init},
  { "Start", _MPI_Start},
  { "Startall", _MPI_Startall},
  { "Status_set_cancelled", _MPI_Status_set_cancelled},
  { "Status_set_elements", _MPI_Status_set_elements},
  { "Test", _MPI_Test},
  { "Test_cancelled", _MPI_Test_cancelled},
  { "Testall", _MPI_Testall},
  { "Testany", _MPI_Testany},
  { "Testsome", _MPI_Testsome},
  { "Topo_test", _MPI_Topo_test},
  { "Type_commit", _MPI_Type_commit},
  { "Type_contiguous", _MPI_Type_contiguous},
  { "Type_create_darray", _MPI_Type_create_darray},
  { "Type_create_hindexed", _MPI_Type_create_hindexed},
  { "Type_create_hvector", _MPI_Type_create_hvector},
  { "Type_create_indexed_block", _MPI_Type_create_indexed_block},
  { "Type_create_keyval", _MPI_Type_create_keyval},
  { "Type_create_resized", _MPI_Type_create_resized},
  { "Type_create_struct", _MPI_Type_create_struct},
  { "Type_create_subarray", _MPI_Type_create_subarray},
  { "Type_delete_attr", _MPI_Type_delete_attr},
  { "Type_dup", _MPI_Type_dup},
  { "Type_free", _MPI_Type_free},
  { "Type_free_keyval", _MPI_Type_free_keyval},
  { "Type_get_attr", _MPI_Type_get_attr},
  { "Type_get_contents", _MPI_Type_get_contents},
  { "Type_get_envelope", _MPI_Type_get_envelope},
  { "Type_get_extent", _MPI_Type_get_extent},
  { "Type_get_name", _MPI_Type_get_name},
  { "Type_get_true_extent", _MPI_Type_get_true_extent},
  { "Type_indexed", _MPI_Type_indexed},
  { "Type_match_size", _MPI_Type_match_size},
  { "Type_set_attr", _MPI_Type_set_attr},
  { "Type_set_name", _MPI_Type_set_name},
  { "Type_size", _MPI_Type_size},
  { "Type_vector", _MPI_Type_vector},
  { "Unpack", _MPI_Unpack},
  { "Unpack_external", _MPI_Unpack_external},
  { "Unpublish_name", _MPI_Unpublish_name},
  { "Wait", _MPI_Wait},
  { "Waitall", _MPI_Waitall},
  { "Waitany", _MPI_Waitany},
  { "Waitsome", _MPI_Waitsome},
  { "Win_call_errhandler", _MPI_Win_call_errhandler},
  { "Win_complete", _MPI_Win_complete},
  { "Win_create", _MPI_Win_create},
  { "Win_create_keyval", _MPI_Win_create_keyval},
  { "Win_delete_attr", _MPI_Win_delete_attr},
  { "Win_fence", _MPI_Win_fence},
  { "Win_free", _MPI_Win_free},
  { "Win_free_keyval", _MPI_Win_free_keyval},
  { "Win_get_attr", _MPI_Win_get_attr},
  { "Win_get_errhandler", _MPI_Win_get_errhandler},
  { "Win_get_group", _MPI_Win_get_group},
  { "Win_get_name", _MPI_Win_get_name},
  { "Win_lock", _MPI_Win_lock},
  { "Win_post", _MPI_Win_post},
  { "Win_set_attr", _MPI_Win_set_attr},
  { "Win_set_errhandler", _MPI_Win_set_errhandler},
  { "Win_set_name", _MPI_Win_set_name},
  { "Win_start", _MPI_Win_start},
  { "Win_test", _MPI_Win_test},
  { "Win_unlock", _MPI_Win_unlock},
  { "Win_wait", _MPI_Win_wait},
  { "Wtick", _MPI_Wtick},
  { "Wtime", _MPI_Wtime},
  { "Init", _MPI_Init},
  { "Init_MTF", _MPI_Init_MTF},
  { "Init_MTS", _MPI_Init_MTS},
  { "Init_MTM", _MPI_Init_MTM},
  {NULL, NULL}};
