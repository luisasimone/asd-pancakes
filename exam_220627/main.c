#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

int main() {
    FILE *fp;
    Graph G;

    fp = fopen("g.txt", "r");

    if (fp == NULL)
        exit(1);

    G = GRAPHload(fp);

    fclose(fp);

    return 0;
}
