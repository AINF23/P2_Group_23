cmake_minimum_required(VERSION 3.15)
project(P2_Group_23)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(P2_Group_23 main.cpp)
add_executable (sever sever.cpp)
if(WIN32)
    target_link_libraries(sever ws2_32)
    target_compile_definitions(sever PRIVATE _WIN32_WINNT=0X0A00)
endif()
add_executable(sorting_test test.cpp)