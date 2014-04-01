#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#include <mpi.h>

#define MPI_STRUCT_TYPE(s, inival)                                      \
  static void luampi_push_MPI_##s(lua_State *L, MPI_##s init, int N)    \
  {                                                                     \
    int n;                                                              \
    MPI_##s *ud = (MPI_##s*) lua_newuserdata(L, N*sizeof(MPI_##s));	\
      for (n=0; n<N; ++n) ud[n] = init;                                 \
      luaL_getmetatable(L, "MPI::"#s);                                  \
      lua_setmetatable(L, -2);                                          \
  }                                                                     \
  static int _MPI_##s(lua_State *L)                                     \
  {                                                                     \
    int N = luaL_optint(L, 1, 1);                                       \
    luampi_push_MPI_##s(L, inival, N);                                  \
      return 1;                                                         \
  }                                                                     \

#define MPI_FUNC_TYPE(s)                                                \
  static void                                                           \
  luampi_push_MPI_##s##_function(lua_State *L, MPI_##s##_function *arg) \
  {                                                                     \
    typedef MPI_##s##_function T;                                       \
      T **ud = (T**) lua_newuserdata(L, sizeof(T*));                    \
      *ud = arg;                                                        \
      luaL_getmetatable(L, "MPI::"#s"_function");                       \
      lua_setmetatable(L, -2);                                          \
  }                                                                     \
  static int _MPI_##s##_function(lua_State *L)                          \
  {                                                                     \
    luampi_push_MPI_##s##_function(L, NULL);                            \
      return 1;                                                         \
  }                                                                     \

static MPI_Aint MPI_AINT_NULL = 0;
static MPI_Status MPI_STATUS_NULL = {0,0,0};
static MPI_Offset MPI_OFFSET_NULL = 0;

MPI_STRUCT_TYPE(Aint, MPI_AINT_NULL)
MPI_STRUCT_TYPE(Comm, MPI_COMM_NULL)
MPI_STRUCT_TYPE(Datatype, MPI_DATATYPE_NULL)
MPI_STRUCT_TYPE(Errhandler, MPI_ERRHANDLER_NULL)
MPI_STRUCT_TYPE(File, MPI_FILE_NULL)
MPI_STRUCT_TYPE(Group, MPI_GROUP_NULL)
MPI_STRUCT_TYPE(Info, MPI_INFO_NULL)
MPI_STRUCT_TYPE(Offset, MPI_OFFSET_NULL)
MPI_STRUCT_TYPE(Op, MPI_DATATYPE_NULL)
MPI_STRUCT_TYPE(Request, MPI_REQUEST_NULL)
MPI_STRUCT_TYPE(Status, MPI_STATUS_NULL)
MPI_STRUCT_TYPE(Win, MPI_WIN_NULL)

MPI_FUNC_TYPE(Comm_copy_attr)
MPI_FUNC_TYPE(Comm_delete_attr)
MPI_FUNC_TYPE(Type_copy_attr)
MPI_FUNC_TYPE(Type_delete_attr)
MPI_FUNC_TYPE(Win_copy_attr)
MPI_FUNC_TYPE(Win_delete_attr)
MPI_FUNC_TYPE(Datarep_conversion)
MPI_FUNC_TYPE(Datarep_extent)
MPI_FUNC_TYPE(Grequest_cancel)
MPI_FUNC_TYPE(Grequest_free)
MPI_FUNC_TYPE(Grequest_query)
MPI_FUNC_TYPE(User)


typedef struct MPI_THStorage
{
    void *data;
    long size;
    int refcount;
    char flag;
} MPI_THStorage;

// #define MPI_THStorage THCudaStorage

static int _MPI_Init(lua_State *L)
{
  int ret = MPI_Init(0, MPI_ARGVS_NULL);
  lua_pushnumber(L, ret);
  return 1;
}
#include "mpifuncs.c"


static void register_constants(lua_State *L)
{
  /* http://cluster.onu.edu.ua/docs/mpi/www3/Constants.html */

  // Data types
  luampi_push_MPI_Datatype(L, MPI_CHAR, 1); lua_setfield(L, -2, "CHAR");
  luampi_push_MPI_Datatype(L, MPI_BYTE, 1); lua_setfield(L, -2, "BYTE");
  luampi_push_MPI_Datatype(L, MPI_SHORT, 1); lua_setfield(L, -2, "SHORT");
  luampi_push_MPI_Datatype(L, MPI_INT, 1); lua_setfield(L, -2, "INT");
  luampi_push_MPI_Datatype(L, MPI_LONG, 1); lua_setfield(L, -2, "LONG");
  luampi_push_MPI_Datatype(L, MPI_FLOAT, 1); lua_setfield(L, -2, "FLOAT");
  luampi_push_MPI_Datatype(L, MPI_DOUBLE, 1); lua_setfield(L, -2, "DOUBLE");
  luampi_push_MPI_Datatype(L, MPI_UNSIGNED_CHAR, 1); lua_setfield(L, -2, "UNSIGNED_CHAR");
  luampi_push_MPI_Datatype(L, MPI_UNSIGNED_SHORT, 1); lua_setfield(L, -2, "UNSIGNED_SHORT");
  luampi_push_MPI_Datatype(L, MPI_UNSIGNED, 1); lua_setfield(L, -2, "UNSIGNED");
  luampi_push_MPI_Datatype(L, MPI_UNSIGNED_LONG, 1); lua_setfield(L, -2, "UNSIGNED_LONG");
  luampi_push_MPI_Datatype(L, MPI_LONG_DOUBLE, 1); lua_setfield(L, -2, "LONG_DOUBLE");
  luampi_push_MPI_Datatype(L, MPI_LONG_LONG_INT, 1); lua_setfield(L, -2, "LONG_LONG_INT");
  luampi_push_MPI_Datatype(L, MPI_FLOAT_INT, 1); lua_setfield(L, -2, "FLOAT_INT");
  luampi_push_MPI_Datatype(L, MPI_LONG_INT, 1); lua_setfield(L, -2, "LONG_INT");
  luampi_push_MPI_Datatype(L, MPI_DOUBLE_INT, 1); lua_setfield(L, -2, "DOUBLE_INT");
  luampi_push_MPI_Datatype(L, MPI_SHORT_INT, 1); lua_setfield(L, -2, "SHORT_INT");
  luampi_push_MPI_Datatype(L, MPI_2INT, 1); lua_setfield(L, -2, "2INT");
  luampi_push_MPI_Datatype(L, MPI_LONG_DOUBLE_INT, 1); lua_setfield(L, -2, "LONG_DOUBLE_INT");
  luampi_push_MPI_Datatype(L, MPI_PACKED, 1); lua_setfield(L, -2, "PACKED");
  luampi_push_MPI_Datatype(L, MPI_UB, 1); lua_setfield(L, -2, "UB");
  luampi_push_MPI_Datatype(L, MPI_LB, 1); lua_setfield(L, -2, "LB");


  // Null objects
  luampi_push_MPI_Comm(L, MPI_COMM_NULL, 1); lua_setfield(L, -2, "COMM_NULL");
  luampi_push_MPI_Op(L, MPI_OP_NULL, 1); lua_setfield(L, -2, "OP_NULL");
  luampi_push_MPI_Group(L, MPI_GROUP_NULL, 1); lua_setfield(L, -2, "GROUP_NULL");
  luampi_push_MPI_Datatype(L, MPI_DATATYPE_NULL, 1); lua_setfield(L, -2, "DATATYPE_NULL");
  luampi_push_MPI_Request(L, MPI_REQUEST_NULL, 1); lua_setfield(L, -2, "REQUEST_NULL");
  luampi_push_MPI_Errhandler(L, MPI_ERRHANDLER_NULL, 1); lua_setfield(L, -2, "ERRHANDLER_NULL");
  luampi_push_MPI_Info(L, MPI_INFO_NULL, 1); lua_setfield(L, -2, "INFO_NULL");


  // Predefined constants
  lua_pushnumber(L, MPI_ANY_SOURCE); lua_setfield(L, -2, "ANY_SOURCE");
  lua_pushnumber(L, MPI_PROC_NULL); lua_setfield(L, -2, "PROC_NULL");
  lua_pushnumber(L, MPI_ROOT); lua_setfield(L, -2, "ROOT");
  lua_pushnumber(L, MPI_ANY_TAG); lua_setfield(L, -2, "ANY_TAG");
  lua_pushnumber(L, MPI_MAX_PROCESSOR_NAME); lua_setfield(L, -2, "MAX_PROCESSOR_NAME");
  lua_pushnumber(L, MPI_MAX_ERROR_STRING); lua_setfield(L, -2, "MAX_ERROR_STRING");
  lua_pushnumber(L, MPI_MAX_OBJECT_NAME); lua_setfield(L, -2, "MAX_OBJECT_NAME");
  lua_pushnumber(L, MPI_UNDEFINED); lua_setfield(L, -2, "UNDEFINED");
  lua_pushnumber(L, MPI_CART); lua_setfield(L, -2, "CART");
  lua_pushnumber(L, MPI_GRAPH); lua_setfield(L, -2, "GRAPH");
  lua_pushnumber(L, MPI_KEYVAL_INVALID); lua_setfield(L, -2, "KEYVAL_INVALID");


  // Collective operations
  luampi_push_MPI_Op(L, MPI_MAX, 1); lua_setfield(L, -2, "MAX");
  luampi_push_MPI_Op(L, MPI_MIN, 1); lua_setfield(L, -2, "MIN");
  luampi_push_MPI_Op(L, MPI_SUM, 1); lua_setfield(L, -2, "SUM");
  luampi_push_MPI_Op(L, MPI_PROD, 1); lua_setfield(L, -2, "PROD");
  luampi_push_MPI_Op(L, MPI_LAND, 1); lua_setfield(L, -2, "LAND");
  luampi_push_MPI_Op(L, MPI_BAND, 1); lua_setfield(L, -2, "BAND");
  luampi_push_MPI_Op(L, MPI_LOR, 1); lua_setfield(L, -2, "LOR");
  luampi_push_MPI_Op(L, MPI_BOR, 1); lua_setfield(L, -2, "BOR");
  luampi_push_MPI_Op(L, MPI_LXOR, 1); lua_setfield(L, -2, "LXOR");
  luampi_push_MPI_Op(L, MPI_BXOR, 1); lua_setfield(L, -2, "BXOR");
  luampi_push_MPI_Op(L, MPI_MINLOC, 1); lua_setfield(L, -2, "MINLOC");
  luampi_push_MPI_Op(L, MPI_MAXLOC, 1); lua_setfield(L, -2, "MAXLOC");


  // Communicators
  luampi_push_MPI_Comm(L, MPI_COMM_WORLD, 1); lua_setfield(L, -2, "COMM_WORLD");
  luampi_push_MPI_Comm(L, MPI_COMM_SELF, 1); lua_setfield(L, -2, "COMM_SELF");


  // Groups
  luampi_push_MPI_Group(L, MPI_GROUP_EMPTY, 1); lua_setfield(L, -2, "GROUP_EMPTY");


  // Results of the compare operations
  lua_pushnumber(L, MPI_IDENT); lua_setfield(L, -2, "IDENT");
  lua_pushnumber(L, MPI_CONGRUENT); lua_setfield(L, -2, "CONGRUENT");
  lua_pushnumber(L, MPI_SIMILAR); lua_setfield(L, -2, "SIMILAR");
  lua_pushnumber(L, MPI_UNEQUAL); lua_setfield(L, -2, "UNEQUAL");


  // MPI Error classes
  lua_pushnumber(L, MPI_SUCCESS); lua_setfield(L, -2, "SUCCESS");
  lua_pushnumber(L, MPI_ERR_BUFFER); lua_setfield(L, -2, "ERR_BUFFER");
  lua_pushnumber(L, MPI_ERR_COUNT); lua_setfield(L, -2, "ERR_COUNT");
  lua_pushnumber(L, MPI_ERR_TYPE); lua_setfield(L, -2, "ERR_TYPE");
  lua_pushnumber(L, MPI_ERR_TAG); lua_setfield(L, -2, "ERR_TAG");
  lua_pushnumber(L, MPI_ERR_COMM); lua_setfield(L, -2, "ERR_COMM");
  lua_pushnumber(L, MPI_ERR_RANK); lua_setfield(L, -2, "ERR_RANK");
  lua_pushnumber(L, MPI_ERR_ROOT); lua_setfield(L, -2, "ERR_ROOT");
  lua_pushnumber(L, MPI_ERR_GROUP); lua_setfield(L, -2, "ERR_GROUP");
  lua_pushnumber(L, MPI_ERR_OP); lua_setfield(L, -2, "ERR_OP");
  lua_pushnumber(L, MPI_ERR_TOPOLOGY); lua_setfield(L, -2, "ERR_TOPOLOGY");
  lua_pushnumber(L, MPI_ERR_DIMS); lua_setfield(L, -2, "ERR_DIMS");
  lua_pushnumber(L, MPI_ERR_ARG); lua_setfield(L, -2, "ERR_ARG");
  lua_pushnumber(L, MPI_ERR_UNKNOWN); lua_setfield(L, -2, "ERR_UNKNOWN");
  lua_pushnumber(L, MPI_ERR_TRUNCATE); lua_setfield(L, -2, "ERR_TRUNCATE");
  lua_pushnumber(L, MPI_ERR_OTHER); lua_setfield(L, -2, "ERR_OTHER");
  lua_pushnumber(L, MPI_ERR_INTERN); lua_setfield(L, -2, "ERR_INTERN");
  lua_pushnumber(L, MPI_ERR_IN_STATUS); lua_setfield(L, -2, "ERR_IN_STATUS");
  lua_pushnumber(L, MPI_ERR_PENDING); lua_setfield(L, -2, "ERR_PENDING");
  lua_pushnumber(L, MPI_ERR_REQUEST); lua_setfield(L, -2, "ERR_REQUEST");
  lua_pushnumber(L, MPI_ERR_LASTCODE); lua_setfield(L, -2, "ERR_LASTCODE");
}


//int luaopen_buffer(lua_State *L);
int luaopen_mpi(lua_State *L)
{
  luaL_Reg mpi_types[] = {
    {"Aint", _MPI_Aint},
    {"Comm", _MPI_Comm},
    {"Comm_copy_attr_function", _MPI_Comm_copy_attr_function},
    {"Comm_delete_attr_function", _MPI_Comm_delete_attr_function},
    {"Datarep_conversion_function", _MPI_Datarep_conversion_function},
    {"Datarep_extent_function", _MPI_Datarep_extent_function},
    {"Datatype", _MPI_Datatype},
    {"Errhandler", _MPI_Errhandler},
    {"File", _MPI_File},
    {"Grequest_cancel_function", _MPI_Grequest_cancel_function},
    {"Grequest_free_function", _MPI_Grequest_free_function},
    {"Grequest_query_function", _MPI_Grequest_query_function},
    {"Group", _MPI_Group},
    {"Info", _MPI_Info},
    {"Offset", _MPI_Offset},
    {"Op", _MPI_Op},
    {"Request", _MPI_Request},
    {"Request", _MPI_Request},
    {"Status", _MPI_Status},
    {"Type_copy_attr_function", _MPI_Type_copy_attr_function},
    {"Type_delete_attr_function", _MPI_Type_delete_attr_function},
    {"User_function", _MPI_User_function},
    {"Win", _MPI_Win},
    {"Win_copy_attr_function", _MPI_Win_copy_attr_function},
    {"Win_delete_attr_function", _MPI_Win_delete_attr_function},
    {NULL, NULL}};

  luaL_newmetatable(L, "MPI::Aint"); lua_pop(L, 1);
  luaL_newmetatable(L, "MPI::Comm"); lua_pop(L, 1);
  luaL_newmetatable(L, "MPI::Comm_copy_attr_function"); lua_pop(L, 1);
  luaL_newmetatable(L, "MPI::Comm_delete_attr_function"); lua_pop(L, 1);
  luaL_newmetatable(L, "MPI::Comm_errhandler_function"); lua_pop(L, 1);
  luaL_newmetatable(L, "MPI::Datarep_conversion_function"); lua_pop(L, 1);
  luaL_newmetatable(L, "MPI::Datarep_extent_function"); lua_pop(L, 1);
  luaL_newmetatable(L, "MPI::Datatype"); lua_pop(L, 1);
  luaL_newmetatable(L, "MPI::Errhandler"); lua_pop(L, 1);
  luaL_newmetatable(L, "MPI::File"); lua_pop(L, 1);
  luaL_newmetatable(L, "MPI::File_errhandler_function"); lua_pop(L, 1);
  luaL_newmetatable(L, "MPI::Grequest_cancel_function"); lua_pop(L, 1);
  luaL_newmetatable(L, "MPI::Grequest_free_function"); lua_pop(L, 1);
  luaL_newmetatable(L, "MPI::Grequest_query_function"); lua_pop(L, 1);
  luaL_newmetatable(L, "MPI::Group"); lua_pop(L, 1);
  luaL_newmetatable(L, "MPI::Info"); lua_pop(L, 1);
  luaL_newmetatable(L, "MPI::Offset"); lua_pop(L, 1);
  luaL_newmetatable(L, "MPI::Op"); lua_pop(L, 1);
  luaL_newmetatable(L, "MPI::Request"); lua_pop(L, 1);
  luaL_newmetatable(L, "MPI::Status"); lua_pop(L, 1);
  luaL_newmetatable(L, "MPI::Type_copy_attr_function"); lua_pop(L, 1);
  luaL_newmetatable(L, "MPI::Type_delete_attr_function"); lua_pop(L, 1);
  luaL_newmetatable(L, "MPI::User_function"); lua_pop(L, 1);
  luaL_newmetatable(L, "MPI::Win"); lua_pop(L, 1);
  luaL_newmetatable(L, "MPI::Win_copy_attr_function"); lua_pop(L, 1);
  luaL_newmetatable(L, "MPI::Win_delete_attr_function"); lua_pop(L, 1);
  luaL_newmetatable(L, "MPI::Win_errhandler_function"); lua_pop(L, 1);

  luaL_register(L,"mpiT",mpi_types);
  luaL_register(L,"mpiT",MPI_module_funcs);
  register_constants(L);
  return 1;
}
