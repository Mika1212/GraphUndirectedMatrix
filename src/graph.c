#include "../include/graph.h"

// Создание графа
undirectedGraph generateGraph(int numberOfVertices) {
    undirectedGraph operatingGraph;
    operatingGraph = malloc(sizeof(struct GraphStructure));
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
    return 0;
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
    return 0;
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
    operatingGraph->numberOfVertices = numberOfVertices;

    operatingGraph->matrix = (int **) realloc(operatingGraph->matrix, numberOfVertices * numberOfVertices * sizeof(int *));
    operatingGraph->matrix[numberOfVertices - 1] = (int *) malloc(numberOfVertices * sizeof(int));

    for (int i = 0; i < numberOfVertices; i++) {
        for (int j = 0; j < numberOfVertices; j++) {
            if ((j == numberOfVertices - 1) || (i == numberOfVertices - 1)) operatingGraph->matrix[i][j] = 0;
        }
    }

    return numberOfVertices;
}

// Удаление вершины
void deleteVertex(undirectedGraph operatingGraph, int vertex) {
    for (int i = 0; i < operatingGraph->numberOfVertices; i++) {
        deleteEdge(vertex, i, operatingGraph);
        deleteEdge(i, vertex, operatingGraph);
    }
}

// Вывод определенного графа в виде матрицы
void graphToFile(undirectedGraph operatingGraph, FILE *outFile) {
    fprintf(outFile, "Matrix of %d x %d:\n\n", operatingGraph->numberOfVertices, operatingGraph->numberOfVertices);
    fprintf(outFile, "  |");

    for (int i = 0; i < operatingGraph->numberOfVertices; i++) {
        fprintf(outFile, " %d |", i);
    }

    fprintf(outFile, "\n");
    fprintf(outFile, "  ");
    for (int i = 0; i < operatingGraph->numberOfVertices; i++) {
        fprintf(outFile, "|---");
    }
    fprintf(outFile, "|");
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

// Поиск самого короткого пути из одной заданной точки в другую
int* findShortestPath(int startingVertex, int destinationVertex, undirectedGraph graph, FILE *outFile) {
    int* result = (int*) malloc(graph->numberOfVertices * sizeof(int*));
    int* journey = (int*) malloc(graph->numberOfVertices * sizeof(int*));
    for (int i = 0; i < graph->numberOfVertices; i++) {
        result[i] = INT_MIN;
        journey[i] = INT_MIN;
    }

    dfs(startingVertex, destinationVertex, graph, journey, result, 0);

    bool flag = false;
    for (int i = 0; i < graph->numberOfVertices; i++) {
        if (result[i] == destinationVertex) flag = true;
    }
    if (!flag) {
        for (int i = 0; i < graph->numberOfVertices; i++) {
            result[i] = -1;
        }
    }

    printShortestPath(result, startingVertex, destinationVertex, outFile);
    return result;
}

//Вывод в файл самого короткого пути из одной заданной точки в другую
void printShortestPath(int* result, int startingVertex, int destinationVertex, FILE *outFile) {
    if (result[0] == -1) {
        fprintf(outFile, "Can't reach vertex %d from vertex %d", destinationVertex, startingVertex);
        return;
    }

    int i = 0;
    fprintf(outFile, "\n");
    fprintf(outFile, "Shortest path from %d to %d is: ", startingVertex, destinationVertex);

    do {
        fprintf(outFile, "%d ", result[i]);
        i++;
    } while (result[i - 1] != destinationVertex);
}

// Поиск в глубину
void dfs(int startingVertex, int destinationVertex, undirectedGraph graph, int* journey, int* result, int k) {
    journey[k] = startingVertex;

    if (startingVertex != destinationVertex) {

        for (int i = 0; i < graph->numberOfVertices; i++) {
            for (int j = k + 1; j < graph->numberOfVertices - k; j++) {
                journey[j] = INT_MIN;
            }

            bool stop = false;
            for (int j = 0; j < graph->numberOfVertices; j++) {
                if (graph->matrix[startingVertex][i] != 1 || i == journey[j]) stop = true;
            }

            if (!stop) dfs(i, destinationVertex, graph, journey, result, k + 1);
        }
    } else {
        bool change = false;
        for (int i = 0; i < graph->numberOfVertices; i++) {
            if (result[0] == INT_MIN && journey[i] != INT_MIN ||
            result[i] > -1 && journey[i] == INT_MIN) change = true;
        }
        if (change) {
            for (int i = 0; i < graph->numberOfVertices; i++) {
                result[i] = journey[i];
            }
        }
    }
}
