cmake_minimum_required(VERSION 3.14)
project(spellcheck)

set(CMAKE_CXX_STANDARD 14)

add_executable(main src/spellcheck.cpp src/hash.cpp)