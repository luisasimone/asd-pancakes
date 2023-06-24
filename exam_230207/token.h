#ifndef EXAM_230207_TOKEN_H
#define EXAM_230207_TOKEN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct token_s {
    char T[2];
} token_t;

struct grid_s {
    int N;
    token_t** grid;
};

typedef struct bonus_s {
    int N;
    token_t* tokens;
    int val;
} bonus_t;

struct bonusblock_s {
    int N;
    bonus_t* block;
};

struct prop_s {
    int N;
    token_t* prop;
};

typedef struct grid_s* Grid;
typedef struct bonusblock_s* BonusBlock;
typedef struct prop_s* Prop;

Grid GRIDinit(FILE* fp);
Grid GRIDread(FILE* fp);
void TOKENadd (Grid G, char token[2], int cnt);
int PROPisValid (Grid G, Prop P);
int TOKENcompare (token_t t1, token_t t2);

#endif //EXAM_230207_TOKEN_H
