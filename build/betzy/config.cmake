set(CMAKE_CXX_FLAGS "@CXXFLAGS@" CACHE STRING "" FORCE)
set(CMAKE_C_FLAGS "@CFLAGS@" CACHE STRING "" FORCE)

set(CARTEX_RMA "@RMA@" CACHE STRING "" FORCE)
set(CARTEX_RUNTIME "@RUNTIME@" CACHE STRING "" FORCE)
set(CARTEX_UCP "@USEUCX@" CACHE BOOL "" FORCE)
set(CARTEX_FIELD_BY_FIELD "ON" CACHE BOOL "" FORCE)
set(CARTEX_FAT_CALLBACKS "OFF" CACHE BOOL "" FORCE)
set(CARTEX_STAGED_EXCHANGE "ON" CACHE BOOL "" FORCE)

set(HWCART_USE_HWLOC "ON" CACHE BOOL "" FORCE)
set(MPI_CXX_SKIP_MPICXX "TRUE" CACHE BOOL "" FORCE)

set(Boost_INCLUDE_DIR "/cluster/home/marcink/software/boost/1.73" CACHE PATH "" FORCE)
set(HWLOC_INCLUDE_DIR "/cluster/home/marcink/software/hwloc/include" CACHE PATH "" FORCE)
set(HWLOC_LIBRARY "/cluster/home/marcink/software/hwloc/lib/libhwloc.so" CACHE FILEPATH "" FORCE)
set(UCP_INCLUDE_DIR "/cluster/software/hpcx/2.7.0/ucx/mt/include" CACHE PATH "" FORCE)
set(UCP_LIBRARY "/cluster/software/hpcx/2.7.0/ucx/mt/lib/libucp.so" CACHE FILEPATH "" FORCE)
set(XPMEM_INCLUDE_DIR "/cluster/home/marcink/software/xpmem/include" CACHE PATH "" FORCE)
set(XPMEM_LIBRARY "/cluster/home/marcink/software/xpmem/lib/libxpmem.so" CACHE FILEPATH "" FORCE)

set(pkgcfg_lib_PC_HWLOC_hwloc "/usr/lib64/libhwloc.so" CACHE FILEPATH "" FORCE)
set(pkgcfg_lib_PC_UCX_ucp "/cluster/software/hpcx/2.7.0/ucx/mt/lib/libucp.so" CACHE FILEPATH "" FORCE)
set(pkgcfg_lib_PC_UCX_ucs "/cluster/software/hpcx/2.7.0/ucx/mt/lib/libucs.so" CACHE FILEPATH "" FORCE)
set(pkgcfg_lib_PC_UCX_uct "/cluster/software/hpcx/2.7.0/ucx/mt/lib/libuct.so" CACHE FILEPATH "" FORCE)

