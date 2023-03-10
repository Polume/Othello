#include "GUI.h"
#include "GUI_init.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


void Affiche_Othello(SDL_Window * window, SDL_Renderer * renderer, 
                     SDL_Surface * image_BG, SDL_Texture * texture_BG,
                     SDL_Surface * image_sides, SDL_Texture * texture_sides, points ** mat_rect_Othello)// Dernier attribut a modifier !!!!!!!
{
        // Affichage de l'image de fond
    if(init_BG_image(window, renderer, image_BG, texture_BG))
        Error("Affichage de l'image de fond échouée.");

    // Affichage de l'image des bordures de l'Othello
    if(init_sides_Othello(window, renderer, image_sides, texture_sides))
        Error("Affichage de l'image des bordures de l'Othello échouée.");

    // Affichage de l'interieur de l'Othello
    if(init_Othello(window, renderer))
        Error("Affichage de l'interieur de l'Othello échouée.");

    // Affichage interne de l'Othello
    mat_rect_Othello = Rect_in_Othello(window, renderer);
}


void run()
{
    SDL_Window * window = NULL;
    SDL_Renderer * renderer = NULL;

    SDL_Surface * image_BG = NULL;
    SDL_Texture * texture_BG = NULL;
    SDL_Surface * image_sides = NULL;
    SDL_Texture * texture_sides = NULL;
    
    SDL_Event e;

    ////////////////////////////////////////////////////////// INITIALISATION DE L'INTERFACE GRAPHIQUE //////////////////////////////////////////////////////////
    init_pakage();
    // Création de la fenêtre
    window = SDL_CreateWindow("Othello", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if(window == NULL)
        Error("Création fenête échouée !");
    // Creation du rendue
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == NULL)
        Error("Création du rendue échoué !");

    points ** mat_rect_Othello = NULL;
    ////////////////////////////////////////////////////////// FIN INITIALISATION DE L'INTERFACE GRAPHIQUE //////////////////////////////////////////////////////////
 
    //-------------------------------------------------------
    /* || Code after init : Event Code  || */
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&e))
        {
            if(e.type != 512 && e.type != 1024)
            {
                printf("\t%d\n",e.type);
                switch (e.type) {
                case SDL_MOUSEBUTTONDOWN: // Click de souris 
                    SDL_Log("+clic");
                    break;
                case SDL_MOUSEBUTTONUP: // Click de souris relâché
                    SDL_Log("-clic");
                    break;
                case SDL_QUIT:
                    quit = 1;
                    break;
                }

                SDL_RenderClear(renderer);
                Affiche_Othello(window, renderer, image_BG, texture_BG, image_sides, texture_sides, mat_rect_Othello);// Dernier attribut a modifier !!!!!!!);
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