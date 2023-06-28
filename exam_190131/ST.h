//
// Created by luiza on 28/06/23.
//

#ifndef EXAM_190131_ST_H
#define EXAM_190131_ST_H

typedef struct symboltable *ST;

ST    STinit(int maxN);
void  STfree(ST st);
int   STsize(ST st);
void  STinsert(ST st, char *str, int i);
int   STsearch(ST st, char *str);
char *STsearchByIndex(ST st, int i);


#endif //EXAM_190131_ST_H
