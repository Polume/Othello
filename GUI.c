#include "GUI.h"
#include "GUI_init.h"
#include "othello.h"
#include "linked_list.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void Affiche_Othello(SDL_Window *window, SDL_Renderer *renderer,
                     SDL_Surface *image_BG, SDL_Texture *texture_BG,
                     SDL_Surface *image_base, SDL_Texture *texture_base,
                     SDL_Surface *image_mode, SDL_Texture *texture_mode, int mode)
{
    // Affichage de l'image de fond
    if (init_BG_image(window, renderer, image_BG, texture_BG, mode))
        Error("Affichage de l'image de fond échouée.");

    // Affichage de l'interieur de l'Othello
    if (init_Othello(window, renderer, image_mode, texture_mode, mode))
        Error("Affichage de l'interieur de l'Othello échouée.");

    // Affichage de l'image de l'Othello
    if (init_base_Othello(window, renderer, image_base, texture_base))
        Error("Affichage de l'image de l'Othello échouée.");
}

void Place_pion(SDL_Window *window, SDL_Renderer *renderer,
                SDL_Surface *image_pion, SDL_Texture *texture_pion,
                cell **matrice_Othello, points **mat_rect_Othello, int mode)
{
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            if (matrice_Othello[x][y].color == 1)
            {
                Dessine_pion(window, renderer, image_pion, texture_pion, mat_rect_Othello[x][y].x1, mat_rect_Othello[x][y].y1, matrice_Othello[x][y].color, mode);
            }
            else if (matrice_Othello[x][y].color == 2)
            {
                Dessine_pion(window, renderer, image_pion, texture_pion, mat_rect_Othello[x][y].x1, mat_rect_Othello[x][y].y1, matrice_Othello[x][y].color, mode);
            }
        }
    }
}

void Place_pion_border(SDL_Window *window, SDL_Renderer *renderer,
                       SDL_Surface *image_pion, SDL_Texture *texture_pion,
                       cell **matrice_Othello, points **mat_rect_Othello,
                       int team, int mode)
{
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            // printf("valid ? %d\n", matrice_Othello[x][y].valide);
            if (matrice_Othello[x][y].valide == 1)
            {
                // printf("%d\t%d\n", mat_rect_Othello[x][y].x1, mat_rect_Othello[x][y].y1);
                Dessine_pion_border(window, renderer, image_pion, texture_pion, mat_rect_Othello[x][y].x1, mat_rect_Othello[x][y].y1, team, mode);
            }
        }
    }
}

void get_coord(points **mat_rect_Othello, int *i, int *j)
{ // Fonction permettant d'avoir les coordonées du carré a l'intereur duquel le joueur a cliquer.
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

void Dessine_pion(SDL_Window *window, SDL_Renderer *renderer,
                  SDL_Surface *image_pion, SDL_Texture *texture_pion,
                  int x, int y, int team, int mode)
{
    if (mode != UwU)
    {
        if (team == 1)
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
            SDL_Rect rect_pion = {x + 5, y + 3, 85, 85};
            // Dessiner la texture dans le rendue
            SDL_RenderCopy(renderer, texture_pion, NULL, &rect_pion);
        }
        else if (team == 2)
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
            SDL_Rect rect_pion = {x + 5, y + 3, 85, 85};
            // Dessiner la texture dans le rendue
            SDL_RenderCopy(renderer, texture_pion, NULL, &rect_pion);
        }
    }
    else if (mode == UwU)
    {
        if (team == 1)
        {
            // Récupération de l'image
            image_pion = IMG_Load("Pictures/White1.png");
            if (image_pion == NULL)
                Error("Récupération de l'image_pion échoué !");

            // Créer la texture avec l'image
            texture_pion = SDL_CreateTextureFromSurface(renderer, image_pion);
            if (texture_pion == NULL)
                Error("Chargement de la texture_pion échoué !");

            // Définir un rect c dcfv cv vcangle pour l'emplacement et la taille de l'image
            SDL_Rect rect_pion = {x + 5, y + 3, 85, 85};
            // Dessiner la texture dans le rendue
            SDL_RenderCopy(renderer, texture_pion, NULL, &rect_pion);
        }
        else if (team == 2)
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
            SDL_Rect rect_pion = {x + 5, y + 3, 85, 85};
            // Dessiner la texture dans le rendue
            SDL_RenderCopy(renderer, texture_pion, NULL, &rect_pion);
        }
    }
}

