#ifndef EXAM_190131_GRAPH_H
#define EXAM_190131_GRAPH_H

#include <stdlib.h>
#include <stdio.h>

struct kernel_s {
    int N;
    int* set;
};

typedef struct kernel_s* Kernel;
typedef struct graph_s* Graph;

Graph GRAPHinit (int V);
Graph GRAPHload (FILE *fp);

#endif //EXAM_190131_GRAPH_H
