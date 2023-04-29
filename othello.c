#include "othello.h"

cell **initializeBoard()
// Fonction qui initialise le plateau de l othello
{
    cell **board = calloc(SIZE_OTHELLO, sizeof(cell *));
    for (int i = 0; i < SIZE_OTHELLO; i++)
    {
        board[i] = calloc(SIZE_OTHELLO, sizeof(cell));
    }
    char c = 'A';
    for (int i = 0; i < SIZE_OTHELLO; i++)
    {
        // attribution à chaque case son id respectif
        for (int j = 0; j < SIZE_OTHELLO; j++)
        {
            board[i][j].id_cell[0] = c;
            board[i][j].id_cell[1] = (i + 1) + '0';
            c++;
        }
        c = 'A';
    }
    board[3][3].color = BLANC;
    board[3][4].color = NOIR;
    board[4][4].color = BLANC;
    board[4][3].color = NOIR;

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

    for (int i = 0; i < SIZE_OTHELLO; i++)
    {
        printf("%d\t", i + 1);
        for (int j = 0; j < SIZE_OTHELLO; j++)
        {
            printf("%d ", board[i][j].color);
        }
        printf("\n");
    }
}

void freeBoard(cell **board)
// Libere la memoire du tableau
{
    for (int i = 0; i < SIZE_OTHELLO; i++)
    {
        free(board[i]);
    }
    free(board);
}

void count_score(cell **board, int *cnt_W, int *cnt_B)
{
    *cnt_W = 0;
    *cnt_B = 0;
    for (int i = 0; i < SIZE_OTHELLO; i++)
    {
        for (int j = 0; j < SIZE_OTHELLO; j++)
        {
            if (board[i][j].color == BLANC)
            {
                *cnt_W = *cnt_W + 1;
            }
            else if (board[i][j].color == NOIR)
            {
                *cnt_B = *cnt_B + 1;
            }
        }
    }
}

int max(int a, int b)
// Retourne le plus grand nombre
{
    return a >= b ? a : b;
}

int min(int a, int b)
{
    return a <= b ? a : b;
}

int isEndGame(cell **board)
{
    return show_valid(board, BLANC) == 0 && show_valid(board, NOIR) == 0 ? 1 : 0;
}

int is_valid(cell **board, int i, int j, int color)
/* Fonction verifiant la validite de la case. Une case valide est de la forme suivante :
   -La case actuelle est verte
   -Au moins un de ses voisins directs a une couleur differente de la couleur a appliquer
   -Si on cherche à poser un pion en diagonale, on regarde également les voisins diagonaux de la case actuelle
   -Au moins un pion sur les lignes, colonnes et diagonales est de la même couleur que celle a appliquer
   et les cases adjacentes a celle-ci ne sont pas vertes
   Renvoie 1 si la case est valide et 0 sinon
*/
{
    int maxi = 0;
    int mini = 0;
    int not_color = 0;
    if (board[i][j].color == VERT &&
        check_neighbors_lines(board, i, j, color) &&
        check_lines(board, i, color) >= 0)
    {
        maxi = max(j, check_lines(board, i, color));
        mini = min(j, check_lines(board, i, color));
        mini++; // La case actuelle sera soit de la couleur correspondante soit verte, on avance donc d'un cran
        while (mini < maxi && board[i][mini].color != VERT)
        {
            if (board[i][mini].color != color)
                not_color = 1;
            mini++; // on boucle entre les indices j et l'indice de la colonne
                    // renvoyé par check_lines pour voir s'il n y a pas de cases vertes entre
        }
        if (mini == maxi && not_color)
            return 1;
    }
    else if (board[i][j].color == VERT &&
             check_neighbors_rows(board, i, j, color) &&
             check_rows(board, j, color) >= 0)
    {
        not_color = 0;
        maxi = max(i, check_rows(board, j, color));
        mini = min(i, check_rows(board, j, color));
        mini++;
        while (mini < maxi && board[mini][j].color != VERT)
        {
            if (board[mini][j].color != color)
                not_color = 1;
            mini++; // on boucle entre les indices j et l'indice de la colonne
                    // renvoyé par check_lines pour voir s'il n y a pas de cases vertes entre
        }
        if (mini == maxi && not_color)
            return 1;
    }

    else if (board[i][j].color == VERT && check_diag(board, i, j, color))
    {
        return 1;
    }
    return 0;
}

