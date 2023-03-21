#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "othello.h"

typedef struct list
{
    cell **board;
    struct list *next;
    struct list *prev;
} list;

cell **newBoard();
cell **copyBoard(cell **board, cell **board2);
list *newList(cell **board);

void push(list **head, cell **board);
void display_linked_list(list *ptr);
void free_linked_list(list *head);

#endif