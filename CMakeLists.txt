cmake_minimum_required(VERSION 3.08)

set(CMAKE_CXX_STANDARD_REQUIRED 20)
project(SharedMemory)

set(TARGET_HEADER msg.h memory_worker.h process.h)
set(TARGET_SRC msg.cpp memory_worker.cpp process.cpp main.cpp)
add_executable(SharedMemory ${TARGET_SRC} ${TARGET_HEADER})