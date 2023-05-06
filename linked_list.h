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
cell *copyArray(cell *board, cell *board2);
list *newList(cell **board);

void backBoard(cell **actual_board, cell **last_board2);
void push(list **head, cell **board);
void display_linked_list(list *ptr);
void free_linked_list(list *head);
void go_back(list **head);
int check_next(list **head);

#endif