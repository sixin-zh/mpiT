// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// MPI for Torch
// adapted from lua-mpi: https://github.com/jzrake/lua-mpi
// Author: Sixin Zhang (zsx@cims.nyu.edu)

#include <luaT.h>
#include <lua-mpi.h>

DLL_EXPORT int luaopen_libmpiT(lua_State *L) {
  luaopen_mpi(L);
  return 1;
}
