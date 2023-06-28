#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

#define MAX 20

int main() {
    Graph G;
    Kernel K;
    FILE *f_graph, *f_vertex, *f_output;

    f_graph = fopen("graph.txt", "r");
    f_vertex = fopen("vertex.txt", "r");
    G = GRAPHload(f_graph);
    K = KERNELload(G, f_vertex);

    KERNELminW(G);


    return 0;
}
