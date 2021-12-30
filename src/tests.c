#include <assert.h>
#include "../include/graph.h"

void createGraphTest() {
    int size = 4;
    undirectedGraph graph = generateGraph(size);
    assert(getNumberOfVertices(graph) == size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            assert(graph->matrix[i][j] == 0);
        }
    }
    deinitializeGraph(graph);
}

void addEdgeTest() {
    int size = 4;
    undirectedGraph graph = generateGraph(size);
    addEdge(0, 1, graph);
    assert(graph->matrix[0][1] == 1);
    assert(graph->matrix[1][0] == 1);
    addEdge(2, 3, graph);
    assert(graph->matrix[2][3] == 1);
    assert(graph->matrix[3][2] == 1);
    deinitializeGraph(graph);
}

void deleteEdgeTest() {
    int size = 4;
    undirectedGraph graph = generateGraph(size);
    addEdge(0, 1, graph);
    assert(graph->matrix[0][1] == 1);
    assert(graph->matrix[1][0] == 1);
    addEdge(2, 3, graph);
    deleteEdge(0, 1, graph);
    assert(graph->matrix[0][1] == 0);
    assert(graph->matrix[1][0] == 0);
    assert(graph->matrix[2][3] == 1);
    assert(graph->matrix[3][2] == 1);
    deinitializeGraph(graph);
}

void addVertexTest() {
    int size = 4;
    undirectedGraph graph = generateGraph(size);
    addEdge(0, 1, graph);
    addEdge(2, 3, graph);
    addNode(graph);
    addEdge(0, 4, graph);
    addEdge(3, 4, graph);
    assert(getNumberOfVertices(graph) == 5);
    assert(graph->matrix[1][4] == 0);
    assert(graph->matrix[0][4] == 1);
    assert(graph->matrix[3][4] == 1);
    deinitializeGraph(graph);
}

void deleteVertexTest() {
    int size = 4;
    undirectedGraph graph = generateGraph(size);
    addEdge(0, 1, graph);
    addEdge(0, 2, graph);
    addEdge(0, 3, graph);
    addEdge(1, 3, graph);
    addEdge(2, 3, graph);
    deleteVertex(graph, 2);
    assert(getNumberOfVertices(graph) == 3);
    assert(graph->matrix[0][1] == 1);
    assert(graph->matrix[0][2] == 1);
    assert(graph->matrix[1][0] == 1);
    assert(graph->matrix[1][2] == 1);
    assert(graph->matrix[1][2] == 1);
    deinitializeGraph(graph);
}

int StartTests() {
    createGraphTest();
    addEdgeTest();
    deleteEdgeTest();
    addVertexTest();
    deleteVertexTest();
    return 0;
}
