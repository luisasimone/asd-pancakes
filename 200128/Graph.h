#ifndef INC_200128_GRAPH_H
#define INC_200128_GRAPH_H

struct st_s {
    char** name;
    int maxN;
    int N;
};

typedef struct st_s *ST;
typedef struct graph_s *Graph;
typedef struct edge_s *Edge;

void GRAPHkcoreW (Graph G, int k);
int GRAPHkcore (Graph G, int k);
void GRAPHjConnectedR (Graph val, int j, int pos, int cnt, Edge* sol);
void EDGEadd (int R, int C, Edge* sol);
void EDGEremove (int R, int C, Edge* sol);

#endif //INC_200128_GRAPH_H
