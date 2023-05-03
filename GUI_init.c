#include "GUI_init.h"

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
/* - - - - - - - - - - - - - INIT - - - - - - - - - - - - -*/
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void Init_package(void)
{
    // Initialisation de SDL2
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
        Error("Initialisation des paramètres de la fenêtre !");
    // Initialisation des types d'images
    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
        Error("Initialisation des types d'images echoue !");
}

void Error(char *chaine)
// Renvoie un message d'erreur en fonction de la fonction
{
    SDL_Log("%s %s\n", chaine, SDL_GetError());
    exit(EXIT_FAILURE);
}


/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
/* - - - - - - - - - - - - - MATRICE - - - - - - - - - - - - -*/
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
points **Cree_mat(SDL_Window* window)
{
    // Creation des rectangles de l'Othello
    points **mat_Othello = calloc(8, sizeof(points));
    for (int i = 0; i < 8; i++)
    {
        mat_Othello[i] = calloc(8, sizeof(points));
    }

    points p_rect;
    partie ecran100 = slice_screen_100(get_screen_size(window).w, get_screen_size(window).h);

    int rect_Othello[4] = { (int)(32.3* ecran100.w)
                          , (int)(18.8* ecran100.h)
                          ,  0, (int)(5.2 * ecran100.w) };
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            // On modifie la place du rectangle
            rect_Othello[0] = rect_Othello[0] + rect_Othello[2];
            rect_Othello[1] = rect_Othello[1];
            rect_Othello[2] = (int)(ecran100.h/0.11);            
            rect_Othello[3] = rect_Othello[3];
            // On ajoute en memoire les indices des rectangles
            p_rect.x1 = rect_Othello[0];
            p_rect.y1 = rect_Othello[1];
            p_rect.x2 = rect_Othello[0] + rect_Othello[2];
            p_rect.y2 = rect_Othello[1] + rect_Othello[3];
            mat_Othello[i][j] = p_rect;
        }
        rect_Othello[0] = (int)(32.33 * ecran100.w) - rect_Othello[2];
        rect_Othello[1] = rect_Othello[1] + rect_Othello[3];
        rect_Othello[2] = rect_Othello[2];
        rect_Othello[3] = rect_Othello[3];
    }
    return mat_Othello;
}

void freeMat(points** board)
// Libere la memoire d'une matrice
{
    for (int i = 0; i < SIZE_OTHELLO; i++)
    {
        free(board[i]);
    }
    free(board);
}


/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
/* - - - - - - - - - - - - - UTILITAIRE - - - - - - - - - - - - -*/
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
char* int_to_char(int num)
{ // permet de passer un entier en chaine de caractère
    int i = 0;
    char* str = NULL;
    // compte le nombre de digit
    int temp = num;
    while (temp != 0) {
        i++;
        temp /= 10;
    }
    // Allocate memoire pour la chaine
    str = (char*)malloc(sizeof(char) * (i + 1));
    // convertir en chaine
    str[i] = '\0';
    while (i > 0) {
        str[i - 1] = (num % 10) + '0';
        num /= 10;
        i--;
    }
    return str;
}

void get_coord(points** mat_rect_Othello, int* i, int* j)
{ // Fonction permettant d'avoir les coordonees du carre a l'intereur duquel le joueur a cliquer.
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            if ((mat_rect_Othello[x][y].x1 < mouse_x && mat_rect_Othello[x][y].y1 < mouse_y) &&
                (mat_rect_Othello[x][y].x2 > mouse_x && mat_rect_Othello[x][y].y2 > mouse_y))
            {
                *i = x;
                *j = y;
            }
        }
    }
}

// ECRAN - TAILLE
partie get_screen_size(SDL_Window *window)
{
    partie ecran;
    int x, y;
    SDL_GetWindowSize(window, &x, &y);
    ecran.w = (float)x;
    ecran.h = (float)y;
    return ecran;
}
partie slice_screen_10(float w, float h)
{
    partie ecran10;
    ecran10.w = w / 10;
    ecran10.h = h / 10;
    return ecran10;
}
partie slice_screen_100(float w, float h)
{
    partie ecran100;
    ecran100.w = w / 100;
    ecran100.h = h / 100;
    return ecran100;
}

// CHARGEMENT SDL
void Dessine_coter_rect(SDL_Renderer *renderer, SDL_Rect rect, SDL_Color couleur)
{
    SDL_SetRenderDrawColor(renderer, couleur.r, couleur.g, couleur.b, couleur.a);
    SDL_RenderDrawRect(renderer, &rect);
    // On réinitialise la couleur de dessin de base (noir)
    SDL_SetRenderDrawColor(renderer, BLACK_COLOR.r, BLACK_COLOR.g, BLACK_COLOR.b, BLACK_COLOR.a);
}
void Place_image(SDL_Renderer* renderer, void * rect_place, char* fichier)
{// Place l'image de fichier au coordonée x-y
    SDL_Surface* image = NULL;
    SDL_Texture* texture = NULL;

    // Recuperation de l'image
    image = IMG_Load(fichier);
    if (image == NULL)
        Error("Recuperation de l'image echoue !");

    // Creer la texture avec l'image
    texture = SDL_CreateTextureFromSurface(renderer, image);
    if (texture == NULL)
        Error("Chargement de la texture echoue !");

    // Dessiner la texture dans le rendue
    SDL_RenderCopy(renderer, texture, NULL, rect_place);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
}
int Ecrit_txt(SDL_Renderer* renderer, int x, int y, char* text, TTF_Font* font, SDL_Color textColor)
{// ecrit du texte a un emplacement saisie
    SDL_Texture* texture = NULL;
    SDL_Surface* surface = NULL;
    SDL_Rect rect;

    int text_width;
    int text_height;
    
    surface = TTF_RenderText_Solid(font, text, textColor);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    text_width = surface->w;
    text_height = surface->h;
    
    rect.x = x;
    rect.y = y;
    rect.w = text_width;
    rect.h = text_height;

    SDL_RenderCopy(renderer, texture, NULL, &rect);    

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    return text_width;
}