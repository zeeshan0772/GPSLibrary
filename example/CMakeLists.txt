cmake_minimum_required(VERSION 3.13)

project(MyProject)

# Set the directory paths
set(SRC_DIR ${CMAKE_SOURCE_DIR}/../src)

# Add the main executable target
add_executable(MyProject main.cpp)

# Add the gps_lib target
add_library(gps_lib ${SRC_DIR}/gps_lib.cpp)

# Add the include directories for the gps_lib target
target_include_directories(gps_lib PUBLIC ${SRC_DIR})

# Link the gps_lib target to the main executable target
target_link_libraries(MyProject gps_lib)
