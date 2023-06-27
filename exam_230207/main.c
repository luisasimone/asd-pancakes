#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token.h"

#define MAX 20

int main() {
    int L = 3;
    FILE *fin_grid, *fin_bonus;
    Grid G = malloc(sizeof(*G));

    fin_grid = fopen("grid.txt", "r");
    fin_bonus = fopen("bonus.txt", "r");

    G = GRIDread(fin_grid);

    fclose(fin_grid);
    return 0;
}
