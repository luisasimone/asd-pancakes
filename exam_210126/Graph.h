#ifndef EXAM_210126_GRAPH_H
#define EXAM_210126_GRAPH_H

#define MAX 20

#include "Item.h"

typedef struct edge_s* Edge;
typedef struct graph_s* Graph;
typedef struct path_s* PATH;

struct path_s {
    int N;
    int tot_gold;
    int tot_treasure;
    Room* rooms;
};

struct edge_s {
    int v;
    int w;
    int wt;
};

struct graph_s {
    int V;
    int E;
    int** madj;
    ST tab;
};


PATH GRAPHpathLoad (Graph G, FILE *fp);
int GRAPHpathCheck(Graph G, PATH p, int M, int PF);
Graph GRAPHinit (int V);
void GRAPHinsertE(Graph G, int id1, int id2, int wt);
Graph GRAPHload (FILE* fp);
int getV (Graph G);
int EDGEsearch (Graph G, int id1, int id2);
PATH GRAPHpathBest(Graph g, int M, int PF);
PATH GRAPHpathBestR(Graph G, int M, int PF, int id, int pos, PATH sol, PATH val);


#endif //EXAM_210126_GRAPH_H
