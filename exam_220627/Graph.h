#ifndef EXAM_220627_GRAPH_H
#define EXAM_220627_GRAPH_H

#include <stdlib.h>
#include <stdio.h>

typedef struct graph_s* Graph;
typedef struct edge_s* Edge;

Graph GRAPHinit (int n);
Graph GRAPHload (FILE *fp);
void GRAPHinsert (Graph G, Edge E);
Edge EDGEcreate (int v, int w);
int getV (Graph G);

#endif //EXAM_220627_GRAPH_H
