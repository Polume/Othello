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
int valid_cell(cell **board, int i, int j);
void fill_lines(cell **board, int i, int color, int pos);
void fill_rows(cell **board, int j, int color, int pos);

#endif
