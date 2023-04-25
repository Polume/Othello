#include "PVC.h"

int easy_mode(cell **board, int team)
/* Fonction qui permet de jouer contre un ordinateur qui pose des cases au hasard
   Renvoie 0 si l'ordinateur doit passer son tour */
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
            } // On remplit notre tableau avec les indices des cases valides
        }
    }
    if (cpt == 0) // pas de cases valides
    {
        return 0;
    }
    int num = ((rand() % (cpt - 1 + 1)) + 1) - 1; // formule de rand = rand() % (upper - lower + 1) + lower
                                                  // - 1 sinon on est en dehors du tableau
    // On récupère un indice du tableau des cases valides au hasard et on remplit le tableau
    fill(board, possible[num][0], possible[num][1], team);
    free(possible);
    return 1;
}

tree *newNode(int data)
{
    tree *temp = (tree *)malloc(sizeof(tree));
    temp->val = data;
    temp->left = temp->right = NULL;
    return temp;
}

int height(tree *current)
/* Fonction récursive qui renvoie la hauteur de l'arbre
   de la feuille la plus lointaine à la racine */
{
    if (current == NULL)
        return 0;
    else
    {
        int lheight = height(current->left);
        int rheight = height(current->right);

        if (lheight > rheight)
            return (lheight + 1);
        else
            return (rheight + 1);
    }
}

void printCurrentLevel(tree *root, int level)
{
    if (root == NULL)
        return;
    if (level == 1)
        printf("%d\t", root->val);
    else if (level > 1)
    {
        printCurrentLevel(root->left, level - 1);
        printCurrentLevel(root->right, level - 1);
    }
}

void printTree(tree *root)
{
    int h = height(root);
    int i;
    for (i = 1; i <= h; i++)
    {
        printCurrentLevel(root, i);
        printf("\n");
    }
}