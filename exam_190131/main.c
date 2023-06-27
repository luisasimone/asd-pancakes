#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

#define MAX 20

int main(int argc, char* argv[]) {
    Graph G;
    char file_graph[MAX];
    char file_vertex[MAX];
    char file_output[MAX];
    FILE *f_graph, *f_vertex, *f_output;

    strcpy(file_graph, argv[1]);
    strcpy(file_vertex, argv[2]);
    strcpy(file_output, argv[3]);

    f_graph = fopen(file_graph, "r");
    G = GRAPHload(f_graph);

    return 0;
}
