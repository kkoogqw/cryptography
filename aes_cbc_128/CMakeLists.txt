cmake_minimum_required(VERSION 3.12)
project(AES_128_CBC)

set(CMAKE_CXX_STANDARD 14)

add_executable(AES_128_CBC AES_128_key.cpp AES_128_key.h AES_128.h AES_128.cpp AES_128_CBC.h AES_128_CBC.cpp AES_128_encrypt.h AES_128_encrypt.cpp AES_128_decrypt.h AES_128_decrypt.cpp run.cpp test.cpp)