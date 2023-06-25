#include "token.h"

Grid GRIDinit(FILE* fp)  {
    int n, i;
    Grid G = malloc(sizeof(*G));

    fscanf(fp, "%d", &n);
    G->N = n;

    for (i=0; i<n; i++)
        G->grid[i] = malloc(G->N * sizeof(token_t*));

    return G;
}

Grid GRIDread(FILE* fp) {
    Grid G = malloc(sizeof(*G));
    int i, cnt=0;
    char token[2];

    G = GRIDinit(fp);

    for (i=0; i<G->N; i++) {
        fscanf(fp, "%s", token);
        TOKENadd(G, token, cnt);
        cnt++;
    }
}

token_t TOKENcreate (char token[2]) {
    token_t t;
    strcpy(t.T, token);
    return t;
}

void TOKENadd (Grid G, char token[2], int cnt) {
    int R, C;
    token_t t = TOKENcreate(token);
    R = cnt/(G->N);
    C = cnt%(G->N);
    G->grid[R][C] = t;
}

BonusTab BONUSread (FILE* fp, int L) {
    BonusTab B = malloc(sizeof(*B));
    int n, nb, j, i;
    char token[2];
    token_t t;
    B->blocks = malloc(L * sizeof(bonus_t*));

    fscanf(fp, "%d", &n);
    for (i=0; i<n; i++) {
        fscanf(fp, "%d", nb);
        for (j=0; i<nb; j++) {
            B->blocks[i].N = nb;
            B->blocks[i].tokens = malloc(nb * sizeof(token_t));
            fscanf(fp, "%s", token);
            t = TOKENcreate(token);
            B->blocks[i].tokens[j] = t;
        }
    }

    return B;
}

//sulla prima riga del file è indicato il numero N di token proposti
//a seguire N token per la proposta di soluzione
int PROPread (FILE *fp, Grid G, BonusTab B, int L) {
    int n, i, bonus=0;
    char token[2];
    Prop P = malloc(sizeof(*P));
    token_t* prop;

    fscanf(fp, "%d", &n);
    //controllo che la lunghezza della proposta non sia maggiore del buffer
    if (n > L)
        return 0;
    P->prop = malloc(n * sizeof(token_t));

    for (i=0; i<n; i++) {
        fscanf(fp, "%s", token);
        P->prop[i] = TOKENcreate(token);
    }

    if (PROPisValid(G, P)) {
        //conteggio bonus
    }
    return bonus;
}

int BONUScnt (BonusTab B, Prop P) {
    int bonus = 0, i, j, k, cnt=0;

    for (i=0; i<B->N; i++) {
        k = 0;
        for (j=0; j<B->blocks[i].N; j++) {
            if (TOKENcompare(B->blocks[i].tokens[j], P->prop[k]))
                cnt++;
            k++;
        }
        if (cnt == B->blocks[i].N)
            bonus += B->blocks[i].val;
    }

    return bonus;
}

int TOKENcompare (token_t t1, token_t t2) {
    if (t1.T[0] == t2.T[0] && t1.T[0] == t2.T[1])
        return 1;
    return 0;
}

int isSameR(Grid G, token_t t1, token_t t2) {
    int i, j, k;
    for (i=0; G->N; i++) {
        for (j=0; j<G->N; j++) {
            if (TOKENcompare(G->grid[i][j], t1)) {
                for (k=0; k<G->N; k++) {
                    if (TOKENcompare(G->grid[i][k], t2))
                        return 1;
                }
                return 0;
            }
        }
    }
    return 0;
}

int isSameC(Grid G, token_t t1, token_t t2) {
    int i, j, k;
    for (i=0; G->N; i++) {
        for (j=0; j<G->N; j++) {
            if (TOKENcompare(G->grid[i][j], t1)) {
                for (k=0; k<G->N; k++) {
                    if (TOKENcompare(G->grid[k][j], t2))
                        return 1;
                }
                return 0;
            }
        }
    }
    return 0;
}

int PROPisValid (Grid G, Prop P) {
    int i;

    for (i=1; i<P->N; i++) {
        if (!isSameR(G, P->prop[i-1], P->prop[i]) && !isSameC(G, P->prop[i-1], P->prop[i]))
            return 0;
    }
    return 1;
}

void PATHsearch (Grid G, int L, BonusTab B) {
    int i;
    Prop val = malloc(sizeof(*val));
    val->N = L;
    val->prop = malloc(val->N * sizeof(token_t));
    Prop sol = malloc(sizeof(*sol));
    sol->N = L;
    sol->prop = malloc(sol->N * sizeof(token_t));
    PATHrec(0, 0, G, B, sol, val, 0);
    PRINTsol(sol);
}

void PATHrec (int x, int y, Grid G, BonusTab B, Prop sol, Prop val, int cnt) {
    int i;
    //terminazione: superati i limiti della matrice o il buffer è pieno
    if (x*y > G->N || cnt >= val->N) {
        if (BONUScnt(B, val) > BONUScnt(B, sol))
            PROPcpy(sol, val);
    }
    //ricorsione: avanza lungo la stessa riga
    for (i=0; i<G->N; i++) {
        val->prop[cnt] = G->grid[x][y];
        PATHrec(x + 1, y, G, B, sol, val, cnt+1);
    }
    //ricorsione: avanza lungo la stessa colonna
    for (i=0; i<G->N; i++) {
        val->prop[cnt] = G->grid[x][y];
        PATHrec(x, y+1, G, B, sol, val, cnt+1);
    }
}