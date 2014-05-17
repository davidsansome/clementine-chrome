set(CMAKE_CXX_COMPILER "${NACL_SDK_ROOT}/toolchain/linux_pnacl/bin/pnacl-clang++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Woverloaded-virtual -Wall -Werror -U__STRICT_ANSI__")

link_directories(
  "${NACL_SDK_ROOT}/lib/pnacl/Release"
  "${NACL_SDK_ROOT}/toolchain/linux_pnacl/sdk/lib"
)
include_directories(
  ${TAGLIB_INCLUDE_DIRECTORY}
)
include_directories(SYSTEM "${NACL_SDK_ROOT}/include")


set(SOURCE
  instance.cc
  library.cc
  main.cc
  ppfile_iostream.cc
)

add_executable(clementine ${SOURCE})
target_link_libraries(clementine
  ppapi_cpp
  ppapi
  ${TAGLIB_LIBRARY}
  ${ZLIB_LIBRARY}
)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
  install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/clementine"
    RENAME "clementine.bc"
    DESTINATION "app"
  )
else()
  add_custom_command(
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/clementine.pexe"
    COMMAND "${NACL_SDK_ROOT}/toolchain/linux_pnacl/bin/pnacl-finalize"
    ARGS "${CMAKE_CURRENT_BINARY_DIR}/clementine"
         "-o"
         "${CMAKE_CURRENT_BINARY_DIR}/clementine.pexe"
    DEPENDS clementine
    COMMENT "Finalizing PNaCl bytecode"
  )

  add_custom_target(clementine-pexe ALL
    DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/clementine.pexe")

  install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/clementine.pexe"
    DESTINATION "app"
  )
endif()

install(
  FILES clementine.nmf
  DESTINATION "app"
)
