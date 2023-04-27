#include "PVC.h"

int **possibilities(cell **board, int size)
// Fonction qui renvoie un tableau contenant les indices des differentes cases valides
{
    int cpt = 0;
    int **possible = calloc(size, sizeof(int *));
    for (int i = 0; i < size; i++)
        possible[i] = calloc(2, sizeof(int));
    // On crée un tableau de la forme [[i, j]] qui contiendra les emplacements des cases valides

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
    return possible;
}

int easy_mode(cell **board, int color)
/* Fonction qui permet de jouer contre un ordinateur qui pose des cases au hasard
   Renvoie 0 si l'ordinateur doit passer son tour */
{
    int nb_valid = show_valid(board, color);
    if (nb_valid == 0) // pas de cases valides
    {
        return 0;
    }
    int **possible = possibilities(board, nb_valid);
    int num = ((rand() % (nb_valid - 1 + 1)) + 1) - 1; // formule de rand = rand() % (upper - lower + 1) + lower
                                                       // - 1 sinon on est en dehors du tableau
    // On récupère un indice du tableau des cases valides au hasard et on remplit le tableau
    fill(board, possible[num][0], possible[num][1], color);
    free(possible);
    return 1;
}

tree *newNode(int data)
// Crée un nouveau noeud pour un arbre
{
    tree *temp = (tree *)malloc(sizeof(tree));
    temp->val = data;
    temp->left = temp->right = NULL;
    return temp;
}

void freeTree(tree *current)
// Fonction qui libere la memoire de l'arbre
{
    if (current != NULL)
    {
        freeTree(current->right);
        freeTree(current->left);
        free(current);
    }
}

int height(tree *current)
/* Fonction récursive qui renvoie la hauteur de l'arbre
   du noeud le plus lointain à la racine */
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
// Fonction utilisee pour afficher chaque niveau d un arbre
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
// Affichage d un arbre
{
    int h = height(root);
    int i;
    for (i = 1; i <= h; i++)
    {
        printCurrentLevel(root, i);
        printf("\n");
    }
}

void free_matrix(float **tab)
// Fonction qui libere la memoire d une matrice
{

    for (int i = 0; i < SIZE_OTHELLO; i++)
    {
        free(tab[i]);
    }
    free(tab);
}

float **gameState(int state)
/* Renvoie un tableau de valeurs en fonction de l'état de la partie en cours
   Utilisé pour l'algorithme minimax
   Les coins du plateau sont les cases les plus fortes et les bordures
   sont en général considérées comme des bonnes cases */
{
    if (state == BEGIN)
    {
        float **BeginPositionScore = calloc(SIZE_OTHELLO, sizeof(int *));
        for (int i = 0; i < SIZE_OTHELLO; i++)
        {
            BeginPositionScore[i] = calloc(SIZE_OTHELLO, sizeof(int));
        }
        BeginPositionScore[0] = (float[]){100, -50, 20, 5, 5, 20, -50, 100};
        BeginPositionScore[1] = (float[]){-50, -70, -5, -5, -5, -5, -70, -50};
        BeginPositionScore[2] = (float[]){20, -5, 15, 3, 3, 15, -5, 20};
        BeginPositionScore[3] = (float[]){5, -5, 3, 3, 3, 3, -5, 5};
        BeginPositionScore[4] = (float[]){5, -5, 3, 3, 3, 3, -5, 5};
        BeginPositionScore[5] = (float[]){20, -5, 15, 3, 3, 15, -5, 20};
        BeginPositionScore[6] = (float[]){-50, -70, -5, -5, -5, -5, -70, -50};
        BeginPositionScore[7] = (float[]){100, -50, 20, 5, 5, 20, -50, 100};
        return BeginPositionScore;
    }

    else if (state == MIDDLE)
    {
        float **MiddlePositionScore = calloc(SIZE_OTHELLO, sizeof(int *));
        for (int i = 0; i < SIZE_OTHELLO; i++)
        {
            MiddlePositionScore[i] = calloc(SIZE_OTHELLO, sizeof(int));
        }
        MiddlePositionScore[0] = (float[]){140, -20, 20, 5, 5, 20, -20, 140},
        MiddlePositionScore[1] = (float[]){-20, -40, -5, -5, -5, -5, -40, -20},
        MiddlePositionScore[2] = (float[]){20, -5, 15, 3, 3, 15, -5, 20},
        MiddlePositionScore[3] = (float[]){5, -5, 3, 3, 3, 3, -5, 5},
        MiddlePositionScore[4] = (float[]){5, -5, 3, 3, 3, 3, -5, 5},
        MiddlePositionScore[5] = (float[]){20, -5, 15, 3, 3, 15, -5, 20},
        MiddlePositionScore[6] = (float[]){-20, -40, -5, -5, -5, -5, -40, -20},
        MiddlePositionScore[7] = (float[]){140, -20, 20, 5, 5, 20, -20, 140};
        return MiddlePositionScore;
    }
    else
    {
        float **EndPositionScore = calloc(SIZE_OTHELLO, sizeof(int *));
        for (int i = 0; i < SIZE_OTHELLO; i++)
        {
            EndPositionScore[i] = calloc(SIZE_OTHELLO, sizeof(int));
        }
        EndPositionScore[0] = (float[]){20, -5, 10, 5, 5, 10, -5, 20},
        EndPositionScore[1] = (float[]){-5, -10, 5, 5, 5, 5, -10, -5},
        EndPositionScore[2] = (float[]){20, 5, 5, 5, 5, 5, 5, 10},
        EndPositionScore[3] = (float[]){5, 5, 3, 5, 5, 5, 5, 5},
        EndPositionScore[4] = (float[]){5, 5, 3, 5, 5, 5, 5, 5},
        EndPositionScore[5] = (float[]){10, 5, 5, 5, 5, 5, 5, 10},
        EndPositionScore[6] = (float[]){-5, -10, 5, 5, 5, 5, -10, -5},
        EndPositionScore[7] = (float[]){20, -5, 10, 5, 5, 10, -5, 20};
        return EndPositionScore;
    }
}

int minimax(cell **board, float *test, int depth, int color, int index)
// Blanc - MAXIMIZE
// Noir - MINIMIZE
{
    // int numMoves = show_valid(board, color);
    // if (numMoves == 0) // pas de cases valides
    // {
    //     return 0;
    // }

    // int **possible = possibilities(board, numMoves);
    int eval = 0;

    if (depth == 0)
    {
        return test[index];
    }
    if (color == BLANC)
    { // On cherche la valeur max
        int maxEval = -10000;
        eval = minimax(board, test, depth - 1, NOIR, index * 2);
        maxEval = max(maxEval, eval);
        eval = minimax(board, test, depth - 1, NOIR, index * 2 + 1);
        maxEval = max(maxEval, eval);

        printf("Max %d\n", maxEval);

        return maxEval;
    }
    else
    { // On cherche la valeur min
        int minEval = 10000;
        eval = minimax(board, test, depth - 1, BLANC, index * 2);
        minEval = min(minEval, eval);
        eval = minimax(board, test, depth - 1, BLANC, index * 2 + 1);
        minEval = min(minEval, eval);

        printf("Min %d\n", minEval);
        return minEval;
    }
}