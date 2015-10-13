package = "mpiT"
version = "openmpi-1"
source = {
url = "https://github.com/sixin-zh/mpiT",
tag = "master"
}
description = {
summary = "MPI for Torch",
}
dependencies = {
"torch >= 7.0",
"sys >= 1.0",
}
build = {
type = "command",
build_command = [[
cmake -E make_directory build && cd build && cmake .. \
-DCMAKE_C_COMPILER=${MPI_PREFIX}/bin/mpicc -DCMAKE_CXX_COMPILER=${MPI_PREFIX}/bin/mpicxx \
-DMPI_ROOT=${MPI_PREFIX} \
-DOPENMPI=1 \
-DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH="$(LUA_BINDIR)/.." -DCMAKE_INSTALL_PREFIX="$(PREFIX)" && $(MAKE)
]],
install_command = "cd build && $(MAKE) install"
}
