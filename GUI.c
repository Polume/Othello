#include "GUI.h"
#include "GUI_init.h"
#include "othello.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


void Affiche_Othello(SDL_Window * window, SDL_Renderer * renderer, 
                     SDL_Surface * image_BG, SDL_Texture * texture_BG,
                     SDL_Surface * image_base, SDL_Texture * texture_base, 
                     SDL_Surface * image_mode, SDL_Texture * texture_mode, int mode)
{
    // Affichage de l'image de fond
    if(init_BG_image(window, renderer, image_BG, texture_BG, mode))
        Error("Affichage de l'image de fond échouée.");

    // Affichage de l'interieur de l'Othello
    if(init_Othello(window, renderer, image_mode, texture_mode, mode))
        Error("Affichage de l'interieur de l'Othello échouée.");

    // Affichage de l'image de l'Othello
    if(init_base_Othello(window, renderer, image_base, texture_base))
        Error("Affichage de l'image de l'Othello échouée.");

    
}

void init_pion(SDL_Window * window, SDL_Renderer * renderer, 
                    SDL_Surface * image_pion, SDL_Texture * texture_pion,
                    cell ** matrice_Othello, points ** mat_rect_Othello, int mode)
{
    for (int y = 0; y < 8; y++)
    {
        for(int x = 0; x < 8; x++)
        {
            if(matrice_Othello[x][y].color == 1)
            {
                draw_circle(window, renderer, image_pion, texture_pion, mat_rect_Othello[x][y].x1, mat_rect_Othello[x][y].y1, matrice_Othello[x][y].color, mode);
            }
            else if (matrice_Othello[x][y].color == 2)
            {
                draw_circle(window, renderer, image_pion, texture_pion, mat_rect_Othello[x][y].x1, mat_rect_Othello[x][y].y1, matrice_Othello[x][y].color, mode);
            }
        }
    }
}

void get_coord(points ** mat_rect_Othello, int * i, int * j)
{// Fonction permettant d'avoir les coordonées du carré a l'intereur duquel le joueur a cliquer.
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);
    for (int y = 0; y < 8; y++)
    {
        for(int x = 0; x < 8; x++)
        {
            if( (mat_rect_Othello[x][y].x1 < mouse_x && mat_rect_Othello[x][y].y1 < mouse_y) && 
                (mat_rect_Othello[x][y].x2 > mouse_x && mat_rect_Othello[x][y].y2 > mouse_y))
            {
                *i = x;
                *j = y;
            }
        }
    }
}

void Update_Othello(SDL_Window * window, SDL_Renderer * renderer, 
                    SDL_Surface * image_pion, SDL_Texture * texture_pion,
                    cell ** matrice_Othello, points ** mat_rect_Othello,
                    int x, int y, int mode)
{
    if(matrice_Othello[x][y].color == 1) // Si pion Blanc enregistrer, placer pion blanc.
        draw_circle(window, renderer, image_pion, texture_pion, mat_rect_Othello[x][y].x1, mat_rect_Othello[x][y].y1, matrice_Othello[x][y].color, mode);

    else if (matrice_Othello[x][y].color == 2) // Sinon, si pion Noir enregistrer, placer pion noir.
        draw_circle(window, renderer, image_pion, texture_pion, mat_rect_Othello[x][y].x1, mat_rect_Othello[x][y].y1, matrice_Othello[x][y].color, mode);
}

void draw_circle(SDL_Window * window, SDL_Renderer * renderer, 
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
    }
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
                draw_circle(window, renderer, image_pion, texture_pion, pos_x, pos_y, matrice_Othello[i][j].color, mode);
            }
        }
    }
}

void test(SDL_Renderer * renderer)
{
    SDL_Rect rect_Othello = { 0, 0, WIDTH, HEIGHT };

        // Changement de couleur pour la base de l'Othello
        if(SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_TRANSPARENT))
            Error("Changement de couleur pour la base de l'Othello échoué !");
        // Dessiner la base de l'Othello
        SDL_RenderDrawRect(renderer,&rect_Othello);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////EN COURS
