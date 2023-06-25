#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Graph.h"
#include "Item.h"

#define MAX 20



Graph GRAPHinit (int V) {

}

void GRAPHinsertE(Graph G, int id1, int id2, int wt) {
    G->madj[id1][id2] = wt;
}

Graph GRAPHload (FILE* fp) {
    Graph G = malloc(sizeof(*G));
    int n, i, id1, id2, trap;
    char name1[MAX], name2[MAX];
    Room room = malloc(sizeof(*room));

    fscanf(fp, "%d", &G->V);
    G = GRAPHinit(G->V);
    for (i=0; i<G->V; i++) {
        fscanf(fp, "%s %d %d %d", room->name, &room->deepness, &room->val_gold, &room->val_treasure);
        STinsert(G->tab, room);
    }
    while (!feof(fp)) {
        fscanf(fp, "%s %s %d", name1, name2, &trap);
        id1 = STsearch(G->tab, name1);
        id2 = STsearch(G->tab, name2);
        GRAPHinsertE(G, id1, id2, trap);
    }
}

int EDGEsearch (Graph G, int id1, int id2) {
    return G->madj[id1][id2];
}

int getV (Graph G) {
    return G->V;
}

PATH GRAPHpathLoad (Graph G, FILE *fp) {
    int cnt=0;
    Room item;
    char name[MAX];
    PATH path = malloc(sizeof(*path));
    path->rooms = malloc(getV(G) * sizeof(Room));
    while (!feof(fp)) {
        fscanf(fp, "%s", name);
        item = STitemSearch(G->tab, name);
        path->rooms[cnt] = item;
        cnt++;
    }
    path->rooms = malloc(cnt * sizeof(Room));
    return path;
}

int GRAPHpathCheck(Graph G, PATH p, int M, int PF) {
    int i, id1, id2;
    //da controllare:
    //che esistano gli archi tra i vertici
    //che il numero di mosse non superi il numero di vertici nel percorso
    //se il numero di mosse è uguale al numero di vertici, controllare che l'esploratore si trovi in una stanza di livello 1 o 2 per poter essere salvato
    //che il numero di punti ferita non venga azzerato dalle trappole

    for (i=1; i<p->N; i++) {
        if (M > p->N)
            return 0;
        id1 = STsearch(G->tab, p->rooms[i-1]->name);
        id2 = STsearch(G->tab, p->rooms[i]->name);
        if ((EDGEsearch(G, id1, id2))!=0) {
            PF -= EDGEsearch(G, id1, id2);
            if (M == p->N || PF <= 0) {
                if (p->rooms[i]->deepness == 3)
                    return 0;
            }
            if (p->rooms[i]->visited == 0) {
                p->tot_gold += p->rooms[i]->val_gold;
                if (p->rooms[i]->val_treasure > p->tot_treasure)
                    p->tot_treasure = p->rooms[i]->val_treasure;
                p->rooms[i]->visited = 1;
            }
        }
    }
    return 1;
}

void PATHcpy (PATH dst, PATH src) {

}

PATH GRAPHpathBest(Graph G, int M, int PF) {
    PATH sol = malloc(sizeof(*sol));
    PATH val = malloc(sizeof(*val));
    sol = GRAPHpathBestR(G, M, PF, 0, 0, sol, val);
}

PATH GRAPHpathBestR(Graph G, int M, int PF, int id, int pos, PATH sol, PATH val) {
    int i, prec_treasure=0;
    //terminazione:
    //PF o mosse finite
    if (M <= 0 || PF <= 0) {
        //salvataggio possibile
        if(G->tab->rooms[id]->deepness != 3) {
            if ((val->tot_treasure + val->tot_gold) > (sol->tot_treasure + sol->tot_gold)) {
                sol->tot_treasure = val->tot_treasure;
                sol->tot_gold = val->tot_gold;
                PATHcpy(sol, val);
                return sol;
            }
        }
    }
    //ricorsione: prendi il tesoro della stanza
    if (G->tab->rooms[id]->val_treasure > val->tot_treasure && val->rooms[pos]->visited == 0) {
        prec_treasure = val->tot_treasure;
        val->tot_treasure = G->tab->rooms[id]->val_treasure;
        val->tot_gold += G->tab->rooms[id]->val_gold;
        val->rooms[pos] = G->tab->rooms[id];
        val->rooms[pos]->visited = 1;
        for (i=0; i<G->V; i++) {
            if (G->madj[id][i] != 0) {
                GRAPHpathBestR(G, M - 1, PF - (G->madj[id][i]), i, pos+1, sol, val);
            }
        }
        //undo
        val->tot_treasure = prec_treasure;
        val->tot_gold -= G->tab->rooms[id]->val_gold;
        val->rooms[pos]->visited = 0;
    }
    //ricorsione: non prendere il tesoro della stanza / non c'è un tesoro nella stanza
    else if (G->tab->rooms[id]->val_treasure <= val->tot_treasure || val->rooms[pos]->visited != 0) {
        val->tot_gold += G->tab->rooms[id]->val_gold;
        val->rooms[pos] = G->tab->rooms[id];
        val->rooms[pos]->visited = 1;
        for (i = 0; i < G->V; i++) {
            if (G->madj[id][i] != 0) {
                GRAPHpathBestR(G, M - 1, PF - (G->madj[id][i]), i, pos+1, sol, val);
            }
        }
        //
        val->tot_treasure = prec_treasure;
        val->tot_gold -= G->tab->rooms[id]->val_gold;
        val->rooms[pos]->visited = 0;
    }
    return sol;
}
