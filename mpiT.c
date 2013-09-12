// The Lua MPI wrappers for Torch
// based on lua-mpi: https://github.com/jzrake/lua-mpi‎
// Author: Sixin Zhang (zsx@cims.nyu.edu)

#include <TH.h>
#include <luaT.h>
#include <lua-mpi.h>

DLL_EXPORT int luaopen_libmpiT(lua_State *L) {
  luaopen_mpi(L);
  return 1;
}
