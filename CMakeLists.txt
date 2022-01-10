cmake_minimum_required(VERSION 3.20)
project(GraphUndirectedMatrix C)

set(CMAKE_C_STANDARD 99)

add_library(libgraph STATIC src/graph.c)

add_executable(graph src/main.c)
add_executable(test src/tests.c)

target_link_libraries(graph libgraph)
target_link_libraries(test libgraph)
