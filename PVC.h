#ifndef PVC_H
#define PVC_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "othello.h"

#define BEGIN 0
#define MIDDLE 25
#define END 50

typedef struct tree
{
    int val;
    struct tree *right;
    struct tree *left;
} tree;

int **possibilities(cell **board, int size);
int easy_mode(cell **board, int team);

tree *newNode(int data);
void freeTree(tree *current);
int height(tree *current);
void printCurrentLevel(tree *root, int level);
void printTree(tree *root);

void free_matrix(float **tab);
float **gameState(int state);

int minimax(cell **board, float *test, int depth, int color, int index);

#endif