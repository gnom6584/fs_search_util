cmake_minimum_required(VERSION 3.16)
project(batya_search)

set(CMAKE_CXX_STANDARD 20)
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif()
add_executable(batya_search main.cpp)