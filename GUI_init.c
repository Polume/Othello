#include "GUI_init.h"


void init_pakage(void)
{
    // Initialisation de SDL2
    if(SDL_Init(SDL_INIT_EVERYTHING))
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

int init_BG_image(SDL_Window * window, SDL_Renderer * renderer, SDL_Surface* image_BG, SDL_Texture* texture_BG)
{
    // Récupération de l'image
    image_BG = IMG_Load("BG_Othello.jpg");
    /*      UwU     */
    // image_BG = IMG_Load("BG_UwU.jpg");
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

int init_sides_Othello(SDL_Window * window, SDL_Renderer * renderer, SDL_Surface* image_sides, SDL_Texture* texture_sides)
{
        // Récupération de l'image
    image_sides = IMG_Load("BG_cotes_Othello.jpg");
    if (image_sides == NULL)
        Error("Récupération de l'image_sides échoué !");

    // Créer la texture avec l'image
    texture_sides = SDL_CreateTextureFromSurface(renderer, image_sides);
    if (texture_sides == NULL)
        Error("Chargement de la texture_sides échoué !");

    // Définir un rectangle pour l'emplacement et la taille de l'image
    SDL_Rect rect_sides = { 110, 90, 880, 880 };
    // Dessiner la texture dans le rendue
    SDL_RenderCopy(renderer, texture_sides, NULL, &rect_sides);

    return EXIT_SUCCESS;
}

int init_Othello(SDL_Window * window, SDL_Renderer * renderer)
{
    // Définir un rectangle pour l'emplacement et la taille de l'image
    SDL_Rect rect_Othello = { 150, 130, 800, 800 };

    // Changement de couleur pour la base de l'Othello
    if(SDL_SetRenderDrawColor(renderer, 0, 102, 51, SDL_ALPHA_OPAQUE))
        Error("Changement de couleur pour la base de l'Othello échoué !");
    // Dessiner la base de l'Othello
    if(SDL_RenderFillRect(renderer,&rect_Othello))
        Error("Dessiner la base de l'Othello échoué !");
    
    /*              UwU             */
    // SDL_Surface * image_UwU = IMG_Load("UwU.jpg");
    // SDL_Texture * texture_UwU = SDL_CreateTextureFromSurface(renderer, image_UwU);
    // SDL_RenderCopy(renderer, texture_UwU, NULL, &rect_Othello);
    /*              UwU             */


    // Changement de couleur pour le contour de l'Othello
    if(SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE))
        Error("Changement de couleur pour le contour de l'Othello échoué !");
    // Rectangles du countour de l'Othello
    SDL_Rect rect_side1 = { 150, 120, 810, 10 };
    SDL_Rect rect_side2 = { 950, 130, 10, 810 };
    SDL_Rect rect_side3 = { 140, 930, 810, 10 };
    SDL_Rect rect_side4 = { 140, 120, 10, 810 };
    SDL_Rect const rect_sides [4] = { rect_side1, rect_side2, rect_side3, rect_side4 };
    // Dessiner le contour de l'Othello
    if(SDL_RenderFillRects(renderer, rect_sides, 4))
         Error("Dessiner le contour de l'Othello échoué !");

    return EXIT_SUCCESS;
}

points ** Rect_in_Othello(SDL_Window * window, SDL_Renderer * renderer)
{
    // Création des rectangles de l'Othello
    points ** mat_Othello = calloc(8, sizeof(points));
    for (int i = 0; i < 8; i++)
    {
        mat_Othello[i] = calloc(8, sizeof(points));
    }

    points p_rect; 
    SDL_Rect rect_Othello = { 150, 130, 0, 100 };
    
    // Changement de couleur pour les cases de l'Othello
    if(SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255))
        Error("Changement de couleur pour les cases de l'Othello échoué !");

    for(int i = 0 ; i < 8 ; i++ )
    {   
        for(int j = 0 ; j < 8 ; j++)
        {
            // On modifie la place du rectangle
            rect_Othello = (SDL_Rect) { .x = rect_Othello.x + rect_Othello.w,
                                        .y = rect_Othello.y,
                                        .w = 100,
                                        .h = rect_Othello.h };
            // On ajoute en mémoire les indices des rectangles
            p_rect.x1 = rect_Othello.x - rect_Othello.w;
            p_rect.y1 = rect_Othello.y;
            p_rect.x2 = rect_Othello.x;
            p_rect.y2 = rect_Othello.y + rect_Othello.h;
            mat_Othello[i][j] = p_rect;
            // Dessiner les Rectangles internes de l'Othello
            if(SDL_RenderDrawRect(renderer,&rect_Othello))
                Error("Dessiner les Rectangles internes de l'Othello échoué !");
        }
        
        rect_Othello = (SDL_Rect) { .x = 150 - rect_Othello.w, 
                                    .y = rect_Othello.y + rect_Othello.h, 
                                    .w = rect_Othello.w, 
                                    .h = rect_Othello.h };
    }
    return mat_Othello;
}