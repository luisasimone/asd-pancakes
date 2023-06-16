#ifndef EXAM_2_MAP_H
#define EXAM_2_MAP_H

#include <stdlib.h>
#include <stdio.h>

struct map_s {
    int NC;
    int NR;
    int** m;
};

typedef struct map_s* Map;

Map MAPinit(int NR, int NC);
void readFILE(Map m, FILE* fp);

Map MAPinit(int NR, int NC) {
    Map m = malloc(sizeof(*m));
    int i;

    m->NR = NR;
    m->NC = NC;

    m->m = malloc(NC * sizeof(int*));

    for (i=0; i<NC; i++)
        m->m[i] = malloc(NR * sizeof(int));
}

void readFILE(Map m, FILE* fp) {
    int NC, NR, i, j;

    fscanf(fp, "%d %d", &NR, &NC);
    m = MAPinit(NR, NC);

    for (i=0; i<NR; i++) {
        for (j=0; j<NC; j++) {
            fscanf(fp, "%d", &m->m[i][j]);
        }
    }
}

void MAPcpy (Map src, Map dst) {
    int i, j;
    dst->NR = src->NR;
    dst->NC = src->NC;
    for (i=0; i<src->NR; i++) {
        for (j=0; j<src->NC; j++)
            dst->m[i][j] = src->m[i][j];
    }
}

void readPROP(Map m, FILE* fp) {
    Map prop = MAPinit(m->NR, m->NC);
    int x, y;

    MAPcpy(m, prop);

    while (!feof(fp)) {
        fscanf(fp, "%d %d", &x, &y);
    }
}

#endif //EXAM_2_MAP_H
