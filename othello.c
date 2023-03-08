#include "othello.h"

cell **initializeBoard()
// Fonction qui initialise le plateau de l othello
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
    board[3][3].color = NOIR;
    board[3][4].color = BLANC; // Attention ! i colonne j lignes
    board[4][4].color = NOIR;
    board[4][3].color = BLANC;

    return board;
}

void printBoard(cell **board)
// Affiche le plateau
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
// Libere la memoire du tableau
{
    for (int i = 0; i < 8; i++)
    {
        free(board[i]);
    }
    free(board);
}

int is_valid(cell **board, int i, int j, int color)
/* Fonction verifiant la validite de la case. Une case valide est de la forme suivante :
   -La case actuelle est verte
   -Au moins un de ses voisins directs a une couleur differente de la couleur a appliquer
   -Au moins un pion sur les lignes, colonnes et diagonales est de la même couleur que celle a appliquer
*/
{
    if (board[i][j].color == VERT && check_neighbors(board, i, j, color) && check_rows(board, j, color))
    {
        return 1;
    }
    printf("aaaaa%d", check_rows(board, j, color));
    return 0;
}

int check_neighbors(cell **board, int i, int j, int color)
/* Fonction qui vérifie la couleur des cases voisines directes de la case aux coordonnées i j
   Renvoie 1 si la couleur d une des cases est differente et non verte, sinon renvoie 0 */
{
    int right, left, top, bottom = 0;
    // on verifie d'abord qu'on est pas en dehors du plateau
    if (i != 0)
        top = board[i - 1][j].color != color && board[i - 1][j].color != VERT;
    if (i != 7)
        bottom = board[i + 1][j].color != color && board[i + 1][j].color != VERT;
    if (j != 0)
        left = board[i][j - 1].color != color && board[i][j - 1].color != VERT;
    if (j != 7)
        right = board[i][j + 1].color != color && board[i][j + 1].color != VERT;
    return top || bottom || right || left;
}

int check_lines(cell **board, int i, int color)
{
    for (int j = 0; j < 8; j++)
    {
        if (board[i][j].color == color && j < i)
        {
            // for (int k = j; k < pos; k++)
            // {
            //     if (board[i][j].color != VERT)
            //     {
            //         board[i][k].color = color;
            //     }
            // }
            return 1;
        }
        else if (board[i][j].color == color && j > i)
        {
            // for (int k = pos; k < j; k++)
            // {
            // if (board[i][j].color != VERT)
            // {
            //     board[i][k].color = color;
            // }
            // }
            return 1;
        }
    }
    return 0;
}

int check_rows(cell **board, int j, int color)
{
    for (int i = 0; i < 8; i++)
    {
        if (board[i][j].color == color && i < j)
        {
            // for (int k = i; k < pos; k++)
            // {
            //     if (board[i][j].color != VERT)
            //     {
            //         board[k][j].color = color;
            //     }
            // }
            return 1;
        }
        else if (board[i][j].color == color && i > j)
        {

            // for (int k = pos; k < i; k++)
            // {
            //     if (board[i][j].color != VERT)
            //     {
            //         board[k][j].color = color;
            //     }
            // }
            return 1;
        }
    }
    return 0;
}

// int fill_diag(cell **board, int d, int color, int pos)
// {
//     for (int i = 0; i < 8; i++)
//     {
//         if (board[d][d].color == color && i < pos)
//         {
//             for (int k = i; k < pos; k++)
//             {
//                 if (board[k][k].color != VERT)
//                 {
//                     board[k][k].color = color;
//                 }
//             }
//             return 1;
//         }
//         else if (board[d][d].color == color && i > pos)
//         {

//             for (int k = pos; k < i; k++)
//             {
//                 if (board[k][k].color != VERT)
//                 {
//                     board[k][k].color = color;
//                 }
//             }
//             return 1;
//         }
//     }
//     return 0;
// }