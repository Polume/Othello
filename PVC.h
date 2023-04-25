#ifndef PVC_H
#define PVC_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "othello.h"

typedef struct tree
{
    int val;
    struct tree *right;
    struct tree *left;
} tree;

int easy_mode(cell **board, int team);

tree *newNode(int data);
int height(tree *current);
void printCurrentLevel(tree *root, int level);
void printTree(tree *root);

#endif