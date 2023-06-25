#include "Item.h"

#include <string.h>

int STsearch (ST st, Key k) {
    int i;
    for (i=0; i<st->N; i++)
        if (strcmp(k, st->rooms[i]->name))
            return i;
}

void STinsert (ST tab, Room room) {
    tab->N++;
    tab->rooms[tab->N] = room;
}