int check_neighbors_lines(cell **board, int i, int j, int color)
/* Fonction qui vérifie la couleur des cases voisines directes de la case aux coordonnées i j
   Renvoie 1 si la couleur d une des cases est differente et non verte, sinon renvoie 0
   Version uniquement pour les lignes*/
{
    int right = 0;
    int left = 0;
    // on verifie d'abord qu'on est pas en dehors du plateau
    if (j != 0 && j - 2 != -1 && board[i][j - 2].color != VERT)
        left = board[i][j - 1].color != color && board[i][j - 1].color != VERT;
    if (j != SIZE_OTHELLO - 1 && j + 2 != SIZE_OTHELLO && board[i][j + 2].color != VERT)
        right = board[i][j + 1].color != color && board[i][j + 1].color != VERT;
    return right || left;
}

int check_neighbors_rows(cell **board, int i, int j, int color)
// Version pour les colonnes
{
    int top = 0;
    int bottom = 0;
    if (i != 0 && i - 2 != -1 && board[i - 2][j].color != VERT)
        top = board[i - 1][j].color != color && board[i - 1][j].color != VERT;
    if (i != SIZE_OTHELLO - 1 && i + 2 != SIZE_OTHELLO && board[i + 2][j].color != VERT)
        bottom = board[i + 1][j].color != color && board[i + 1][j].color != VERT;
    return top || bottom;
}

int check_lines(cell **board, int i, int color)
// Verifie si color se trouve sur la ligne i et renvoie son indice
{
    for (int j = 0; j < SIZE_OTHELLO; j++)
    {
        if (board[i][j].color == color)
        {
            if ((j + 1 < SIZE_OTHELLO && board[i][j + 1].color != VERT) ||
                (j - 1 >= 0 && board[i][j - 1].color != VERT))
                return j;
        }
    }
    return -1;
}

int check_rows(cell **board, int j, int color)
// Verifie si color se trouve sur la colonne j et renvoie son indice
{
    for (int i = 0; i < SIZE_OTHELLO; i++)
    {
        if (board[i][j].color == color)
        {
            if ((i + 1 < SIZE_OTHELLO && board[i + 1][j].color != VERT) ||
                (i - 1 >= 0 && board[i - 1][j].color != VERT))
                return i;
        }
    }
    return -1;
}

int check_diag_t_left(cell **board, int i, int j, int color, int *cpy_i, int *cpy_j)
// Verifie si color se trouve sur la diagonale superieure gauche
{
    *cpy_i = i;
    *cpy_j = j;
    while (*cpy_i != -1 && *cpy_j != -1)
    {
        if ((*cpy_i - 1 != -1 && *cpy_j - 1 != -1) && board[*cpy_i - 1][*cpy_j - 1].color == VERT)
            return 0;
        else if ((*cpy_i - 1 != -1 && *cpy_j - 1 != -1) && board[*cpy_i - 1][*cpy_j - 1].color == color)
            return 1;
        *cpy_i = *cpy_i - 1; // on garde les valeurs des indices pour la fonction fill_diag
        *cpy_j = *cpy_j - 1;
    }
    return 0;
}

int check_diag_t_right(cell **board, int i, int j, int color, int *cpy_i, int *cpy_j)
// Verifie si color se trouve sur la diagonale superieure droite
{
    *cpy_i = i;
    *cpy_j = j;
    while (*cpy_i != -1 && *cpy_j < SIZE_OTHELLO)
    {
        if ((*cpy_i - 1 != -1 && *cpy_j + 1 < SIZE_OTHELLO) && board[*cpy_i - 1][*cpy_j + 1].color == VERT)
            return 0;
        else if ((*cpy_i - 1 != -1 && *cpy_j + 1 < SIZE_OTHELLO) && board[*cpy_i - 1][*cpy_j + 1].color == color)
            return 1;
        *cpy_i = *cpy_i - 1;
        *cpy_j = *cpy_j + 1;
    }
    return 0;
}

int check_diag_b_left(cell **board, int i, int j, int color, int *cpy_i, int *cpy_j)
// Verifie si color se trouve sur la diagonale inferieure gauche
{
    *cpy_i = i;
    *cpy_j = j;
    while (*cpy_i < SIZE_OTHELLO && *cpy_j != -1)
    {
        if ((*cpy_i + 1 < SIZE_OTHELLO && *cpy_j - 1 != -1) && board[*cpy_i + 1][*cpy_j - 1].color == VERT)
            return 0;
        else if ((*cpy_i + 1 < SIZE_OTHELLO && *cpy_j - 1 != -1) && board[*cpy_i + 1][*cpy_j - 1].color == color)
            return 1;
        *cpy_i = *cpy_i + 1;
        *cpy_j = *cpy_j - 1;
    }
    return 0;
}

