cmake_minimum_required(VERSION 2.8)

# The user must set these.
set(NACL_SDK_ROOT "" CACHE PATH "Path to a nacl SDK")

set(TAGLIB_INCLUDE_DIRECTORY "${NACL_SDK_ROOT}/ports/include")
set(TAGLIB_LIBRARY "${NACL_SDK_ROOT}/ports/lib/newlib_pnacl/${CMAKE_BUILD_TYPE}/libtag.a")
set(ZLIB_LIBRARY "${NACL_SDK_ROOT}/ports/lib/newlib_pnacl/${CMAKE_BUILD_TYPE}/libz.a")

set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}")

add_subdirectory(app)
add_subdirectory(nacl)
