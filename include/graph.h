#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct GraphStructure {
    int numberOfVertices;
    int** matrix;
};

typedef struct GraphStructure *undirectedGraph;
undirectedGraph generateGraph(int numberOfVertices); //создание графа размерности numberOfVertices
int addEdge(int vertex1, int vertex2, undirectedGraph operatingGraph); //добавление ребра между 2 вершинами с определенным весом
int deleteEdge(int vertex1, int vertex2, undirectedGraph operatingGraph); //удаление ребра между 2 вершинами
int addVertex(undirectedGraph operatingGraph); //добавление вершины в граф
void deleteVertex(undirectedGraph operatingGraph, int vertex); //удаление вершины из графа
void deinitializeGraph(undirectedGraph operatingGraph); //деинициализации графа
void deinitializeMatrix(int **matrix, int numberOfVertices); //деинициализации матрицы
void graphToFile(undirectedGraph operatingGraph, FILE *outFile); //печать содержимого графа в файл
int getNumberOfVertices(undirectedGraph operatingGraph); //получение размерности графа
int** getMatrix(undirectedGraph operatingGraph); //получение матрицы графа
void printShortestPath(int startingVertex, int destinationVertex, undirectedGraph graph, FILE *outFile);
void dfs(int startingVertex, int destinationVertex, undirectedGraph graph, int* journey, int* result, int k);
