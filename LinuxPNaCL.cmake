# Used for cross-compiling taglib.

SET(_pnacl_prefix "$ENV{NACL_SDK_ROOT}/toolchain/linux_pnacl/bin/pnacl-")

# the name of the target operating system
SET(CMAKE_SYSTEM_NAME Linux)

# which compilers to use for C and C++
SET(CMAKE_C_COMPILER "${_pnacl_prefix}clang")
SET(CMAKE_CXX_COMPILER "${_pnacl_prefix}clang++")
SET(CMAKE_LINKER "${_pnacl_prefix}clangld")
SET(CMAKE_AR "${_pnacl_prefix}ar" CACHE FILEPATH "Archiver")
SET(CMAKE_RANLIB "${_pnacl_prefix}ranlib" CACHE FILEPATH "Ranlib")

set(SIZEOF_WCHAR_T 4)
set(CMAKE_SIZEOF_UNSIGNED_SHORT 2)
set(CMAKE_SIZEOF_UNSIGNED_INT 4)
set(CMAKE_SIZEOF_UNSIGNED_LONG 4)
set(HAVE_IS_BIG_ENDIAN On)
set(IS_BIG_ENDIAN Off)
