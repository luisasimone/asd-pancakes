#include "Graph.h"

#include <stdlib.h>
#include <stdio.h>

struct graph_s {
    int V;
    int E;
    int** madj;
    int* mark;
    ST st;
};

struct edge_s {
    int v;
    int w;
};

Graph GRAPHinit (int V) {
    int i;
    Graph G = malloc(sizeof(*G));
    G->V = V;
    G->E = 0;
    //allocazione matrice
    G->mark = malloc(G->V * sizeof(int));

    for (i=0; i<G->V; i++)
        G->mark[i] = 0;
}

Graph GRAPHload (FILE *fp) {

}

void GRAPHkcoreW (Graph G, int k) {
    int i;
    if (GRAPHkcore(G, k)) {
        for (i = 0; i < G->V; i++)
            if (G->mark[i] == 0)
                printf("%d ", G->mark[i]);
    }
    else
        printf("Non esiste il %d-core del grafo", k);
}

int EDGEScnt (Graph G, int v) {
    int i, cnt=0;
    for (i=0; i<G->V; i++)
        if (G->madj[v][i] == 1 && G->mark[i] != 1)
            cnt++;

    return cnt;
}

int GRAPHkcore (Graph G, int k) {
    int i, flag=0;

    do {
        for (i = 0; i < G->V; i++) {
            if (G->mark[i] == 0) {
                if (EDGEScnt(G, i) < k) {
                    G->mark[i] = 1;
                    flag = 1;
                }
            }
        }
    } while(flag);

    return 1;
}

int GRAPHisConnected (Graph G) {
    if (GRAPHcc(G) == 1)
        return 1;
    else
        return 0;
}

void GRAPHjConnectedW (Graph G, int j) {
    Graph val = malloc(sizeof(*val));
    GRAPHcpy(val, G);
    Edge sol[j];
    GRAPHjConnectedR(val, j, 0, 0, sol);
}

void GRAPHjConnectedR (Graph val, int j, int pos, int cnt, Edge* sol) {
    int i, R, C;
    //terminazione: il grafo è sconnesso
    if (!GRAPHisConnected(val) || pos > (val->V) * (val->V)) {
        if (cnt == j)
            EDGEprintSol(sol);
        return;
    }
    //ricorsione: elimino l'arco
    for (i=0; i<(val->V)*(val->V); i++) {
        R = pos/val->V;
        C = pos%val->V;
        if (val->madj[R][C]!=0) {
            //elimino l'arco corrente
            val->madj[R][C] = 0;
            cnt++;
            EDGEadd(R, C, sol);
            GRAPHjConnectedR(val, j, pos+1, cnt, sol);
            //ripristino l'arco eliminato
            val->madj[R][C] = 1;
            EDGEremove(R, C, sol);
        }
        //ricorro per saltare l'arco corrente
        GRAPHjConnectedR(val, j, pos+1, cnt, sol);
    }
}