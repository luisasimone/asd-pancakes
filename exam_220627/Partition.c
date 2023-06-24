#include <stdio.h>
#include <stdlib.h>

#include "Partition.h"

int isValidV (int n, int v) {
    if (v <= n)
        return 1;
    else
        return 0;
}

int cntPartitions (Partition P) {
    int i, max;
    for (i=0; i<P->tot_v; i++)
        if (P->p[i] > max)
            max = P->p[i];
    return max;
}

int isDominatingSet (Partition P, int i) {
    int k, j, sol[P->tot_v];

    for (i=0; i<P->n_part; i++)
        sol[i] = 0;

    k = 0;
    sol[i] = 1;
    while (k != P->tot_v) {
        if (P->p[k] == i) {
            for (j=0; j<P->tot_v; j++) {
                if (sol[j] != 1)
                    if (EDGEexists(k, j))
                        sol[j] = 1;
            }
        }
        k++;
    }
    for (j=0; j<P->n_part; j++)
        if (sol[j] == 0)
            return 0;
    return 1;
}

int isValidPart (Graph G, Partition P) {
    int i;

    for (i=0; i<P->tot_v; i++) {
        if (!isDominatingSet(P, i))
            return 0;
    }

    return 1;
}

void PARTprop (Graph G, FILE* fp) {
    int p, v;
    Partition P = malloc(sizeof(*P));
    P->tot_v = getV(G);
    P->p = malloc(P->tot_v * sizeof(int*));

    while (!feof(fp)) {
        fscanf(fp, "%d %d", &v, &p);
        if (isValidV(P->tot_v, v))
            P->p[v] = p;
    }
    P->n_part = cntPartitions(P);
}

void PARTcpy (Partition dst, Partition src) {
    int i;
    dst->n_part = src->n_part;
    for (i=0; i<dst->n_part; i++)
        dst->p[i] = src->p[i];
}

void SP_rec (Graph G, int m, int pos, Partition sol, Partition val) {
    int i;
    //terminazione
    if (pos >= sol->tot_v) {
        if (isValidPart(G, val)) {
            if (val->n_part > sol->n_part)
                PARTcpy(sol, val);
        }
        return;
    }
    //ricorsione con pos+1
    for (i=0; i<m; i++) {
        val->p[pos] = i;
        SP_rec(G, m, pos+1, sol, val);
    }
    //ricorsione m+1 e pos+1
    val->p[pos] = m;
    SP_rec(G, m+1, pos+1, sol, val);
}

void PARTfind (Graph G) {
    Partition sol = malloc(sizeof(*sol));
    Partition val = malloc(sizeof(*val));
    sol->tot_v = val->tot_v = getV(G);
    SP_rec(G, 1, 0, sol, val);
}