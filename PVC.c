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
        // On ne peut pas renvoyer de matrice de taille connue, on copie donc dans une matrice temporaire
        float **BeginPositionScore = calloc(SIZE_OTHELLO, sizeof(float *));
        for (int i = 0; i < SIZE_OTHELLO; i++)
        {
            BeginPositionScore[i] = calloc(SIZE_OTHELLO, sizeof(float));
        }
        float BeginPositionScoreTemp[8][8] = {{100, -50, 20, 5, 5, 20, -50, 100},
                                              {-50, -70, -5, -5, -5, -5, -70, -50},
                                              {20, -5, 15, 3, 3, 15, -5, 20},
                                              {5, -5, 3, 3, 3, 3, -5, 5},
                                              {5, -5, 3, 3, 3, 3, -5, 5},
                                              {20, -5, 15, 3, 3, 15, -5, 20},
                                              {-50, -70, -5, -5, -5, -5, -70, -50},
                                              {100, -50, 20, 5, 5, 20, -50, 100}};
        for (int i = 0; i < SIZE_OTHELLO; i++)
            for (int j = 0; j < SIZE_OTHELLO; j++)
                BeginPositionScore[i][j] = BeginPositionScoreTemp[i][j];

        return BeginPositionScore;
    }

    else if (state == MIDDLE)
    {
        float **MiddlePositionScore = calloc(SIZE_OTHELLO, sizeof(float *));
        for (int i = 0; i < SIZE_OTHELLO; i++)
        {
            MiddlePositionScore[i] = calloc(SIZE_OTHELLO, sizeof(float));
        }
        float MiddlePositionScoreTemp[8][8] = {{140, -20, 20, 5, 5, 20, -20, 140},
                                               {-20, -40, -5, -5, -5, -5, -40, -20},
                                               {20, -5, 15, 3, 3, 15, -5, 20},
                                               {5, -5, 3, 3, 3, 3, -5, 5},
                                               {5, -5, 3, 3, 3, 3, -5, 5},
                                               {20, -5, 15, 3, 3, 15, -5, 20},
                                               {-20, -40, -5, -5, -5, -5, -40, -20},
                                               {140, -20, 20, 5, 5, 20, -20, 140}};
        for (int i = 0; i < SIZE_OTHELLO; i++)
            for (int j = 0; j < SIZE_OTHELLO; j++)
                MiddlePositionScore[i][j] = MiddlePositionScoreTemp[i][j];

        return MiddlePositionScore;
    }
    else
    {
        float **EndPositionScore = calloc(SIZE_OTHELLO, sizeof(float *));
        for (int i = 0; i < SIZE_OTHELLO; i++)
        {
            EndPositionScore[i] = calloc(SIZE_OTHELLO, sizeof(float));
        }
        float EndPositionScoreTemp[8][8] = {{20, -5, 10, 5, 5, 10, -5, 20},
                                            {-5, -10, 5, 5, 5, 5, -10, -5},
                                            {20, 5, 5, 5, 5, 5, 5, 10},
                                            {5, 5, 3, 5, 5, 5, 5, 5},
                                            {5, 5, 3, 5, 5, 5, 5, 5},
                                            {10, 5, 5, 5, 5, 5, 5, 10},
                                            {-5, -10, 5, 5, 5, 5, -10, -5},
                                            {20, -5, 10, 5, 5, 10, -5, 20}};
        for (int i = 0; i < SIZE_OTHELLO; i++)
            for (int j = 0; j < SIZE_OTHELLO; j++)
                EndPositionScore[i][j] = EndPositionScoreTemp[i][j];

        return EndPositionScore;
    }
}

float *tree_values(cell **board, int **possible, int move, int color)
// Renvoie le tableau des valeurs contenues dans gameState en fonction des indices des cases valides
{
    // Creation d un nouveau plateau où on posera une des cases possibles
    cell **tmp_board = initializeBoard();
    copyBoard(board, tmp_board);
    fill(tmp_board, possible[move][0], possible[move][1], color);

    reset_valid(tmp_board);
    if (color == BLANC)
        color = NOIR;
    else
        color = BLANC; // changement de team

    int tmp_numMoves = show_valid(tmp_board, color);
    int **tmp_possible = possibilities(tmp_board, tmp_numMoves);
    // On regarde ensuite les differentes possibilites du coup adverse
    // printBoard(tmp_board);
    float **state = gameState(BEGIN); // Importance des cases
    float *tree_values = calloc(tmp_numMoves, sizeof(float));

    for (int i = 0; i < tmp_numMoves; i++)
    {
        float value = state[tmp_possible[i][0]][tmp_possible[i][1]];
        tree_values[i] = value;
        // printf("%f %d %d ", value, tmp_possible[i][0], tmp_possible[i][1]);
    }
    // printf("\n");
    free_matrix_float(state, SIZE_OTHELLO);
    free_matrix_int(tmp_possible, tmp_numMoves);
    freeBoard(tmp_board);

    return tree_values; // puis on renvoie l'arbre des differentes valeurs obtenues
}

float minimax(tree *root, int depth, int color)
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
    ce qui correspond à numMoves - 1
    Pour chaque arbre, on utilisera minimax et nous prendrons la solution la plus adéquate */
{
    int numMoves = show_valid(board, color);
    int finalSize = 0;
    int original_color = color;
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

    float *final_array = calloc(finalSize, sizeof(float));
    float bestMoveWhite = MAX_EVAL;
    float bestMoveBlack = MIN_EVAL;
    float bestMove;
    int best_index;

    // color == BLANC ? bestValue = MIN_EVAL : bestValue = MAX_EVAL;

    int **possible = possibilities(board, numMoves); // tableau des indices des cases valides

    // Pour tout les moves possibles, on va observer les possibles
    // coups adverses pour voir quelle est la meilleure case à utiliser
    for (int move = 0; move < numMoves; move++)
    {
        int tree_index = 0;
        float *tree_val = tree_values(board, possible, move, color);

        // tableau qui contiendra les valeurs de l'arbre binaire
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
        if (color == BLANC)
            color = NOIR;
        else
            color = BLANC; // changement de team comme dans tree_values pour garder la bonne couleur

        float minmax = minimax(root, height(root), color);

        if (color == BLANC) // choix de la meilleure valeur et du meilleur indice
        {
            bestMove = max(bestMoveWhite, minmax);
            if (bestMove == minmax)
                best_index = move;
        }
        else
        {
            bestMove = min(bestMoveBlack, minmax);
            if (bestMove == minmax)
                best_index = move;
        }
        printf("Au secours %f \n", minmax);
        color = original_color; // On reviens à la couleur de base pour reboucler
    }
    fill(board, possible[best_index][0], possible[best_index][1], color);
    return 1;
}