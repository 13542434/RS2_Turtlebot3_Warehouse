# The minimum version of CMake Required 
cmake_minimum_required (VERSION 3.0.0)

# Change project name
project (RS2_turtlebot3_warehouse)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(BUILD_TESTS ON)
SET(MYDEBUG CACHE STRING "Additional definition" ON)

# find_package(pipes REQUIRED)

# CMake will create your library, add the cpp files needed
add_library(taskallocation taskallocation.cpp order.cpp)
target_link_libraries(taskallocation)

# CMake will create the cell library that you will need 
# add_library(mission mission.cpp)

# CMake will create executable add the cpp files needed
add_executable(main main.cpp)

# Cmake will link against the libraries in final step
target_link_libraries(main taskallocation)

# add_dependencies(a1 pipes::pfmsconnector)
link_directories(/usr/local/lib)

# if(BUILD_TESTS)
#    add_subdirectory(test)
# endif()
