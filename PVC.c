#include "PVC.h"

void easy_mode(cell **board, int team)
{
    int cpt = 0;
    int **possible = calloc((SIZE_OTHELLO * SIZE_OTHELLO), sizeof(int *));
    for (int i = 0; i < SIZE_OTHELLO * SIZE_OTHELLO; i++)
        possible[i] = calloc(2, sizeof(int));
    // On crée un tableau de la forme [[i, j]] qui contiendra les emplacements des cases valides
    show_valid(board, team);

    for (int i = 0; i < SIZE_OTHELLO; i++)
    {
        for (int j = 0; j < SIZE_OTHELLO; j++)
        {
            if (board[i][j].valide == 1)
            {
                possible[cpt][0] = i;
                possible[cpt][1] = j;
                cpt++;
            }
        }
    }
    int num = ((rand() % (cpt - 1 + 1)) + 1) - 1; // formule de rand = rand() % (upper - lower + 1) + lower
                                                  // - 1 sinon on est en dehors du tableau
    // On récupère un indice du tableau des cases valides au hasard et on remplit le tableau
    fill(board, possible[num][0], possible[num][1], team);
    free(possible);
}
