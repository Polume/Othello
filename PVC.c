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
    free_matrix_int(possible, 2);
    return 1;
}

void free_matrix_int(int **tab, int size)
// Fonction qui libere la memoire d une matrice d'int
{

    for (int i = 0; i < size; i++)
    {
        free(tab[i]);
    }
    free(tab);
}

void free_matrix_float(float **tab, int size)
// Fonction qui libere la memoire d une matrice de float
{
    for (int i = 0; i < size; i++)
    {
        free(tab[i]);
    }
    free(tab);
}

tree *newNode(float data)
// Crée un nouveau noeud pour un arbre
{
    tree *temp = (tree *)malloc(sizeof(tree));
    temp->val = data;
    temp->left = temp->right = NULL;
    return temp;
}

tree *insertInTree(float *tab, int i, int n)
// Cree un arbre binaire en fonction du tableau tab
{
    tree *root = NULL;
    if (i < n) // Creation de l'arbre en recursion
    {
        root = newNode(tab[i]);
        root->left = insertInTree(tab, 2 * i + 1, n);
        root->right = insertInTree(tab, 2 * i + 2, n);
    }
    return root;
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
        printf("%f\t", root->val);
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

float *tree_values(cell **board, int numMoves)
// Renvoie le tableau des valeurs contenues dans gameState en fonction des indices des cases valides
{
    int **possible = possibilities(board, numMoves); // tableau des indices des cases valides
    float **state = gameState(BEGIN);                // Importance des cases
    float *tree_values = calloc(numMoves, sizeof(float));
    for (int i = 0; i < numMoves; i++)
    {
        float value = state[possible[i][0]][possible[i][1]];
        tree_values[i] = value;
    }
    // free_matrix_float(state, SIZE_OTHELLO);
    // free_matrix_int(possible, numMoves);
    return tree_values;
}

int minimax(tree *root, int depth, int color)
// Blanc - MAXIMIZE
// Noir - MINIMIZE
{
    int eval = 0;
    if (depth == 1)
    {
        return root->val;
    }
    if (color == BLANC)
    // On cherche ici la valeur max, pour chaque fils du noeud courant
    {
        int maxEval = MAX_EVAL;
        if (root->left != NULL)
        {
            eval = minimax(root->left, depth - 1, NOIR);
            maxEval = max(maxEval, eval);
        }
        if (root->right != NULL)
        {
            eval = minimax(root->right, depth - 1, NOIR);
            maxEval = max(maxEval, eval);
        }
        root->val = maxEval; // On attribue la valeur maximale au noeud pour l'affichage
        return maxEval;
    }
    else
    { // On cherche ici la valeur min
        int minEval = MIN_EVAL;
        if (root->left != NULL)
        {
            eval = minimax(root->left, depth - 1, BLANC);
            minEval = min(minEval, eval);
        }
        if (root->right != NULL)
        {
            eval = minimax(root->right, depth - 1, BLANC);
            minEval = min(minEval, eval);
        }
        root->val = minEval; // On attribue la valeur minimale au noeud pour l'affichage
        return minEval;
    }
}

int hard_mode(cell **board, int color)
/*  Fonction qui permet de créer une IA qui utilise l algorithme minimax
    On doit faire en sorte d'adapter la taille de notre tableau pour remplir correctement notre arbre binaire
    par rapport à la puissance de 2 du nombre de coups possibles
    ex : numMoves = 8 alors l'arbre sera de profondeur 4 et on a les valeurs -1, 3, 5, 1, -6, -4, 0, 9
    notre arbre sera donc de la forme suivante après la fonction minimax
                                                                 3.000000
                              3.000000                                                           -4.000000
                3.000000                         5.000000                      -4.000000                         9.000000
        -1.000000       3.000000        5.000000        1.000000        -6.000000       -4.000000       0.000000        9.000000
    On a donc besoin de créer 7 noeuds auparavant pour qu'ils puissent contenir les différentes valeurs min et max
    ce qui correspond à numMoves - 1 */
{
    int numMoves = show_valid(board, color);
    int finalSize = 0;
    if (numMoves == 0) // pas de cases valides
    {
        return 0;
    }

    float log = log2(numMoves);
    int is_power_of_2 = (ceilf(log) == log); // Renvoie 1 si f est entier sinon 0
    int log_int = (int)log;

    // Si notre nombre de cases valides n'est pas une puissance de 2, log2 sera un float
    // on convertira alors le log2 en entier et on ajoute 1 pour ajuster l'arbre
    if (is_power_of_2)
        finalSize = numMoves - 1 + numMoves;
    else
    {
        finalSize = powf(2.0, log_int + 1) - 1 + numMoves;
    }
    printf("SSSSSS %d\n", finalSize);

    float *tree_val = tree_values(board, numMoves);
    float *final_array = calloc(finalSize, sizeof(float));
    // tableau qui contiendra les valeurs de l'arbre et les noeuds supplémentaires

    int tree_index = 0;
    if (is_power_of_2)
    {
        for (int i = numMoves - 1; i < finalSize; i++)
        {
            final_array[i] = tree_val[tree_index];
            tree_index++;
        }
    }
    else
    {
        for (int i = powf(2.0, log_int + 1) - 1; i < finalSize; i++)
        {
            final_array[i] = tree_val[tree_index];
            tree_index++;
        }
    }
    tree *root = insertInTree(final_array, 0, finalSize);
    minimax(root, height(root), color);
    printTree(root);
    return 0;
}