void run()
{
    SDL_Window * window = NULL;
    SDL_Renderer * renderer = NULL;

    SDL_Surface * image_BG = NULL;
    SDL_Texture * texture_BG = NULL;
    SDL_Surface * image_base = NULL;
    SDL_Texture * texture_base = NULL;
    SDL_Surface * image_pion = NULL;
    SDL_Texture * texture_pion = NULL;
    SDL_Surface * image_mode = NULL;
    SDL_Texture * texture_mode = NULL;

    SDL_Event e;
    cell ** matrice_Othello;
    int mode = 0;
    int i, j, cpt_pion = 4,team = 1;

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
    
    SDL_DestroyTexture(texture_BG);
    SDL_DestroyTexture(texture_mode);
    SDL_DestroyTexture(texture_base);
    SDL_FreeSurface(image_BG);
    SDL_FreeSurface(image_mode);
    SDL_FreeSurface(image_base);
    SDL_RenderClear(renderer);

    points ** mat_rect_Othello = Cree_mat();
    matrice_Othello = initializeBoard();
    Affiche_Othello(window, renderer, image_BG, texture_BG, image_base, texture_base, image_mode, texture_mode, mode);
    init_pion(  window, renderer, image_pion, texture_pion,
                matrice_Othello, mat_rect_Othello, mode);
    SDL_RenderPresent(renderer);
    // SDL_RenderPresent(renderer);
    
    //////////////////////////////////////////////////////////            
    //-------------------------------------------------------
    /* || Code after init : Event Code  || */
    SDL_bool quit = SDL_FALSE;
    while (!quit) 
    {


        // SDL_RenderClear(renderer);
        // SDL_DestroyTexture(texture_BG);
        // SDL_DestroyTexture(texture_mode);
        // SDL_DestroyTexture(texture_base);
        // SDL_FreeSurface(image_BG);
        // SDL_FreeSurface(image_mode);
        // SDL_FreeSurface(image_base);
        // Affiche_Othello(window, renderer, image_BG, texture_BG, image_base, texture_base, image_mode, texture_mode, mode);
        // init_pion(  window, renderer, image_pion, texture_pion,
        //             matrice_Othello, mat_rect_Othello, mode);

        SDL_RenderPresent(renderer);

        while(SDL_PollEvent(&e))
        {
            printf("%d\n", e.type);
            if ((e.type == SDL_MOUSEBUTTONDOWN) || (e.type == SDL_QUIT))
            {
                printf("%d\n", e.type);
                switch (e.type) 
                {
                    case SDL_MOUSEBUTTONDOWN: // Click de souris
                        if(team == 1)
                            team = 2;
                        else    
                            team = 1;
                        get_coord( mat_rect_Othello, &i, &j );
                        if((0<=i || i>=7) && (0<=j || j>=7))
                        {
                            printf("i : %d - j : %d -__- team : %d\n", i, j, team);
                            matrice_Othello[i][j].color = team;
                            printBoard(matrice_Othello);
                        }
                        break;
                    case SDL_QUIT:
                        quit = SDL_TRUE;
                        continue;
                }  


            }
        }
        
    }

    //         printf("%d\n", e.type);
    //         switch (e.type) 
    //         {
    //             case SDL_MOUSEBUTTONDOWN: // Click de souris
    //                 if(team == 1)
    //                     team = 2;
    //                 else    
    //                     team = 1;
                    
    //                 get_coord( mat_rect_Othello, &i, &j );
    //                 if((0<=i || i>=7) && (0<=j || j>=7))
    //                 {
    //                     printf("i : %d - j : %d -__- team : %d\n", i, j, team);
    //                     matrice_Othello[i][j].color = team;
    //                     printBoard(matrice_Othello);

    //                     // clear_renderer(renderer,image_BG,texture_BG,image_base,texture_base,image_mode,texture_mode);
    //                     Affiche_Othello(window, renderer, image_BG, texture_BG, image_base, texture_base, image_mode, texture_mode, mode);
    //                     Update_Othello( window              , renderer, 
    //                                     image_pion[cpt_pion], texture_pion[cpt_pion],
    //                                     matrice_Othello     , mat_rect_Othello, 
    //                                     i, j, mode);
    //                     cpt_pion++;
    //                 }
    //                 continue;
    //             case SDL_QUIT:
    //                 quit = SDL_TRUE;
    //                 continue;
    //         }  
    //     }   
    // }

    //-----------Desttruction des variables pointeurs-----------//
    SDL_DestroyTexture(texture_BG);
    SDL_DestroyTexture(texture_mode);
    SDL_DestroyTexture(texture_base);

    SDL_FreeSurface(image_BG);
    SDL_FreeSurface(image_mode);
    SDL_FreeSurface(image_base);

    SDL_RenderClear(renderer);
    Quit_GUI(window, renderer);

    free(matrice_Othello);
    free(mat_rect_Othello);
}