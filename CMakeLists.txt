cmake_minimum_required(VERSION 3.14)
project(spellcheck)

set(CMAKE_CXX_STANDARD 14)

add_executable(spellcheck src/spellcheck.cpp src/hash.cpp src/functions.cpp)
add_executable(heap src/useHeap.cpp src/hash.cpp src/functions.cpp src/heap.cpp)
add_executable(dijkstra src/findShortestPath.cpp src/hash.cpp src/functions.cpp src/heap.cpp src/dijkstra.cpp)
add_executable(togethertotheend src/TogetherToTheEnd.cpp)