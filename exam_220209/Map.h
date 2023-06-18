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

void MAPinit(Map m, int NR, int NC);
void readFILE(Map m, FILE* fp);
void MAPcpy (Map src, Map dst);
dir_e DIRread (char c);
int PATHmaxcnt (Map prop);
int DIRcheck (int x, int y, dir_e dir, Map prop);
void XYupdate (int *x, int *y, dir_e dir, Map prop);
int readPROP(Map m, FILE* fp);
void MAPfill (Map m, int x, int y);
void MAPundo (Map m, int x, int y);
void PATHfindR (int NC, int NR, int pos, int *curr_val, int *best_val, Map m, Map sol) ;
Map PATHfindWr (Map m);

#endif //EXAM_2_MAP_H
