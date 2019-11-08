cmake_minimum_required(VERSION 3.12)
project(SHA_1)

set(CMAKE_CXX_STANDARD 11)

add_executable(SHA_1 main.cpp SHA_1.h SHA_1.cpp)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")