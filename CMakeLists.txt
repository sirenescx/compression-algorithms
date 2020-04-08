cmake_minimum_required(VERSION 3.15)
project(kdz)

set(CMAKE_CXX_STANDARD 17)

add_executable(kdz main.cpp huffman.h lz77.h iarchiver.h huffman.cpp lz77.cpp utils.h)