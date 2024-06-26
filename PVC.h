#ifndef PVC_H
#define PVC_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <math.h>
#include "linked_list.h"
#include "othello.h"

#define MAX_EVAL -10000
#define MIN_EVAL 10000
#define AUX_VALUE 500

typedef struct tree
{
    float val;
    struct tree *right;
    struct tree *left;
} tree;

int **possibilities(cell **board, int size);
int random_mode(cell **board, int team);
int easy_mode(cell **board, int color);

void free_matrix_int(int **tab, int size);
void free_matrix_float(float **tab, int size);

tree *newNode(float data);
tree *insertInTree(float *tab, int i, int n);
void freeTree(tree *current);
int height(tree *current);
void printCurrentLevel(tree *root, int level);
void printTree(tree *root);

float **gameState();
float *tree_values(cell **board, int **possible, int move, int color, int *tmp_numMoves);

float minimax(tree *root, int depth, float alpha, float beta, int color);
int hard_mode(cell **board, int color);

#endif