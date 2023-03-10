#include "othello.h"

cell **initializeBoard()
// Fonction qui initialise le plateau de l othello
{
    cell **board = calloc(SIZE_MAX, sizeof(cell *));
    for (int i = 0; i < SIZE_MAX; i++)
    {
        board[i] = calloc(SIZE_MAX, sizeof(cell));
    }
    char c = 'A';
    for (int i = 0; i < SIZE_MAX; i++)
    {
        // attribution à chaque case son id respectif
        for (int j = 0; j < SIZE_MAX; j++)
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

    for (int i = 0; i < SIZE_MAX; i++)
    {
        printf("%d\t", i + 1);
        for (int j = 0; j < SIZE_MAX; j++)
        {
            printf("%d ", board[i][j].color);
        }
        printf("\n");
    }
}

void freeBoard(cell **board)
// Libere la memoire du tableau
{
    for (int i = 0; i < SIZE_MAX; i++)
    {
        free(board[i]);
    }
    free(board);
}

int is_valid(cell **board, int i, int j, int color)
/* Fonction verifiant la validite de la case. Une case valide est de la forme suivante :
   -La case actuelle est verte
   -Au moins un de ses voisins directs a une couleur differente de la couleur a appliquer
   -Si on cherche à poser un pion en diagonale, on regarde également les voisins diagonaux de la case actuelle
   -Au moins un pion sur les lignes, colonnes et diagonales est de la même couleur que celle a appliquer
   Renvoie 1 si la case est valide et 0 sinon
*/
{
    if (board[i][j].color == VERT && check_neighbors_lines(board, i, j, color) && check_lines(board, i, color) >= 0)
    {
        return 1;
    }
    else if (board[i][j].color == VERT && check_neighbors_rows(board, i, j, color) && check_rows(board, j, color) >= 0)
    {
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
    if (j != 0)
        left = board[i][j - 1].color != color && board[i][j - 1].color != VERT;
    if (j != SIZE_MAX - 1)
        right = board[i][j + 1].color != color && board[i][j + 1].color != VERT;
    return right || left;
}

int check_neighbors_rows(cell **board, int i, int j, int color)
// Version pour les colonnes
{
    int top = 0;
    int bottom = 0;
    if (i != 0)
        top = board[i - 1][j].color != color && board[i - 1][j].color != VERT;
    if (i != SIZE_MAX - 1)
        bottom = board[i + 1][j].color != color && board[i + 1][j].color != VERT;
    return top || bottom;
}

int check_lines(cell **board, int i, int color)
// Verifie si color se trouve sur la ligne i et renvoie son inidice
{
    for (int j = 0; j < SIZE_MAX; j++)
    {
        if (board[i][j].color == color)
        {
            return j;
        }
    }
    return -1;
}

int check_rows(cell **board, int j, int color)
// Verifie si color se trouve sur la colonne j et renvoie son inidice
{
    for (int i = 0; i < SIZE_MAX; i++)
    {
        if (board[i][j].color == color)
        {
            return i;
        }
    }
    return -1;
}

int check_diag_t_left(cell **board, int i, int j, int color)
// Verifie si color se trouve sur la diagonale superieure gauche
{
    int cpy_i = i;
    int cpy_j = j;
    while (cpy_i != 0 && cpy_j != 0)
    {
        if (board[cpy_i][cpy_j].color == color)
            return 1;
        cpy_i--;
        cpy_j--;
    }
    return 0;
}

int check_diag_t_right(cell **board, int i, int j, int color)
// Verifie si color se trouve sur la diagonale superieure droite
{
    int cpy_i = i;
    int cpy_j = j;
    while (cpy_i != 0 && cpy_j != SIZE_MAX - 1)
    {
        if (board[cpy_i][cpy_j].color == color)
            return 1;

        cpy_i--;
        cpy_j++;
    }
    return 0;
}

int check_diag_b_left(cell **board, int i, int j, int color)
// Verifie si color se trouve sur la diagonale inferieure gauche
{
    int cpy_i = i;
    int cpy_j = j;
    while (cpy_i != SIZE_MAX - 1 && cpy_j != 0)
    // diagonale inferieure gauche
    {
        if (board[cpy_i][cpy_j].color == color)
            return 1;
        cpy_i++;
        cpy_j--;
    }
    return 0;
}

int check_diag_b_right(cell **board, int i, int j, int color)
// Verifie si color se trouve sur la diagonale inferieure droite
{
    int cpy_i = i;
    int cpy_j = j;
    while (cpy_i != SIZE_MAX - 1 && cpy_j != SIZE_MAX - 1)
    // diagonale inferieure droite
    {
        if (board[cpy_i][cpy_j].color == color)
            return 1;
        cpy_i++;
        cpy_j++;
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
    // on verifie d'abord qu'on est pas en dehors du plateau
    if (i != 0 && j != 0)
        // Puis on check chaque diagonale une par une
        top_left = board[i - 1][j - 1].color != color && board[i - 1][j - 1].color != VERT && check_diag_t_left(board, i, j, color);
    if (i != 0 && j != SIZE_MAX - 1)
        top_right = board[i - 1][j + 1].color != color && board[i - 1][j + 1].color != VERT && check_diag_t_right(board, i, j, color);
    if (i != SIZE_MAX - 1 && j != 0)
        bottom_left = board[i + 1][j - 1].color != color && board[i + 1][j - 1].color != VERT && check_diag_b_left(board, i, j, color);
    if (i != SIZE_MAX - 1 && j != SIZE_MAX - 1)
        bottom_right = board[i + 1][j + 1].color != color && board[i + 1][j + 1].color != VERT && check_diag_b_right(board, i, j, color);
    return top_right || top_left || bottom_right || bottom_left;
}

void print_valid(cell **board, int color)
// Affiche toutes les cases valides du plateau
{
    for (int i = 0; i < SIZE_MAX; i++)
    {
        for (int j = 0; j < SIZE_MAX; j++)
        {
            if (is_valid(board, i, j, color))
            {
                printf("Case %s valide\n", board[i][j].id_cell);
            }
        }
    }
}

void fill(cell **board, int i, int j, int color)
{
    fill_lines(board, i, j, color);
    fill_rows(board, i, j, color);
    board[i][j].color = color; // On colorie la case actuelle a la fin
}

void fill_lines(cell **board, int i, int j, int color)
/* Fonction qui permet de remplir le plateau et de modifier les pions ennemis
   en fonction du coloriage d'une case a la position i j
   Version concernant uniquement les lignes */
{
    int line_index = check_lines(board, i, color); // indice de la ou se trouve la premiere couleur color sur une ligne i
    int second_color = 0;
    if (is_valid(board, i, j, color) && line_index >= 0) // on doit d'abord avoir une case valide
    {
        second_color = line_index + 1;
        while (second_color < SIZE_MAX && board[i][second_color].color != color)
            second_color++; // indice de la deuxieme couleur sur la ligne, pour pouvoir boucler entre les indices

        if (second_color != 8) // cas ou la case valide est entre plusieurs pions de sa couleur
        {
            while (line_index < second_color)
            {
                board[i][line_index].color = color;
                line_index++;
            }
        }
        else if (j > line_index) // cas ou on doit retourner les pions de gauche à droite
        {
            while (line_index < j)
            {
                board[i][line_index].color = color; // et tant qu on ne retrouve pas la meme couleur, on remplit avec celle-ci
                line_index++;
            }
        }
        else if (j < line_index) // cas ou on doit retourner les pions de droite à gauche
        {
            while (line_index > j)
            {
                board[i][line_index].color = color;
                line_index--;
            }
        }
    }
}

void fill_rows(cell **board, int i, int j, int color)
/* Fonction qui permet de remplir le plateau et de modifier les pions ennemis
   en fonction du coloriage d'une case a la position i j
   Version concernant uniquement les lignes */
{
    int row_index = check_rows(board, j, color); // indice de la ou se trouve la premiere couleur color sur une colonne j
    int row_index2 = 0;
    if (is_valid(board, i, j, color) && row_index >= 0) // on doit d'abord avoir une case valide
    {
        row_index2 = row_index + 1;
        while (row_index2 < SIZE_MAX && board[row_index2][j].color != color)
            row_index2++; // indice de la deuxieme couleur sur la colonne, pour pouvoir boucler entre les indices

        if (row_index2 != 8) // cas ou la case valide est entre plusieurs pions de sa couleur
        {
            while (row_index < row_index2)
            {
                board[row_index][j].color = color;
                row_index++;
            }
        }
        else if (i > row_index) // cas ou on doit retourner les pions de haut en bas
        {
            while (row_index < i)
            {
                board[row_index][j].color = color; // et tant qu on ne retrouve pas la meme couleur, on remplit avec celle-ci
                row_index++;
            }
        }
        else if (i < row_index) // cas ou on doit retourner les pions de bas en haut
        {
            while (row_index > i)
            {
                board[row_index][j].color = color;
                row_index--;
            }
        }
    }
}
