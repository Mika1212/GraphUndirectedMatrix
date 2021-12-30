#include <stdio.h>
#include <stdlib.h>
#include "../include/graph.h"
#include "../include/tests.h"

/*
    Параметры командной строки:
 1) numberOfVertices количество вершин;
 2) numberOfEdges количетсво переходов из одной вершины в другую (граф ненаправленный, следовательно движение в обе стороны);
 3) data входные занчения переходов по номерам вершин;
 4) outputFile выходные значения, итоговая матрица;
 5) -t тестирование;
 6) -f (номер стартовой вершины) (номер конечной вершины) поиск кратчайшего пути до всех вершин;
 5 и 6 пункты опциональны и используется либо один, либо другой, нельзя использовать сразу оба.
 */

int main(int argc, char *argv[]) {
    if ((argc < 5) || (argc > 8)) {
        printf("\nOops, something went wrong with arguments\n");
        return -1;
    }

    if ((argc == 6) && (*argv[5] == *"-t")) {
        StartTests();
        return 0;
    }

    int numberOfVertices, numberOfEdges;
    sscanf(argv[1], "%d", &numberOfVertices);
    sscanf(argv[2], "%d", &numberOfEdges);
    numberOfEdges *= 2;

    int *edges = (int *) malloc(numberOfEdges * sizeof(int));
    FILE *data;
    FILE *outFile;

    data = fopen(argv[3], "r");
    for (int i = 0; !feof(data); i++) {
        fscanf(data, "%d", &edges[i]);
    }

    undirectedGraph operatingGraph = generateGraph(numberOfVertices);
    for (int k = 0; k < numberOfEdges; k += 2) {
        addEdge(edges[k], edges[k + 1], operatingGraph);
    }

    free(edges);
    fclose(data);

    outFile = fopen(argv[4], "w");
    graphToFile(operatingGraph, outFile);


    if ((argc == 8) && (*argv[5] == *"-f") ) {
        int startingVertex;
        sscanf(argv[6], "%d", &startingVertex);
        int endingVertex;
        sscanf(argv[7], "%d", &endingVertex);
        if (startingVertex < numberOfVertices && endingVertex < numberOfVertices) {
            printShortestPath(startingVertex, endingVertex, operatingGraph, outFile);
        } else {
            printf("\nOops, something went wrong with arguments\n");
            return -1;
        }
    }

    fclose(outFile);
    deinitializeGraph(operatingGraph);
    return 0;
}