void Dessine_pion_border(SDL_Window *window, SDL_Renderer *renderer,
                         SDL_Surface *image_pion, SDL_Texture *texture_pion,
                         int x, int y, int team, int mode)
{
    if (mode != UwU)
    {
        if (team == 1)
        {
            // Récupération de l'image
            image_pion = IMG_Load("Pictures/White_Border.png");
            if (image_pion == NULL)
                Error("Récupération de l'image_pion échoué !");

            // Créer la texture avec l'image
            texture_pion = SDL_CreateTextureFromSurface(renderer, image_pion);
            if (texture_pion == NULL)
                Error("Chargement de la texture_pion échoué !");

            // Définir un rectangle pour l'emplacement et la taille de l'image
            SDL_Rect rect_pion = {x + 5, y + 3, 85, 85};
            // Dessiner la texture dans le rendue
            SDL_RenderCopy(renderer, texture_pion, NULL, &rect_pion);
        }
        else if (team == 2)
        {
            // Récupération de l'image
            image_pion = IMG_Load("Pictures/Black_Border.png");
            if (image_pion == NULL)
                Error("Récupération de l'image_pion échoué !");

            // Créer la texture avec l'image
            texture_pion = SDL_CreateTextureFromSurface(renderer, image_pion);
            if (texture_pion == NULL)
                Error("Chargement de la texture_pion échoué !");

            // Définir un rectangle pour l'emplacement et la taille de l'image
            SDL_Rect rect_pion = {x + 5, y + 3, 85, 85};
            // Dessiner la texture dans le rendue
            SDL_RenderCopy(renderer, texture_pion, NULL, &rect_pion);
        }
    }
    else if (mode == UwU)
    {
        if (team == 1)
        {
            // Récupération de l'image
            image_pion = IMG_Load("Pictures/White1_Border.png");
            if (image_pion == NULL)
                Error("Récupération de l'image_pion échoué !");

            // Créer la texture avec l'image
            texture_pion = SDL_CreateTextureFromSurface(renderer, image_pion);
            if (texture_pion == NULL)
                Error("Chargement de la texture_pion échoué !");

            // Définir un rect c dcfv cv vcangle pour l'emplacement et la taille de l'image
            SDL_Rect rect_pion = {x + 5, y + 3, 85, 85};
            // Dessiner la texture dans le rendue
            SDL_RenderCopy(renderer, texture_pion, NULL, &rect_pion);
        }
        else if (team == 2)
        {
            // Récupération de l'image
            image_pion = IMG_Load("Pictures/Black1_Border.png");
            if (image_pion == NULL)
                Error("Récupération de l'image_pion échoué !");

            // Créer la texture avec l'image
            texture_pion = SDL_CreateTextureFromSurface(renderer, image_pion);
            if (texture_pion == NULL)
                Error("Chargement de la texture_poin échoué !");

            // Définir un rectangle pour l'emplacement et la taille de l'image
            SDL_Rect rect_pion = {x + 5, y + 3, 85, 85};
            // Dessiner la texture dans le rendue
            SDL_RenderCopy(renderer, texture_pion, NULL, &rect_pion);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////EN COURS
void run()
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    SDL_Surface *image_BG = NULL;
    SDL_Texture *texture_BG = NULL;
    SDL_Surface *image_base = NULL;
    SDL_Texture *texture_base = NULL;
    SDL_Surface *image_pion = NULL;
    SDL_Texture *texture_pion = NULL;
    SDL_Surface *image_mode = NULL;
    SDL_Texture *texture_mode = NULL;

    SDL_Event e;
    cell **matrice_Othello;

    int mode = 0;
    int i, j, team = BLANC, cnt_b = 0, cnt_w = 0;
    int key_press_alt = SDL_FALSE;
    int key_press_ctrl = SDL_FALSE;

    ////////////////////////////////////////////////////////// INITIALISATION DE L'INTERFACE GRAPHIQUE //////////////////////////////////////////////////////////
    init_package();
    // Création de la fenêtre
    window = SDL_CreateWindow("Othello", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_FULLSCREEN);
    if (window == NULL)
        Error("Création fenêtre échouée !");
    // Creation du rendue
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
        Error("Création du rendu échoué !");

    SDL_DestroyTexture(texture_BG);
    SDL_DestroyTexture(texture_mode);
    SDL_DestroyTexture(texture_base);
    SDL_FreeSurface(image_BG);
    SDL_FreeSurface(image_mode);
    SDL_FreeSurface(image_base);
    SDL_RenderClear(renderer);

    points **mat_rect_Othello = Cree_mat();
    matrice_Othello = initializeBoard();
    list *head = newList(matrice_Othello);
    Affiche_Othello(window, renderer, image_BG, texture_BG, image_base, texture_base, image_mode, texture_mode, mode);
    Place_pion(window, renderer, image_pion, texture_pion,
               matrice_Othello, mat_rect_Othello, mode);
    show_valid(matrice_Othello, team);
    Place_pion_border(window, renderer,
                      image_pion, texture_pion,
                      matrice_Othello, mat_rect_Othello,
                      team, mode);
    SDL_RenderPresent(renderer);

    //////////////////////////////////////////////////////////
    //-------------------------------------------------------
    /* || Code after init : Event Code  || */
    SDL_bool quit = SDL_FALSE;
    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type != 1024)
            {
                // printf("%d\n", e.type);
                switch (e.type)
                {
                case SDL_MOUSEBUTTONDOWN: // Click de souris
                    get_coord(mat_rect_Othello, &i, &j);
                    if (is_valid(matrice_Othello, i, j, team))
                    {

                        if ((0 <= i && i <= 7) && (0 <= j && j <= 7))
                        {
                            printf("i : %d - j : %d -__- team : %d\n", i, j, team);

                            fill(matrice_Othello, i, j, team);
                            push(&head, matrice_Othello);

                            count_score(matrice_Othello, &cnt_w, &cnt_b);
                            printf("White Team Score : %d\t Black Team Score : %d\n", cnt_w, cnt_b);

                            printBoard(matrice_Othello);
                            SDL_RenderClear(renderer);

                            Affiche_Othello(window, renderer,
                                            image_BG, texture_BG,
                                            image_base, texture_base,
                                            image_mode, texture_mode, mode);
                            Place_pion(window, renderer,
                                       image_pion, texture_pion,
                                       matrice_Othello, mat_rect_Othello, mode);

                            if (team == BLANC)
                                team = NOIR;
                            else
                                team = BLANC;

                            reset_valid(matrice_Othello);
                            show_valid(matrice_Othello, team);
                            Place_pion_border(window, renderer,
                                              image_pion, texture_pion,
                                              matrice_Othello, mat_rect_Othello,
                                              team, mode);
                            SDL_RenderPresent(renderer);
                        }
                    }
                    break;

                case SDL_KEYDOWN: // Touche pressée
                    switch (e.key.keysym.sym)
                    {
                    case SDLK_q:
                        quit = SDL_TRUE;
                        break;
                    case SDLK_z:
                        if (key_press_ctrl == SDL_TRUE)
                        {
                            printf("CTRL_Z\n");
                            if (check_next(&head) == 1)
                            {
                                go_back(&head);
                                display_linked_list(head);
                                copyBoard(matrice_Othello, head->board);
                            }
                        }
                        break;
                    case SDLK_s:
                        if (key_press_ctrl == SDL_TRUE)
                        {
                            // cas de la sauvegarde du plateau dans un fichier txt
                            printf("CTRL_S\n");
                            FILE *f;
                            f = fopen("save.oth", "wb");
                            if (f == NULL)
                            {
                                printf("Ouverture du fichier impossible.(save)\n");
                                exit(1);
                            }
                            for (int i = 0; i < SIZE_OTHELLO; i++)
                            {
                                for (int j = 0; j < SIZE_OTHELLO; j++)
                                {
                                    fwrite(&matrice_Othello[i][j].valide, sizeof(int), 1, f);
                                    fwrite(&matrice_Othello[i][j].color, sizeof(int), 1, f);
                                }
                            }
                            fclose(f);
                        }
                        break;
                    case SDLK_o:
                        // cas de l'ouverture du fichier sauvegarde
                        printf("CTRL_O\n");
                        FILE *f;

                        f = fopen("save.oth", "rb");
                        if (f == NULL)
                        {
                            printf("Ouverture du fichier impossible.(open)\n");
                            exit(1);
                        }
                        for (int i = 0; i < SIZE_OTHELLO; i++)
                        {
                            for (int j = 0; j < SIZE_OTHELLO; j++)
                            {
                                fread(&matrice_Othello[i][j].valide, sizeof(int), 1, f);
                                fread(&matrice_Othello[i][j].color, sizeof(int), 1, f);
                            }
                        }
                        head = newList(matrice_Othello); // On initialise ensuite la liste chainee au nouveau plateau
                        fclose(f);
                        break;

                    case SDLK_LALT: // Touche ALT gauche pressée
                        key_press_alt = SDL_TRUE;
                        break;
                    case SDLK_LCTRL: // Touche CTRL gauche pressée
                        key_press_ctrl = SDL_TRUE;
                        break;
                    }
                    break;

                case SDL_KEYUP: // Touche relachée
                    switch (e.key.keysym.sym)
                    {
                    case SDLK_LALT: // Touche ALT gauche pressée
                        key_press_alt = SDL_FALSE;
                        break;
                    case SDLK_LCTRL: // Touche CTRL gauche pressée
                        key_press_ctrl = SDL_FALSE;
                        break;
                    }
                    break;

                case SDL_QUIT:
                    quit = SDL_TRUE;
                    continue;
                }
            }
        }
    }
    // if (e.type == SDL_TEXTINPUT || e.type == SDL_KEYDOWN)
    //{
    //     ctrl(e, &head, matrice_Othello, "save.txt");
    //     display_linked_list(head);
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

    freeBoard(matrice_Othello);
    free(mat_rect_Othello);
}
