#include "Graph.h"

#define MAXC 20

struct graph_s {
    int V;
    int E;
    ST tab;
    int **madj;
};

static Edge EDGEcreate(int v, int w) {
    Edge e;
    e.v = v;
    e.w = w;
    return e;
}

static int **MATRIXint(int r, int c, int val) {
    int i, j, **t;
    t = malloc(r * sizeof(int *));
    if (t==NULL)
        return NULL;

    for (i=0; i < r; i++) {
        t[i] = malloc(c * sizeof(int));
        if (t[i]==NULL)
            return NULL;
    }
    for (i=0; i < r; i++)
        for (j=0; j < c; j++)
            t[i][j] = val;
    return t;
}

Graph GRAPHinit(int V) {
    Graph G = malloc(sizeof *G);
    if (G == NULL)
        return NULL;
    G->V = V;
    G->E = 0;
    G->madj = MATRIXint(V, V, 0);
    if (G->madj == NULL)
        return NULL;
    G->tab = STinit(V);
    if (G->tab == NULL)
        return NULL;
    return G;
}

void GRAPHfree(Graph G) {
    int i;
    for (i=0; i<G->V; i++)
        free(G->madj[i]);
    free(G->madj);
    STfree(G->tab);
    free(G);
}

Graph GRAPHload(FILE *fin) {
    int V, i, id1, id2;
    char label1[MAXC], label2[MAXC];
    Graph G;

    fscanf(fin, "%d", &V);
    G = GRAPHinit(V);

    for (i=0; i<V; i++) {
        fscanf(fin, "%s", label1);
        STinsert(G->tab, label1, i);
    }

    while(fscanf(fin, "%s %s", label1, label2) == 2) {
        id1 = STsearch(G->tab, label1);
        id2 = STsearch(G->tab, label2);
        if (id1 >= 0 && id2 >=0)
            GRAPHinsertE(G, id1, id2);
    }
    return G;
}

static void insertE(Graph G, Edge e) {
    int v = e.v, w = e.w;

    if (G->madj[v][w] == 0)
        G->E++;
    G->madj[v][w] = 1;
}

void GRAPHstore(Graph G, FILE *fout) {
    int i;
    Edge *a;

    a = malloc(G->E * sizeof(Edge));
    if (a == NULL)
        return;

    GRAPHedges(G, a);

    fprintf(fout, "%d\n", G->V);
    for (i = 0; i < G->V; i++)
        fprintf(fout, "%s\n", STsearchByIndex(G->tab, i));

    for (i = 0; i < G->E; i++)
        fprintf(fout, "%s  %s\n", STsearchByIndex(G->tab, a[i].v), STsearchByIndex(G->tab, a[i].w));

}

int GRAPHgetIndex(Graph G, char *label) {
    int id;
    id = STsearch(G->tab, label);
    if (id == -1) {
        id = STsize(G->tab);
        STinsert(G->tab, label, id);
    }
    return id;
}

void GRAPHinsertE(Graph G, int id1, int id2) {
    insertE(G, EDGEcreate(id1, id2));
}

void GRAPHedges(Graph G, Edge *a) {
    int v, w, E = 0;
    for (v=0; v < G->V; v++)
        for (w=0; w < G->V; w++)
            if (G->madj[v][w] == 1)
                a[E++] = EDGEcreate(v, w);
}

Kernel KERNELinit (int N) {
    Kernel K = malloc(sizeof(*K));
    K->N = N;
    K->set = malloc(N * sizeof(int));
    return K;
}

Kernel KERNELload (Graph G, FILE *fp) {
    int cnt=0;
    char c;
    Kernel K = KERNELinit(G->V);

    while (!feof(fp)) {
        fscanf(fp, "%c", &c);
        K->set[cnt] = STsearch(G->tab, &c);
        cnt++;
    }
    K->N = cnt;
    return K;
}

int KERNELvalid (Graph G, Kernel K) {
    int m[G->V];
    int i, j;

    for (i=0; i<K->N; i++) {
        m[i] = 1;
    }

    for (i=1; i<K->N; i++)
        if (G->madj[i-1][i] != 0)
            return 0;

    for (i=0; i<K->N; i++) {
        for (j=0; j<G->V; j++) {
            if (G->madj[i][j] != 0)
                m[i] = 1;
        }
    }

    for (i=0; i<G->V; i++)
        if (m[i] == 0)
            return 0;
    return 1;
}

void KERNELminW (Graph G)  {
    int curr_val=0, best_val=100;
    Kernel sol = KERNELinit(G->V);
    Kernel val = KERNELinit(G->V);
    KERNELmin(G, 0, sol, val, best_val, curr_val, 0, 0);

}

void KERNELcpy (Kernel dst, Kernel src) {
    int i;
    dst->N = src->N;
    dst->set = malloc(src->N * sizeof(int));
    src->set = malloc(src->N * sizeof(int));
    for (i=0; i<src->N; i++)
        dst[i] = src[i];
}

int KERNELcnt (Kernel val) {
    return val->N;
}

void KERNELmin (Graph G, int pos, Kernel sol, Kernel val, int best_val, int curr_val, int start, int cnt_val) {
    int i;
    //terminazione: non ci sono più vertici
    if (start >= G->V) {
        val->N = cnt_val;
        curr_val = KERNELcnt(val);
        if (curr_val < best_val && KERNELvalid(G, val)) {
            best_val = curr_val;
            KERNELcpy(sol, val);
            for (i=0; i<sol->N; i++)
                printf("%s ", STsearchByIndex(G->tab, sol->set[i]));
        }
        return;
    }
    for (i=start; i<G->V; i++) {
        val->set[i] = i;
        cnt_val++;
        KERNELmin(G, pos+1, sol, val, best_val, curr_val, i+1, cnt_val);
        cnt_val--;
    }
    KERNELmin(G, pos, sol, val, best_val, curr_val, G->V, cnt_val);
}

void LONGESTpathW (Graph G, Kernel K) {
    int path[G->V], sol;
    sol = LONGESTpath(G, 0, 0, 0, path, K);
}

int KERNELinclude (Kernel K, int key) {
    int i;
    for (i=0; i<K->N; i++)
        if (K->set[i] == key)
            return 1;
    return 0;
}

int LONGESTpath (Graph G, int pos, int *best_val, int *curr_val, int* path, Kernel K) {
    int i, j;
    //terminazione: pos ha superato il numero di vertici
    if (pos > G->V) {
        if (*curr_val > *best_val)
            *best_val = *curr_val;
        return *best_val;
    }
    for (j=0; j<G->V; j++) {
        if (G->madj[path[pos]][j] != 0) {
            pos++;
            //ricorro non includendo il vertice corrente nel percorso
            if (KERNELinclude(K, j))
                (*curr_val)++;
            LONGESTpath(G, pos, best_val, curr_val, path, K);
            //ricorro includendo il vertice corrente nel percorso
            path[pos] = j;
            if (KERNELinclude(K, j))
                (*curr_val)++;
            LONGESTpath(G, pos, best_val, curr_val, path, K);
        }
    }
}