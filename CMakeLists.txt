cmake_minimum_required(VERSION 3.20)
project(GraphUndirectedMatrix C)

set(CMAKE_C_STANDARD 99)

add_library(libgraph STATIC src/graph.c)

add_executable(graph include/graph.h  src/main.c  src/graph.c)
add_executable(test include/tests.h src/tests.c)

target_link_libraries(graph libgraph)
target_link_libraries(test libgraph)
