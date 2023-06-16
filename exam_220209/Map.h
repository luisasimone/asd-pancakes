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

typedef enum {n, s, w, o} dir_e;

void MAPinit(Map m, int NR, int NC) {
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
    MAPinit(m, NR, NC);

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

dir_e DIRread (char c) {
    int i;
    char opt[4] = {n, s, w, o};

    for (i=0; i<4; i++) {
        if (c == opt[i])
            return (dir_e) i;
    }
}

int PATHmaxcnt (Map prop) {
    int i, j, cnt=0;

    for (i=0; i<prop->NR; i++) {
        for (j=0; j<prop->NC; j++) {
            if (prop->m[i][j] == 0)
                cnt++;
        }
    }

    return cnt;
}

int DIRcheck (int x, int y, dir_e dir, Map prop) {
    if (dir == n)
        x--;
    if (dir == s)
        x++;
    if (dir == w)
        y--;
    if (dir == o)
        y++;
    if (prop->m[x][y] == 0)
        return 1;
    else
        return 0;
}

void XYupdate (int *x, int *y, dir_e dir, Map prop) {
    if (dir == n)
        (*x)--;
    if (dir == s)
        (*x)++;
    if (dir == w)
        (*y)--;
    if (dir == o)
        (*y)++;
    prop->m[*x][*y] = 1;
}

int readPROP(Map m, FILE* fp) {
    Map prop = malloc(sizeof(*prop));
    MAPinit(prop, m->NR, m->NC);
    char c;
    int cnt, pos=0, change_dir=0, x=0, y=0;
    dir_e dir, *path;

    MAPcpy(m, prop);

    cnt = PATHmaxcnt(prop);
    path = malloc(cnt * sizeof(int));

    while (!feof(fp)) {
        fscanf(fp, "%c", &c);
        dir = DIRread(c);
        if (pos > cnt)
            return change_dir;
        if (DIRcheck(x, y, dir, prop)) {
            if (dir != path[pos])
                change_dir++;
            pos++;
            XYupdate(&x, &y, dir, prop);
        }
        else
            return change_dir;
    }
}



int MAPfill (int NC, Map m, int pos) {
    int x, y;
    x = pos/NC;
    y = pos%NC;
    if (m->m[x][y] == 0) {
        m->m[x][y] = 1;
        return 1;
    }
    else
        return 0;
}

void MAPundo (int NC, Map m, int pos) {
    int x, y;
    x = pos/NC;
    y = pos%NC;
    m->m[x][y] = 0;
}

void PATHfindR (int NC, int NR, int pos, int *curr_val, int *best_val, Map m, Map sol) {
    int x, y;
    x = pos/NC;
    y = pos%NC;
    //terminazione
    if (pos != x+1 || pos != y+1)
        return;
    if (pos > NR*NC) {
        if (*curr_val < *best_val) {
            *best_val = *curr_val;
            MAPcpy(m, sol);
        }
        return;
    }
    //chiamata alla funzione ricorsiva
    if (pos != x && pos != y)
        (*curr_val)++;
    //update
    if (MAPfill(NC, m, pos)) {
        PATHfindR(NC, NR, pos + 1, curr_val, best_val, m, sol);
        //undo
        MAPundo(NC, m, pos);
    }
    //ricorsione
    PATHfindR(NC, NR, pos+1, curr_val, best_val, m, sol);
}

Map PATHfindWr (Map m) {
    Map sol = malloc(sizeof(*sol));
    MAPinit(sol, m->NR, m->NC);
    PATHfindR(m->NC, m->NR, 0, 0, 0, m, sol);
}

#endif //EXAM_2_MAP_H