int check_diag_b_right(cell **board, int i, int j, int color, int *cpy_i, int *cpy_j)
// Verifie si color se trouve sur la diagonale inferieure droite
{
    *cpy_i = i;
    *cpy_j = j;
    while (*cpy_i < SIZE_OTHELLO && *cpy_j < SIZE_OTHELLO)
    {
        if ((*cpy_i + 1 < SIZE_OTHELLO && *cpy_j + 1 < SIZE_OTHELLO) && board[*cpy_i + 1][*cpy_j + 1].color == VERT)
            return 0;
        else if ((*cpy_i + 1 < SIZE_OTHELLO && *cpy_j + 1 < SIZE_OTHELLO) && board[*cpy_i + 1][*cpy_j + 1].color == color)
            return 1;
        *cpy_i = *cpy_i + 1;
        *cpy_j = *cpy_j + 1;
    }
    return 0;
}

int check_diag(cell **board, int i, int j, int color)
/* Fonction qui vérifie la couleur des cases voisines directes en diagonale, utilisee dans is_valid
   top_right = i - 1 j + 1  top_left = i - 1 j - 1  bottom_left = i + 1 j - 1   bottom_right = i + 1 j + 1 */
{
    int top_right = 0;
    int top_left = 0;
    int bottom_right = 0;
    int bottom_left = 0;
    int cpy_i;
    int cpy_j;
    // on verifie d'abord qu'on est pas en dehors du plateau
    if (i != 0 && j != 0)
        // Puis on check chaque diagonale une par une
        top_left = board[i - 1][j - 1].color != color &&
                   board[i - 1][j - 1].color != VERT &&
                   check_diag_t_left(board, i, j, color, &cpy_i, &cpy_j);
    if (i != 0 && j != SIZE_OTHELLO - 1)
        top_right = board[i - 1][j + 1].color != color &&
                    board[i - 1][j + 1].color != VERT &&
                    check_diag_t_right(board, i, j, color, &cpy_i, &cpy_j);
    if (i != SIZE_OTHELLO - 1 && j != 0)
        bottom_left = board[i + 1][j - 1].color != color &&
                      board[i + 1][j - 1].color != VERT &&
                      check_diag_b_left(board, i, j, color, &cpy_i, &cpy_j);
    if (i != SIZE_OTHELLO - 1 && j != SIZE_OTHELLO - 1)
        bottom_right = board[i + 1][j + 1].color != color &&
                       board[i + 1][j + 1].color != VERT &&
                       check_diag_b_right(board, i, j, color, &cpy_i, &cpy_j);
    return top_right || top_left || bottom_right || bottom_left;
}

int show_valid(cell **board, int color)
// Affiche toutes les cases valides du plateau
{
    int cpt = 0;
    for (int i = 0; i < SIZE_OTHELLO; i++)
    {
        for (int j = 0; j < SIZE_OTHELLO; j++)
        {
            if (is_valid(board, i, j, color))
            {
                board[i][j].valide = 1;
                cpt++;
                // printf("Case %s valide\n", board[i][j].id_cell);
            }
        }
    }
    return cpt;
}

void reset_valid(cell **board)
// Enlève toutes les cases valides du plateau
{
    for (int i = 0; i < SIZE_OTHELLO; i++)
    {
        for (int j = 0; j < SIZE_OTHELLO; j++)
        {
            if (board[i][j].valide == 1)
            {
                board[i][j].valide = 0;
            }
        }
    }
}

void fill(cell **board, int i, int j, int color)
/* Fonction qui permet de remplir le plateau et de modifier les pions ennemis
   en fonction du coloriage d'une case a la position i j */
{
    if (is_valid(board, i, j, color))
    {
        fill_lines(board, i, j, color);
        board[i][j].color = VERT; // On reinitialise la case actuelle a 0 pour les autres fonctions
        fill_rows(board, i, j, color);
        board[i][j].color = VERT;
        fill_diag(board, i, j, color);
        board[i][j].color = color; // On colorie la case actuelle a la fin
    }
}

void fill_lines(cell **board, int i, int j, int color)
// Fonction de remplissage concernant uniquement les lignes
{
    int line_index = check_lines(board, i, color); // indice de la ou se trouve la premiere couleur color sur une ligne i
    int copy_j = j;
    int second_color = 0;
    if (line_index >= 0 &&
        ((j + 1 < SIZE_OTHELLO && board[i][j + 1].color != VERT) ||
         (j - 1 >= 0 && board[i][j - 1].color != VERT)) &&
        check_neighbors_lines(board, i, j, color))
    // on doit d'abord avoir une case valide a tous ces criteres
    {
        second_color = j + 1;
        while (second_color < SIZE_OTHELLO && board[i][second_color].color != color)
            second_color++; // indice de la deuxieme couleur sur la ligne, pour pouvoir boucler entre les indices

        if (j > line_index && line_index <= second_color) // cas ou on doit retourner les pions de haut en bas
        {

            copy_j--;
            while (copy_j >= 0 && board[i][copy_j].color != VERT && board[i][copy_j].color != color)
            {
                board[i][copy_j].color = color; // et tant qu on ne retrouve pas la meme couleur, on remplit avec celle-ci
                copy_j--;
            }
            copy_j = j;
        }
        if (j < line_index && line_index >= second_color) // cas ou on doit retourner les pions de bas en haut
        {
            copy_j++;
            while (copy_j < SIZE_OTHELLO && board[i][copy_j].color != VERT && board[i][copy_j].color != color)
            {
                board[i][copy_j].color = color;
                copy_j++;
            }
        }
    }
}

