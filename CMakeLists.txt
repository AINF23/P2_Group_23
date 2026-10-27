cmake_minimum_required(VERSION 3.15)
project(P2_Group_23)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(P2_Group_23 ${SOURCES})
target_include_directories(P2_Group_23 PRIVATE src)