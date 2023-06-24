#include <stdio.h>
#include <stdlib.h>

#include "Partition.h"

int isValidV (int n, int v) {
    if (v <= n)
        return 1;
    else
        return 0;
}

int cntPartitions (int* p, int nv) {
    int i, max;
    for (i=0; i<nv; i++)
        if (p[i] > max)
            max = p[i];
    return max;
}

int isDominatingSet (int nv, int* p, int i, int np) {
    int k, j, sol[nv],;

    for (i=0; i<np; i++)
        sol[i] = 0;

    k = 0;
    sol[i] = 1;
    while (k != nv) {
        if (p[k] == i) {
            for (j=0; j<nv; j++) {
                if (sol[j] != 1)
                    if (EDGEexists(k, j))
                        sol[j] = 1;
            }
        }
        k++;
    }
    for (j=0; j<np; j++)
        if (sol[j] == 0)
            return 0;
    return 1;
}

int isValidPart (Graph G, int* p) {
    int nv = getV(G);
    int np = cntPartitions(p, nv);
    int i;

    for (i=0; i<np; i++) {
        if (!isDominatingSet(nv, p, i, np))
            return 0;
    }

    return 1;
}

void PARTprop (Graph G, FILE* fp) {
    int p, v, partitions[getV(G)];

    while (!feof(fp)) {
        fscanf(fp, "%d %d", &v, &p);
        if (isValidV(getV(G), v))
            partitions[v] = p;
    }
}