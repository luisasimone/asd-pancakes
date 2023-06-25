#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token.h"

#define MAX 20

int main(int argc, char* argv[]) {
    int L = atoi(argv[1]);
    char nome_file[MAX];
    FILE* fin_grid;
    Grid G = malloc(sizeof(*G));

    strcpy(nome_file, argv[2]);

    fin_grid = fopen(nome_file, "r");

    G = GRIDread(fin_grid);

    fclose(fin_grid);
    return 0;
}
