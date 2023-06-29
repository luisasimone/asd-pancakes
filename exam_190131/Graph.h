#ifndef EXAM_190131_GRAPH_H
#define EXAM_190131_GRAPH_H

#include <stdlib.h>
#include <stdio.h>

#include "ST.h"

struct kernel_s {
    int N;
    int* set;
};

typedef struct edge {
    int v;
    int w;
} Edge;

typedef struct kernel_s* Kernel;
typedef struct graph_s* Graph;

static Edge EDGEcreate(int v, int w);
static int **MATRIXint(int r, int c, int val);
static void insertE(Graph G, Edge e);
static void removeE(Graph G, Edge e);

Graph GRAPHinit (int V);
Graph GRAPHload (FILE *fp);
void GRAPHinsertE(Graph G, int id1, int id2);
void GRAPHedges(Graph G, Edge *a);
Kernel KERNELload (Graph G, FILE *f_in);
void KERNELminW (Graph G);
void KERNELmin (Graph G, int pos, Kernel sol, Kernel val, int best_val, int curr_val, int start, int cnt_val);
void LONGESTpathW (Graph G, Kernel K);
int LONGESTpath (Graph G, int pos, int *best_val, int *curr_val, int* path, Kernel K);

#endif //EXAM_190131_GRAPH_H
