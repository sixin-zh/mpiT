CMAKE_MINIMUM_REQUIRED(VERSION 2.6 FATAL_ERROR)
CMAKE_POLICY(VERSION 2.6)

FIND_PACKAGE(Torch REQUIRED)
#FIND_PACKAGE(IBVERBS)

message ("MPI ROOT is ${MPI_ROOT}")

IF (APPLE)
	message ("APPLE")
	FILE(GLOB LMPI ${MPI_ROOT}/lib/*.dylib)
ELSE()
	IF(${OPENMPI})
        	message ("LINK openmpi")
        	SET(LMPI "${MPI_ROOT}/lib/liboshmem.so")
        	FILE(GLOB LMCA "${MPI_ROOT}/lib/openmpi/*.so")
	ELSE()
        	FILE(GLOB LMPI ${MPI_ROOT}/lib/*.so)
	ENDIF()
ENDIF()

message ("LMPI is ${LMPI}")
message ("LMCA is ${LMCA}")

SET(src mpiT.c)
SET(luasrc init.lua queue.lua)

ADD_TORCH_PACKAGE(mpiT "${src}" "${luasrc}" "MPI Torch")
TARGET_LINK_LIBRARIES(mpiT luaT TH ${LMPI} ${LMCA})
