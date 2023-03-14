#include "GUI_init.h"


void init_pakage(void)
{
    // Initialisation de SDL2
    if(SDL_Init(SDL_INIT_VIDEO))
        Error("Initialisation des paramètres de la fenêtre !");
    //Initialisation des types d'images
    if(! IMG_Init(IMG_INIT_PNG|IMG_INIT_JPG))
        Error("Initialisation des types d'images échoué !");
}

void Quit_GUI(SDL_Window * window, SDL_Renderer * renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Destroy_texture(SDL_Surface* image, SDL_Texture* texture)
{
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
}

void Error(char *chaine)
// Renvoie un message d'erreur en fonction de la fonction
{
    SDL_Log("%s %s\n", chaine, SDL_GetError());
    exit(EXIT_FAILURE);
}

int init_BG_image(SDL_Window * window, SDL_Renderer * renderer, SDL_Surface* image_BG, SDL_Texture* texture_BG, int mode)
{
    // Récupération de l'image
    image_BG = IMG_Load("Pictures/BG_Othello.jpg");
    /*      UwU     */
    if(mode == 1)
        image_BG = IMG_Load("Pictures/BG_UwU.jpg");
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

int init_base_Othello(SDL_Window * window, SDL_Renderer * renderer, SDL_Surface* image_base, SDL_Texture* texture_base)
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
    SDL_Rect rect_sides = { 110, 90, 880, 880 };
    // Dessiner la texture dans le rendue
    SDL_RenderCopy(renderer, texture_base, NULL, &rect_sides);

    return EXIT_SUCCESS;
}

int init_Othello(SDL_Window * window, SDL_Renderer * renderer, SDL_Surface * image_mode, SDL_Texture * texture_mode, int mode)
{
    // Définir un rectangle pour l'emplacement et la taille de l'image
    SDL_Rect rect_Othello = { 150, 130, 800, 800 };


    // Changement de couleur pour la base de l'Othello
    if(SDL_SetRenderDrawColor(renderer, 0, 102, 40, SDL_ALPHA_OPAQUE))
        Error("Changement de couleur pour la base de l'Othello échoué !");
    // Dessiner la base de l'Othello
    if(SDL_RenderFillRect(renderer,&rect_Othello))
        Error("Dessiner la base de l'Othello échoué !");
    
    /*              UwU             */
    if(mode == 1)
    {
        image_mode = IMG_Load("Pictures/UwU.jpg");
        texture_mode = SDL_CreateTextureFromSurface(renderer, image_mode);
        SDL_RenderCopy(renderer, texture_mode, NULL, &rect_Othello);
    }
    /*              UwU             */

    return EXIT_SUCCESS;
}

points ** Cree_mat()
{
    // Création des rectangles de l'Othello
    points ** mat_Othello = calloc(8, sizeof(points));
    for (int i = 0; i < 8; i++)
    {
        mat_Othello[i] = calloc(8, sizeof(points));
    }

    points p_rect; 
    int rect_Othello[4] = { 150, 130, 0, 100 };

    for(int i = 0 ; i < 8 ; i++ )
    {   
        for(int j = 0 ; j < 8 ; j++)
        {
            // On modifie la place du rectangle
            rect_Othello[0] = rect_Othello[0] + rect_Othello[2];
            rect_Othello[1] =  rect_Othello[1];
            rect_Othello[2] =  100;
            rect_Othello[3] =  rect_Othello[3];
            // On ajoute en mémoire les indices des rectangles
            p_rect.x1 = rect_Othello[0];
            p_rect.y1 = rect_Othello[1];
            p_rect.x2 = rect_Othello[0] + rect_Othello[2];
            p_rect.y2 = rect_Othello[1] + rect_Othello[3];
            mat_Othello[i][j] = p_rect;
        }
        
        rect_Othello[0] =  150 - rect_Othello[2];
        rect_Othello[1] =  rect_Othello[1] + rect_Othello[3]; 
        rect_Othello[2] =  rect_Othello[2]; 
        rect_Othello[3] =  rect_Othello[3];
    }
    return mat_Othello;
}