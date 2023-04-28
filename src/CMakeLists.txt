add_library(gps_lib)

target_sources(gps_lib
  PRIVATE
    gps_lib.cpp
  PUBLIC
    gps_lib.h
  )

target_include_directories(gps_lib
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )

# we use this to get code coverage
# flags are only valid with the GNU compiler and on Linux
if(CMAKE_CXX_COMPILER_ID MATCHES GNU AND CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
  target_compile_options(gps_lib
    PUBLIC
      "--coverage"
    )
  target_link_options(gps_lib
    INTERFACE
      "--coverage"
    )
endif()
