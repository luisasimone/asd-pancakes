#include "Graph.h"

struct graph_s {
    int V;
    int E;
    int** madj;
};

struct edge_s {
    int v;
    int w;
};

Graph GRAPHinit (int n) {
    int i;
    Graph G = malloc(sizeof(*G));
    G->V = n;

    G->madj = malloc(G->V * sizeof(int*));

    for (i=0; i<G->V; i++)
        G->madj[i] = malloc(sizeof(int));
}

Graph GRAPHload (FILE *fp) {
    Graph G;
    Edge E;
    int n, i, v, w;

    fscanf(fp, "%d", &n);

    G = GRAPHinit(n);

    for (i=0; i<G->V; i++) {
        fscanf(fp, "%d %d", &v, &w);
        E = EDGEcreate(v, w);
        GRAPHinsert(G, E);
    }
}

int getV (Graph G) {
    return G->V;
}