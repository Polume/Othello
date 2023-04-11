#include "linked_list.h"
#include "gui.h"

cell **newBoard()
{
    cell **new_board = calloc(SIZE_OTHELLO, sizeof(cell *));
    for (int i = 0; i < SIZE_OTHELLO; i++)
    {
        new_board[i] = calloc(SIZE_OTHELLO, sizeof(cell));
    }
    return new_board;
}

cell **copyBoard(cell **board, cell **board2)
{
    for (int i = 0; i < SIZE_OTHELLO; i++)
    {
        for (int j = 0; j < SIZE_OTHELLO; j++)
        {
            board2[i][j] = board[i][j];
        }
    }
    return board2;
}

list *newList(cell **board)
{
    list *new = (list *)malloc(sizeof(list));
    new->board = newBoard();
    new->board = copyBoard(board, new->board);
    new->next = NULL;
    new->prev = NULL;
    return new;
}

void push(list **head, cell **board)
{
    list *new_node = newList(board);

    new_node->next = (*head);
    new_node->prev = NULL;

    if ((*head) != NULL)
        (*head)->prev = new_node;

    (*head) = new_node;
}

void free_linked_list(list *head)
// Fonction qui libere la memoire de chaque noeud
{
    list *tmp = head;
    while (tmp)
    {
        list *next = tmp->next;
        free(tmp);
        tmp = next;
    }
}

void display_linked_list(list *ptr)
// Affiche la liste de la fin vers le debut
{
    printf("\nListe \n");
    while (ptr != NULL)
    {
        printBoard(ptr->board);
        ptr = ptr->next;
    }
}
