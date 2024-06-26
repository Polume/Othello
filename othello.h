#ifndef OTHELLO_H
#define OTHELLO_H

#include <stdio.h>
#include <stdlib.h>
#include "string.h"

#define VERT 0
#define BLANC 1
#define NOIR 2

#define SIZE_OTHELLO 8

typedef struct
{
    int color;
    int valide;
    char id_cell[2];
} cell;

cell **initializeBoard();
void printBoard(cell **board);
void freeBoard(cell **board);
void count_score(cell **board, int *cnt_W, int *cnt_B);

int max(int a, int b);
int min(int a, int b);
int isEndGame(cell **board);

int is_valid(cell **board, int i, int j, int color);
int check_neighbors_lines(cell **board, int i, int j, int color);
int check_neighbors_rows(cell **board, int i, int j, int color);
int check_lines(cell **board, int i, int color);
int check_rows(cell **board, int j, int color);
int get_last_color_lines(cell **board, int i, int color);
int get_last_color_rows(cell **board, int i, int color);

int check_diag_t_left(cell **board, int i, int j, int color, int *cpy_i, int *cpy_j);
int check_diag_t_right(cell **board, int i, int j, int color, int *cpy_i, int *cpy_j);
int check_diag_b_left(cell **board, int i, int j, int color, int *cpy_i, int *cpy_j);
int check_diag_b_right(cell **board, int i, int j, int color, int *cpy_i, int *cpy_j);
int check_diag(cell **board, int i, int j, int color);

int show_valid(cell **board, int color);
void reset_valid(cell **board);

void fill(cell **board, int i, int j, int color);
void fill_lines(cell **board, int i, int j, int color);
void fill_rows(cell **board, int i, int j, int color);
void fill_diag(cell **board, int i, int j, int color);

#endif
