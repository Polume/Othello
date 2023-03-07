#include "othello.h"

int **initializeBoard()
{
    int **board = calloc(8, sizeof(int *));
    for (int i = 0; i < 8; i++)
    {
        board[i] = calloc(8, sizeof(int));
    }
    board[3][3] = 2;
    board[3][4] = 1;
    board[4][4] = 2;
    board[4][3] = 1;

    return board;
}

void printBoard(int **board)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

void freeBoard(int **board)
{
    for (int i = 0; i < 8; i++)
    {
        free(board[i]);
    }
    free(board);
}