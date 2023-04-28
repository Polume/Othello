#include "GUI_init.h"

void init_package(void)
{
    // Initialisation de SDL2
    if (SDL_Init(SDL_INIT_VIDEO))
        Error("Initialisation des paramètres de la fenêtre !");
    // Initialisation des types d'images
    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
        Error("Initialisation des types d'images échoué !");
}

void Quit_GUI(SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Error(char *chaine)
// Renvoie un message d'erreur en fonction de la fonction
{
    SDL_Log("%s %s\n", chaine, SDL_GetError());
    exit(EXIT_FAILURE);
}

int init_BG_image(SDL_Window *window, SDL_Renderer *renderer, SDL_Surface *image_BG, SDL_Texture *texture_BG, int mode)
{
    // Récupération de l'image
    image_BG = IMG_Load("Pictures/BG_Othello.png");
    
    if (mode == 0)
        image_BG = IMG_Load("Pictures/Oth.png"); 
    else if (mode == 2)
        image_BG = IMG_Load("Pictures/BG_Othello.png");
    /*      UwU     */
    else if (mode == 2)
        image_BG = IMG_Load("Pictures/BG_UwU.png");
    /*      UwU     */
    if (image_BG == NULL)
        Error("Récupération de l'image échoué !");

    // Créer la texture avec l'image
    texture_BG = SDL_CreateTextureFromSurface(renderer, image_BG);
    if (texture_BG == NULL)
        Error("Chargement de la texture échoué !");

    // Dessiner la texture dans le rendue
    SDL_RenderCopy(renderer, texture_BG, NULL, NULL);

    return EXIT_SUCCESS;
}

int init_base_Othello(SDL_Window *window, SDL_Renderer *renderer, SDL_Surface *image_base, SDL_Texture *texture_base)
{
    // Récupération de l'image
    image_base = IMG_Load("Pictures/Base_Othello.png");
    if (image_base == NULL)
        Error("Récupération de l'image_base échoué !");

    // Créer la texture avec l'image
    texture_base = SDL_CreateTextureFromSurface(renderer, image_base);
    if (texture_base == NULL)
        Error("Chargement de la texture_base échoué !");

    // Définir un rectangle pour l'emplacement et la taille de l'image
    SDL_Rect rect_sides = {WIDTH/4, HEIGHT/6, 880, 880};
    // Dessiner la texture dans le rendue
    SDL_RenderCopy(renderer, texture_base, NULL, &rect_sides);

    return EXIT_SUCCESS;
}

int init_Othello(SDL_Window *window, SDL_Renderer *renderer, SDL_Surface *image_mode, SDL_Texture *texture_mode, int mode)
{
    // Définir un rectangle pour l'emplacement et la taille de l'image
    SDL_Rect rect_Othello = {WIDTH/4, HEIGHT/6, 880, 880};

    // Changement de couleur pour la base de l'Othello
    if (SDL_SetRenderDrawColor(renderer, 0, 102, 40, SDL_ALPHA_OPAQUE))
        Error("Changement de couleur pour la base de l'Othello échoué !");
    // Dessiner la base de l'Othello
    if (SDL_RenderFillRect(renderer, &rect_Othello))
        Error("Dessiner la base de l'Othello échoué !");

    /*              UwU             */
    if (mode == 2)
    {
        image_mode = IMG_Load("Pictures/UwU.png");
        texture_mode = SDL_CreateTextureFromSurface(renderer, image_mode);
        SDL_RenderCopy(renderer, texture_mode, NULL, &rect_Othello);
    }
    /*              UwU             */

    return EXIT_SUCCESS;
}

points **Cree_mat()
{
    // Création des rectangles de l'Othello
    points **mat_Othello = calloc(8, sizeof(points));
    for (int i = 0; i < 8; i++)
    {
        mat_Othello[i] = calloc(8, sizeof(points));
    }

    points p_rect;
    int rect_Othello[4] = {WIDTH/4 + 40, HEIGHT/6 + 40, 0, 100};

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            // On modifie la place du rectangle
            rect_Othello[0] = rect_Othello[0] + rect_Othello[2];
            rect_Othello[1] = rect_Othello[1];
            rect_Othello[2] = 100;
            rect_Othello[3] = rect_Othello[3];
            // On ajoute en mémoire les indices des rectangles
            p_rect.x1 = rect_Othello[0];
            p_rect.y1 = rect_Othello[1];
            p_rect.x2 = rect_Othello[0] + rect_Othello[2];
            p_rect.y2 = rect_Othello[1] + rect_Othello[3];
            mat_Othello[i][j] = p_rect;
        }

        rect_Othello[0] = WIDTH/4 + 40 - rect_Othello[2];
        rect_Othello[1] = rect_Othello[1] + rect_Othello[3];
        rect_Othello[2] = rect_Othello[2];
        rect_Othello[3] = rect_Othello[3];
    }
    return mat_Othello;
}

