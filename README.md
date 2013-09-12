mpiT: MPI for Torch

-- INSTALL Torch
if [ ! -d "build" ]; then mkdir build
fi
pushd build
cmake \
    -DCMAKE_INSTALL_PREFIX="${install_dir}" \
    -DCMAKE_C_COMPILER=/usr/bin/gcc -DCMAKE_CXX_COMPILER=/usr/bin/g++ \
    -DWITH_LUA_JIT=1 \
    ..
make && make install
popd

-- INSTALL mpiT
if [ ! -d "build" ]; then mkdir build
fi
pushd build
cmake \
    -DCMAKE_INSTALL_PREFIX="${install_dir}" \
    -DCMAKE_C_COMPILER=/local/openmpi/bin/mpicc -DCMAKE_CXX_COMPILER=/usr/bin/g++ \
    ..
make && make install
popd


