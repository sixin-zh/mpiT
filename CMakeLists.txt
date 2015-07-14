CMAKE_MINIMUM_REQUIRED(VERSION 2.6 FATAL_ERROR)
CMAKE_POLICY(VERSION 2.6)

FIND_PACKAGE(Torch REQUIRED)
#FIND_PACKAGE(IBVERBS)

message ("POME is ${POME}")
message ("MPI ROOT is ${MPI_ROOT}")
FILE(GLOB LMPI ${MPI_ROOT}/lib/*.so)
message ("LMPI is ${LMPI}")

SET(src mpiT.c)
SET(luasrc init.lua queue.lua)

ADD_TORCH_PACKAGE(mpiT "${src}" "${luasrc}" "MPI Torch")
TARGET_LINK_LIBRARIES(mpiT luaT TH ${LMPI})
