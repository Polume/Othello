#ifndef OTHELLO_H
#define OTHELLO_H

#include <stdio.h>
#include <stdlib.h>
#include "string.h"

#define VERT 0
#define BLANC 1
#define NOIR 2

typedef struct liste
{
    int num;
    struct liste *svt;
} *liste;

typedef struct
{
    int color;
    char id_cell[2];
} cell;

cell **initializeBoard();
void printBoard(cell **board);
void freeBoard(cell **board);
int is_valid(cell **board, int i, int j, int color);
int check_neighbors(cell **board, int i, int j, int color);

int check_lines(cell **board, int i, int color);
int check_rows(cell **board, int j, int color);
// int fill_diag(cell **board, int d, int color);

#endif