partie get_screen_size()
{
    SDL_DisplayMode current;
    partie ecran;
    SDL_GetCurrentDisplayMode(0, &current);
    ecran.w = current.w;
    ecran.h = current.h;
    return ecran;
}
partie slice_screen_10(int w, int h)
{
    partie ecran10;
    ecran10.w = w / 10;
    ecran10.h = h / 10;
    return ecran10;
}
partie slice_screen_100(int w, int h)
{
    partie ecran100;
    ecran100.w = w / 100;
    ecran100.h = h / 100;
    return ecran100;
}

points * init_bouttons(SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* image_bouttons, SDL_Texture* texture_bouttons)
{
    points * pts_bouttons = malloc(2*sizeof(points));
    partie ecran10 = slice_screen_10(get_screen_size().w, get_screen_size().h);
    // Premier Boutton 
    image_bouttons = IMG_Load("Pictures/Contre_Joueur.png");
    if (image_bouttons == NULL)
        Error("Récupération de Contre_Joueur.png échoué !");
    // Créer la texture avec l'image
    texture_bouttons = SDL_CreateTextureFromSurface(renderer, image_bouttons);
    if (texture_bouttons == NULL)
        Error("Chargement de la texture de Contre_Joueur.png échoué !");
    // Définir un rectangle pour l'emplacement et la taille de l'image
    pts_bouttons[0].x1 = ecran10.w *2;
    pts_bouttons[0].y1 = ecran10.h *5;
    pts_bouttons[0].x2 = (ecran10.w *2) + (ecran10.w *2);
    pts_bouttons[0].y2 = (ecran10.h *5) + (ecran10.h *2);
    SDL_Rect rect_boutton_Joueurs = { pts_bouttons[0].x1, pts_bouttons[0].y1, ecran10.w *2, ecran10.h *2 };
    // Dessiner la texture dans le rendue
    SDL_RenderCopy(renderer, texture_bouttons, NULL, &rect_boutton_Joueurs);

    // Second Boutton
    image_bouttons = IMG_Load("Pictures/Contre_IA.png");
    if (image_bouttons == NULL)
        Error("Récupération de Contre_IA.png échoué !");
    // Créer la texture avec l'image
    texture_bouttons = SDL_CreateTextureFromSurface(renderer, image_bouttons);
    if (texture_bouttons == NULL)
        Error("Chargement de la texture de Contre_IA.png échoué !");
    // Définir un rectangle pour l'emplacement et la taille de l'image
    pts_bouttons[1].x1 = (ecran10.w *6);
    pts_bouttons[1].y1 = (ecran10.h *5);
    pts_bouttons[1].x2 = (ecran10.w *6) + (ecran10.w *2);
    pts_bouttons[1].y2 = (ecran10.h *5) + (ecran10.h *2);
    SDL_Rect rect_boutton_IA = { pts_bouttons[1].x1, pts_bouttons[1].y1,  ecran10.w *2, ecran10.h *2 };
    // Dessiner la texture dans le rendue
    SDL_RenderCopy(renderer, texture_bouttons, NULL, &rect_boutton_IA);
    
    return pts_bouttons;
}