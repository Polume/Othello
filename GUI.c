#include "GUI.h"
#include "GUI_init.h"
#include "othello.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


void Affiche_Othello(SDL_Window * window, SDL_Renderer * renderer, 
                     SDL_Surface * image_BG, SDL_Texture * texture_BG,
                     SDL_Surface * image_sides, SDL_Texture * texture_sides, 
                     SDL_Surface * image_mode, SDL_Texture * texture_mode, int mode)
{
    // Affichage de l'image de fond
    if(init_BG_image(window, renderer, image_BG, texture_BG, mode))
        Error("Affichage de l'image de fond échouée.");

    // Affichage de l'interieur de l'Othello
    if(init_Othello(window, renderer, image_mode, texture_mode, mode))
        Error("Affichage de l'interieur de l'Othello échouée.");

    // Affichage de l'image de l'Othello
    if(init_base_Othello(window, renderer, image_sides, texture_sides))
        Error("Affichage de l'image de l'Othello échouée.");

    
}

points get_coord(points ** mat_rect_Othello, int * i, int * j)
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
                *i = x;
                *j = y;
            }
        }
    }
    return ret_coords;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////EN COURS
int draw_circle(SDL_Window * window, SDL_Renderer * renderer, 
                SDL_Surface * image_pion, SDL_Texture * texture_pion, 
                int x, int y, int team, int mode)
{
    if(mode != UwU)
    {
        if(team == 1)
        {
            // Récupération de l'image
            image_pion = IMG_Load("Pictures/White.png");
            if (image_pion == NULL)
                Error("Récupération de l'image_pion échoué !");

            // Créer la texture avec l'image
            texture_pion = SDL_CreateTextureFromSurface(renderer, image_pion);
            if (texture_pion == NULL)
                Error("Chargement de la texture_pion échoué !");

            // Définir un rectangle pour l'emplacement et la taille de l'image
            SDL_Rect rect_pion = { x+5, y+3, 85, 85 };
            // Dessiner la texture dans le rendue
            SDL_RenderCopy(renderer, texture_pion, NULL, &rect_pion);
        }
        else if(team == 2)
        {
            // Récupération de l'image
            image_pion = IMG_Load("Pictures/Black.png");
            if (image_pion == NULL)
                Error("Récupération de l'image_pion échoué !");

            // Créer la texture avec l'image
            texture_pion = SDL_CreateTextureFromSurface(renderer, image_pion);
            if (texture_pion == NULL)
                Error("Chargement de la texture_pion échoué !");

            // Définir un rectangle pour l'emplacement et la taille de l'image
            SDL_Rect rect_pion = { x+5, y+3, 85, 85 };
            // Dessiner la texture dans le rendue
            SDL_RenderCopy(renderer, texture_pion, NULL, &rect_pion);  
        }
        else 
        {
            return EXIT_FAILURE;
        }
    }
    else if (mode == UwU)
    {
        if(team == 1)
        {
            // Récupération de l'image
            image_pion = IMG_Load("Pictures/White1.png");
            if (image_pion == NULL)
                Error("Récupération de l'image_pion échoué !");

            // Créer la texture avec l'image
            texture_pion = SDL_CreateTextureFromSurface(renderer, image_pion);
            if (texture_pion == NULL)
                Error("Chargement de la texture_pion échoué !");

            // Définir un rectangle pour l'emplacement et la taille de l'image
            SDL_Rect rect_pion = { x+5, y+3, 85, 85 };
            // Dessiner la texture dans le rendue
            SDL_RenderCopy(renderer, texture_pion, NULL, &rect_pion);
        }
        else if(team == 2)
        {
            // Récupération de l'image
            image_pion = IMG_Load("Pictures/Black1.png");
            if (image_pion == NULL)
                Error("Récupération de l'image_pion échoué !");

            // Créer la texture avec l'image
            texture_pion = SDL_CreateTextureFromSurface(renderer, image_pion);
            if (texture_pion == NULL)
                Error("Chargement de la texture_poin échoué !");

            // Définir un rectangle pour l'emplacement et la taille de l'image
            SDL_Rect rect_pion = { x+5, y+3, 85, 85 };
            // Dessiner la texture dans le rendue
            SDL_RenderCopy(renderer, texture_pion, NULL, &rect_pion);  
        }
        else
        {
            return EXIT_FAILURE;
        }
    }  
    else
    {
        return EXIT_FAILURE;
    } 
    return EXIT_SUCCESS;
}


