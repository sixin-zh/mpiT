CMAKE_MINIMUM_REQUIRED(VERSION 2.6 FATAL_ERROR)
CMAKE_POLICY(VERSION 2.6)

FIND_PACKAGE(Torch REQUIRED)

message ("INSTALL mpiT to ${POME}")
SET(MPI_ROOT "${POME}/exe/mpi")
FILE(GLOB LMPI ${MPI_ROOT}/lib/*.so)

SET(src mpiT.c)
SET(luasrc init.lua queue.lua)

ADD_TORCH_PACKAGE(mpiT "${src}" "${luasrc}" "MPI Torch")
TARGET_LINK_LIBRARIES(mpiT luaT TH ${LMPI} ${LMCA} ${LCUDA} ${LCUPTI}) # TH
