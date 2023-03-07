#ifndef OTHELLO_H
#define OTHELLO_H

#include <stdio.h>
#include <stdlib.h>

#define VERT 0
#define BLANC 1
#define NOIR 2

typedef struct liste
{
    int num;
    struct liste *svt;
} *liste;

int **initializeBoard();
void printBoard(int **board);
void freeBoard(int **board);

#endif