void fill_rows(cell **board, int i, int j, int color)
// Fonction de remplissage concernant uniquement les colonnes
{
    int copy_i = i;
    int row_index = check_rows(board, j, color); // indice de la ou se trouve la premiere couleur color sur une colonne j
    int second_color = 0;
    if (row_index >= 0 &&
        ((i + 1 < SIZE_OTHELLO && board[i + 1][j].color != VERT) ||
         (i - 1 >= 0 && board[i - 1][j].color != VERT)) &&
        check_neighbors_rows(board, i, j, color))
    // on doit d'abord avoir une case valide qui correspond a tous ces criteres
    {
        second_color = i + 1;
        while (second_color < SIZE_OTHELLO && board[second_color][j].color != color)
            second_color++;

        if (i > row_index && row_index <= second_color) // cas ou on doit retourner les pions de haut en bas
        {
            copy_i--;
            while (copy_i >= 0 && board[copy_i][j].color != VERT && board[copy_i][j].color != color)
            {
                board[copy_i][j].color = color; // et tant qu on ne retrouve pas la meme couleur, on remplit avec celle-ci
                copy_i--;
            }
            copy_i = i;
        }
        if (i < row_index && row_index <= second_color) // cas ou on doit retourner les pions de bas en haut
        {
            copy_i++;
            while (copy_i < SIZE_OTHELLO && board[copy_i][j].color != VERT && board[copy_i][j].color != color)
            {
                board[copy_i][j].color = color;
                copy_i++;
            }
        }
    }
}

void fill_diag(cell **board, int i, int j, int color)
// Fonction de remplissage concernant uniquement les diagonales
{
    int cpy_i = i;
    int cpy_j = j;
    // i et j ne doivent pas etre modifies, on cree donc une copie
    if (check_diag_t_left(board, i, j, color, &cpy_i, &cpy_j) &&
        board[i - 1][j - 1].color != VERT &&
        board[i - 1][j - 1].color != color)
    {                                                                       // on verifie egalement que la case suivante n est pas verte
        while (cpy_i < i && cpy_j < j && board[cpy_i][cpy_j].color != VERT) // les copies ont desormais l emplacement d une couleur sur leur diagonale respective
        {

            board[cpy_i][cpy_j].color = color;
            cpy_i++; // On part donc de cet emplacement pour revenir a la case aux coordonnees i et j
            cpy_j++; // donc on va a l envers
        }
    }
    cpy_i = i; // et on re recupere les valeurs initiales de i et j pour chaque diagonale
    cpy_j = j; // puis on reitere l operation pour les autres diagonales
    if (check_diag_t_right(board, i, j, color, &cpy_i, &cpy_j) &&
        board[i - 1][j + 1].color != VERT &&
        board[i - 1][j + 1].color != color)
    {
        while (cpy_i < i && cpy_j > j && board[cpy_i][cpy_j].color != VERT)
        {
            board[cpy_i][cpy_j].color = color;
            cpy_i++;
            cpy_j--;
        }
    }
    cpy_i = i;
    cpy_j = j;
    if (check_diag_b_left(board, i, j, color, &cpy_i, &cpy_j) &&
        board[i + 1][j - 1].color != VERT &&
        board[i + 1][j - 1].color != color)
    {
        while (cpy_i > i && cpy_j < j && board[cpy_i][cpy_j].color != VERT)
        {
            board[cpy_i][cpy_j].color = color;
            cpy_i--;
            cpy_j++;
        }
    }
    cpy_i = i;
    cpy_j = j;
    if (check_diag_b_right(board, i, j, color, &cpy_i, &cpy_j) &&
        board[i + 1][j + 1].color != VERT &&
        board[i + 1][j + 1].color != color)
    {
        while (cpy_i > i && cpy_j > j && board[cpy_i][cpy_j].color != VERT)
        {
            board[cpy_i][cpy_j].color = color;
            cpy_i--;
            cpy_j--;
        }
    }
}
