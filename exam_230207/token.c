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

BonusBlock BONUSread (FILE* fp, int L) {
    BonusBlock B = malloc(sizeof(*B));
    int n, nb, j, i;
    char token[2];
    token_t t;
    B->block = malloc(L * sizeof(bonus_t*));

    fscanf(fp, "%d", &n);
    for (i=0; i<n; i++) {
        fscanf(fp, "%d", nb);
        for (j=0; i<nb; j++) {
            B->block[i].N = nb;
            B->block[i].tokens = malloc(nb * sizeof(token_t));
            fscanf(fp, "%s", token);
            t = TOKENcreate(token);
            B->block[i].tokens[j] = t;
        }
    }

    return B;
}

//sulla prima riga del file è indicato il numero N di token proposti
//a seguire N token per la proposta di soluzione
int PROPread (FILE *fp, Grid G, BonusBlock B, int L) {
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

int BONUScnt (BonusBlock B, Prop P) {
    int bonus = 0, i, j, k, cnt=0;

    for (i=0; i<B->N; i++) {
        k = 0;
        for (j=0; j<B->block[i].N; j++) {
            if (TOKENcompare(B->block[i].tokens[j], P->prop[k]))
                cnt++;
            k++;
        }
        if (cnt == B->block[i].N)
            bonus += B->block[i].val;
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