#cmake_minimum_required(VERSION 3.28)
#project(labwork11)
#
#set(CMAKE_CXX_STANDARD 17)
#
#add_executable(labwork11 main.cpp)

cmake_minimum_required(VERSION 3.26)
project(labwork11)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib)
add_subdirectory(bin)

enable_testing()
add_subdirectory(tests)

