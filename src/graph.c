#include "../include/graph.h"

// Создание графа
undirectedGraph generateGraph(int numberOfVertices) {
    undirectedGraph operatingGraph;
    operatingGraph = malloc(numberOfVertices * sizeof(int *));
    operatingGraph->numberOfVertices = numberOfVertices;
    operatingGraph->matrix = (int **) malloc(numberOfVertices * sizeof(int *));

    for (int i = 0; i < numberOfVertices; i++) {
        operatingGraph->matrix[i] = (int *) malloc(numberOfVertices * sizeof(int));
    }

    for (int i = 0; i < numberOfVertices; i++) {
        for (int j = 0; j < numberOfVertices; j++) {
            operatingGraph->matrix[i][j] = 0;
        }
    }

    return operatingGraph;
}

// Добавление ребра
int addEdge(int vertex1, int vertex2, undirectedGraph operatingGraph) {
    if ((vertex2 < operatingGraph->numberOfVertices) && (vertex1 < operatingGraph->numberOfVertices)) {
        operatingGraph->matrix[vertex1][vertex2] = 1;
        operatingGraph->matrix[vertex2][vertex1] = 1;
    }
    else {
        printf("\nCouldn't add an edge\n");
        return -1;
    }
}

// Удаление ребра
int deleteEdge(int vertex1, int vertex2, undirectedGraph operatingGraph) {
    if ((vertex2 < operatingGraph->numberOfVertices) && (vertex1 < operatingGraph->numberOfVertices)) {
        operatingGraph->matrix[vertex1][vertex2] = 0;
        operatingGraph->matrix[vertex2][vertex1] = 0;
    }
    else {
        printf("\nCouldn't delete an edge\n");
        return -1;
    }
}

// Деинициализации матрицы
void deinitializeMatrix(int **matrix, int numberOfVertices) {
    for (int i = 0; i < numberOfVertices; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Деинициализации графа
void deinitializeGraph(undirectedGraph operatingGraph) {
    deinitializeMatrix(operatingGraph->matrix, operatingGraph->numberOfVertices);
    free(operatingGraph);
}

// Добавление вершины
int addVertex(undirectedGraph operatingGraph) {
    int numberOfVertices = operatingGraph->numberOfVertices + 1;
    int **matrix = (int **) realloc(operatingGraph->matrix, numberOfVertices * sizeof(int *));

    for(int i = 0; i < numberOfVertices; i++) {
        matrix[i] = (int *) malloc(numberOfVertices * sizeof(int));
    }

    for (int i = 0; i < numberOfVertices; i++) {
        for (int j = 0; j < numberOfVertices; j++) {
            if ((j == numberOfVertices - 1) || (i == numberOfVertices - 1)) matrix[i][j] = 0;
            else matrix[i][j] = operatingGraph->matrix[i][j];
        }
    }

    deinitializeMatrix(operatingGraph->matrix, operatingGraph->numberOfVertices);
    operatingGraph->matrix = matrix;
    operatingGraph->numberOfVertices = numberOfVertices;
    return numberOfVertices;
}

// Удаление вершины
void deleteVertex(undirectedGraph operatingGraph, int vertex) {
    int **matrix = (int **) malloc(operatingGraph->numberOfVertices * sizeof(int *));
    int shift = 0;

    for (int i = 0; i < operatingGraph->numberOfVertices; i++) {
        matrix[i] = (int *) malloc(operatingGraph->numberOfVertices * sizeof(int));
    }

    for (int i = 0; i < operatingGraph->numberOfVertices; i++) {
        matrix[vertex][i] = 0;
        matrix[i][vertex] = 0;
    }

    deinitializeMatrix(operatingGraph->matrix, operatingGraph->numberOfVertices);
    operatingGraph->matrix = matrix;
}

// Вывод определенного графа в виде матрицы
void graphToFile(undirectedGraph operatingGraph, FILE *outFile) {
    fprintf(outFile, "Matrix of %d x %d:\n\n", operatingGraph->numberOfVertices, operatingGraph->numberOfVertices);
    fprintf(outFile, "  |");

    for (int i = 0; i < operatingGraph->numberOfVertices; i++) {
        fprintf(outFile, " %d |", i);
    }

    fprintf(outFile, "\n");
    fprintf(outFile, "  |---|---|---|---|---|");
    fprintf(outFile, "\n");

    for (int i = 0; i < operatingGraph->numberOfVertices; i++) {
        for (int j = 0; j < operatingGraph->numberOfVertices; j++) {
            if (j == 0) fprintf(outFile, "%d |", i);
            fprintf(outFile, " %d |", operatingGraph->matrix[i][j]);
        }
        fprintf(outFile, "\n");
    }
}

// Получение размерности графа
int getNumberOfVertices(undirectedGraph operatingGraph) {
    return operatingGraph->numberOfVertices;
}

// Получение матрицы графа
int** getMatrix(undirectedGraph operatingGraph) {
    return operatingGraph->matrix;
}

int* shortestPath(int startingVertex, int destinationVertex, undirectedGraph graph) {
    int* result = (int*) malloc(graph->numberOfVertices * sizeof(int*));
    printf("%d;", sizeof(result));
    printf("\n");

    int* journey = (int*) malloc(graph->numberOfVertices * sizeof(int*));
    dfs(startingVertex, destinationVertex, graph, journey, result, 0);
    return result;
}

void dfs(int startingVertex, int destinationVertex, undirectedGraph graph, int* journey, int* result, int k) {
    journey[k] = startingVertex;

    if (startingVertex != destinationVertex) {

        for (int i = 0; i < graph->numberOfVertices; i++) {
            bool stop = false;
            for (int j = 0; j < graph->numberOfVertices; j++) {
                if (graph->matrix[startingVertex][i] != 1 || i == journey[j]) stop = true;
            }
            if (!stop) dfs(i, destinationVertex, graph, journey, result, k + 1);
        }
    }

    if (startingVertex == destinationVertex) {

    }
}

