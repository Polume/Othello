#include "othello.h"

cell **initializeBoard()
{
    cell **board = calloc(8, sizeof(cell *));
    for (int i = 0; i < 8; i++)
    {
        board[i] = calloc(8, sizeof(cell));
    }
    char c = 'A';
    for (int i = 0; i < 8; i++)
    {
        // attribution à chaque case son id respectif
        for (int j = 0; j < 8; j++)
        {
            board[i][j].id_cell[0] = c;
            board[i][j].id_cell[1] = (i + 1) + '0';
        }
        c++;
    }
    board[3][3].color = 2;
    board[3][4].color = 1;
    board[4][4].color = 2;
    board[4][3].color = 1;

    return board;
}

void printBoard(cell **board)
{
    printf("\t");
    for (char c = 'A'; c <= 'H'; c++)
    {
        printf("%c ", c);
    }
    printf("\n");

    for (int i = 0; i < 8; i++)
    {
        printf("%d\t", i + 1);
        for (int j = 0; j < 8; j++)
        {
            printf("%d ", board[i][j].color);
        }
        printf("\n");
    }
}

void freeBoard(cell **board)
{
    for (int i = 0; i < 8; i++)
    {
        free(board[i]);
    }
    free(board);
}

int valid_cell(cell **board, int i, int j)
{
    if (board[i][j].color == VERT)
    {
        return 1;
    }
    return 0;
}

// int close_to(int **board)
// {
// }

void fill_lines(cell **board, int i, int color, int pos)
{
    for (int j = 0; j < 8; j++)
    {
        if (board[i][j].color == color && j < pos)
        {
            for (int k = j; k < pos; k++)
            {
                board[i][k].color = color;
            }
        }
        else if (board[i][j].color == color && j > pos)
        {
            for (int k = pos; k < j; k++)
            {
                board[i][k].color = color;
            }
        }
    }
}

void fill_rows(cell **board, int j, int color, int pos)
{
    for (int i = 0; i < 8; i++)
    {
        if (board[i][j].color == color && i < pos)
        {
            for (int k = i; k < pos; k++)
            {
                board[k][j].color = color;
            }
        }
        if (board[i][j].color == color && i > pos)
        {
            for (int k = pos; k < i; k++)
            {
                board[k][j].color = color;
            }
        }
    }
}