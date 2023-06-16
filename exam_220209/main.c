#include <stdio.h>

#include "Map.h"

int main() {
    Map m;

    FILE *fp;
    fp = fopen("griglia.txt", "r");

    readFILE(m, fp);

    fclose(fp);
    return 0;
}
