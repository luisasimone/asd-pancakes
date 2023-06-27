#include "Graph.h"

struct graph_s {
    int V;
    int E;
    ST st;
    int **madj;
};

Graph GRAPHinit (int V) {

}

Graph GRAPHload (FILE *fp) {

}

Kernel KERNELinit (int N) {

}

Kernel KERNELload (Graph G, FILE *fp) {
    int cnt=0;
    Kernel K = KERNELinit(G->V);

    while (!feof(fp)) {
        fscanf(fp, "%d", &K->set[cnt]);
        cnt++;
    }
    K->N = cnt;
    return K;
}

int KERNELvalid (Graph G, Kernel K) {
    int m[G->V];
    int i, j;

    for (i=0; i<K->N; i++) {
        m[i] = 1;
    }

    for (i=1; i<K->N; i++)
        if (G->madj[i-1][i] != 0)
            return 0;

    for (i=0; i<K->N; i++) {
        for (j=0; j<G->V; j++) {
            if (G->madj[i][j] != 0)
                m[i] = 1;
        }
    }

    for (i=0; i<G->V; i++)
        if (m[i] == 0)
            return 0;
    return 1;
}