void draw_board(SDL_Window * window, SDL_Renderer * renderer, 
                SDL_Surface * image_pion, SDL_Texture * texture_pion,
                cell ** matrice_Othello, int pos_x, int pos_y, int mode)
{
    for(int i = 0 ; i < 8 ; i++)
    {
        for(int j = 0 ; j < 8 ; j++)
        {
            if(matrice_Othello[i][j].color != 0)
            {
                if(draw_circle(window, renderer, image_pion, texture_pion, pos_x, pos_y, matrice_Othello[i][j].color, mode))
                    Error("Placement de pion échoué !");
            }
        }
    }
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
    SDL_Surface * image_pion = NULL;
    SDL_Texture * texture_pion = NULL;
    SDL_Surface * image_mode = NULL;
    SDL_Texture * texture_mode = NULL;

    SDL_Event e;
    points clic_rect;
    cell ** matrice_Othello;
    int mode = UwU;
    int i, j, team = 1;

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
    //////////////////////////////////////////////////////////
    
    Affiche_Othello(window, renderer, image_BG, texture_BG, image_sides, texture_sides, image_mode, texture_mode, mode);// Dernier attribut a modifier !!!!!!!);
    SDL_RenderPresent(renderer);

    
                
    //-------------------------------------------------------
    /* || Code after init : Event Code  || */
    int quit = 0;
    while (!quit) {
        SDL_WaitEvent(&e);
        while (e.type != 512 || e.type != 1024)
        {
            if(1)
            {
                switch (e.type) {
                case SDL_MOUSEBUTTONDOWN: // Click de souris 
                    //On récupère le placement de la case liée au clic souris ainsi que son "emplacement"
                    clic_rect = get_coord(mat_rect_Othello, &i, &j);
                    printf("%d - %d \n",clic_rect.x1, clic_rect.y1);
                    //Place un pion de l'équipe ayant pas joué précédement
                    if(team == 1)
                        team = 2;
                    else    
                        team = 1;
                    break;
                case SDL_QUIT:
                    quit = 1;
                    break;
                }
                //-------------------Rénitialisation des variables de textures-------------------//
                SDL_RenderClear(renderer);
                Destroy_texture(image_pion, texture_pion);
                Destroy_texture(image_mode, texture_mode);
                Destroy_texture(image_sides, texture_sides);
                Destroy_texture(image_BG, texture_BG);
                //------------------Redessinner les textures et les formes-----------------------//
                Affiche_Othello(window, renderer, image_BG, texture_BG, image_sides, texture_sides, image_mode, texture_mode, mode);// Dernier attribut a modifier !!!!!!!);
                if(clic_rect.x1 != 0)
                {
                    draw_board( window, renderer, image_pion, texture_pion, matrice_Othello, clic_rect.x1, clic_rect.y1, mode);
                }
                SDL_RenderPresent(renderer);
                //-----------------------------------------------------------------------------//
                
                
            }
        }

    }
    //-----------Desttruction des variables pointeurs-----------//
    Destroy_texture(image_pion, texture_pion);
    Destroy_texture(image_mode, texture_mode);
    Destroy_texture(image_sides, texture_sides);
    Destroy_texture(image_BG, texture_BG);
    SDL_RenderClear(renderer);
    free(mat_rect_Othello);
    Quit_GUI(window, renderer);
}