#ifndef EXAM_210126_ITEM_H
#define EXAM_210126_ITEM_H

#define MAX 20

typedef struct vertex_s* Room;
typedef struct tab_s* ST;
typedef char* Key;

struct vertex_s {
    char name[MAX];
    int deepness;
    int val_gold;
    int val_treasure;
    int visited;
};

struct tab_s {
    int N;
    Room* rooms;
};

int STsearch (ST st, Key k);
Room STitemSearch(ST st, Key k);
void STinsert (ST tab, Room room);

#endif //EXAM_210126_ITEM_H
