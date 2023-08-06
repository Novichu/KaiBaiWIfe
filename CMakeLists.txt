
cmake_minimum_required(VERSION 3.10)

project(kaibaiwife)

set(CMAKE_CXX_STANDARD 20)

add_executable(${CMAKE_PROJECT_NAME}  main.cpp)

if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    find_package(Threads)
    target_link_libraries(LiveShare ${CMAKE_THREAD_LIBS_INIT})
endif(CMAKE_SYSTEM_NAME MATCHES "Linux")