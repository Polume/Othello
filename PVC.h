#ifndef PVC_H
#define PVC_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <math.h>
#include "othello.h"

#define BEGIN 0
#define MIDDLE 25
#define END 50

#define MAX_EVAL -10000
#define MIN_EVAL 10000

typedef struct tree
{
    float val;
    struct tree *right;
    struct tree *left;
} tree;

int **possibilities(cell **board, int size);
int easy_mode(cell **board, int team);

void free_matrix_int(int **tab, int size);
void free_matrix_float(float **tab, int size);

tree *newNode(float data);
tree *insertInTree(float *tab, int i, int n);
void freeTree(tree *current);
int height(tree *current);
void printCurrentLevel(tree *root, int level);
void printTree(tree *root);

float **gameState(int state);
float *tree_values(cell **board, int numMoves);

int minimax(tree *root, int depth, int color);
int hard_mode(cell **board, int color);

#endif