#include "GUI.h"
#include "GUI_init.h"
#include "othello.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


void Affiche_Othello(SDL_Window * window, SDL_Renderer * renderer, 
                     SDL_Surface * image_BG, SDL_Texture * texture_BG,
                     SDL_Surface * image_sides, SDL_Texture * texture_sides, int mode)// Dernier attribut a modifier !!!!!!!
{
        // Affichage de l'image de fond
    if(init_BG_image(window, renderer, image_BG, texture_BG, mode))
        Error("Affichage de l'image de fond échouée.");

    // Affichage de l'image des bordures de l'Othello
    if(init_sides_Othello(window, renderer, image_sides, texture_sides))
        Error("Affichage de l'image des bordures de l'Othello échouée.");

    // Affichage de l'interieur de l'Othello
    if(init_Othello(window, renderer, mode))
        Error("Affichage de l'interieur de l'Othello échouée.");

    // Affichage interne de l'Othello
    if(Rect_in_Othello(window, renderer))
        Error("Affichage interne de l'Othello échoué !");
}

points get_coord(points ** mat_rect_Othello)
{// Fonction permettant d'avoir les coordonées du carré a l'intereur duquel le joueur a cliquer.
 // Si le joueur ne clic pas dans un carré, la fonction renvoie {0,0,0,0}
    int mouse_x, mouse_y;
    points ret_coords = {0,0,0,0};
    SDL_GetMouseState(&mouse_x, &mouse_y);
    for (int y = 0; y < 8; y++)
    {
        for(int x = 0; x < 8; x++)
        {
            if( (mat_rect_Othello[x][y].x1 < mouse_x && mat_rect_Othello[x][y].y1 < mouse_y) && 
                (mat_rect_Othello[x][y].x2 > mouse_x && mat_rect_Othello[x][y].y2 > mouse_y))
            {
                ret_coords.x1 = mat_rect_Othello[x][y].x1;
                ret_coords.y1 = mat_rect_Othello[x][y].y1;
                ret_coords.x2 = mat_rect_Othello[x][y].x2;
                ret_coords.y2 = mat_rect_Othello[x][y].y2; 
            }
        }
    }
    return ret_coords;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////EN COURS
int draw_circle(SDL_Window * window, SDL_Renderer * renderer, int x, int y, int team)
{
    // Récupération de l'image
    image_sides = IMG_Load("Picture/Blanc1.jpg");
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
/////////////////////////////////////////////////////////////////////////////////////////////////////EN COURS
void run()
{
    SDL_Window * window = NULL;
    SDL_Renderer * renderer = NULL;

    SDL_Surface * image_BG = NULL;
    SDL_Texture * texture_BG = NULL;
    SDL_Surface * image_sides = NULL;
    SDL_Texture * texture_sides = NULL;
    
    SDL_Event e;
    points clic_rect;
    cell ** matrice_Othello;
    int mode = UwU;

    ////////////////////////////////////////////////////////// INITIALISATION DE L'INTERFACE GRAPHIQUE //////////////////////////////////////////////////////////
    init_pakage();
    // Création de la fenêtre
    window = SDL_CreateWindow("Othello", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if(window == NULL)
        Error("Création fenête échouée !");
    // Creation du rendue
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
        Error("Création du rendue échoué !");

    points ** mat_rect_Othello = Cree_mat();
    matrice_Othello = initializeBoard();
    /////////////////////////
    
    Affiche_Othello(window, renderer, image_BG, texture_BG, image_sides, texture_sides, mode);// Dernier attribut a modifier !!!!!!!);
    SDL_RenderPresent(renderer);

    
                
    //-------------------------------------------------------
    /* || Code after init : Event Code  || */
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&e))
        {
            
            if(e.type != 512 && e.type != 1024)
            {
                
                switch (e.type) {
                case SDL_MOUSEBUTTONDOWN: // Click de souris 
                    clic_rect = get_coord(mat_rect_Othello);
                    break;
                case SDL_QUIT:
                    quit = 1;
                    break;
                }
                SDL_RenderClear(renderer);
                Affiche_Othello(window, renderer, image_BG, texture_BG, image_sides, texture_sides, mode);// Dernier attribut a modifier !!!!!!!);
                SDL_RenderPresent(renderer);
            }
        }

    }
    //-------------------------------------------------------

    free(mat_rect_Othello);
    SDL_RenderClear(renderer);
    Destroy_texture(image_sides, texture_sides);
    Destroy_texture(image_BG, texture_BG);
    Quit_GUI(window, renderer);
}