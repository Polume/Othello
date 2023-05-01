#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "GUI_init.h"
#include "othello.h"
#include "linked_list.h"
#include "GUI.h"
#include "PVP.h"
#include "PVC.h"

int main(int argc, char *argv[])
{
    srand(time(0));

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    SDL_Surface* image_intro = NULL;
    SDL_Texture* texture_intro = NULL;
    SDL_Surface* image_bouttons = NULL;
    SDL_Texture* texture_bouttons = NULL;
    SDL_Surface* image_BG = NULL;
    SDL_Texture* texture_BG = NULL;
    SDL_Surface* image_base = NULL;
    SDL_Texture* texture_base = NULL;
    SDL_Surface* image_pion = NULL;
    SDL_Texture* texture_pion = NULL;
    SDL_Surface* image_mode = NULL;
    SDL_Texture* texture_mode = NULL;
    SDL_Texture* texture_txt = NULL;

    SDL_Surface* surface_barre_txt = NULL;
    
    SDL_Event e;

    cell** matrice_Othello;
    points* pts_bouttons;

    int mode = 0, change_amb = 1;
    int i, j, IA_p=0, mouse_x, mouse_y, team = BLANC, cnt_b = 0, cnt_w = 0, win = 0;
    int intro = SDL_TRUE, choix = 0;
    int key_press_ctrl = SDL_FALSE;

    ////////////////////////////////////////////////////////// INITIALISATION DE L'INTERFACE GRAPHIQUE //////////////////////////////////////////////////////////
    TTF_Init();
    init_package();
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_Chunk* click_sound = Mix_LoadWAV("Sound/placer_pion.wav");
    Mix_Chunk* fin_sound = Mix_LoadWAV("Sound/bravo.wav");
    Mix_Chunk* ambiance_sound = Mix_LoadWAV("Sound/ambiance1.wav");
    Mix_Chunk* ambiance_sound_UwU = Mix_LoadWAV("Sound/ambiance2.wav");
    Mix_Chunk* sus_sound = Mix_LoadWAV("Sound/sus.wav");
    // Création de la fenêtre
    SDL_DisplayMode current;
    SDL_GetCurrentDisplayMode(0, &current);
    window = SDL_CreateWindow("Othello", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, current.w, current.h, SDL_WINDOW_FULLSCREEN /*SDL_WINDOW_SHOWN*/);
    if (window == NULL)
        Error("Création fenêtre échouée !");
    // Creation du rendue
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
        Error("Création du rendu échoué !");
    partie ecran100 = slice_screen_100(get_screen_size(window).w, get_screen_size(window).h);
    TTF_Font* font = TTF_OpenFont("arial.ttf", (int)(ecran100.h * 4.7));

    points** mat_rect_Othello = Cree_mat(window);
    matrice_Othello = initializeBoard();
    list* head = newList(matrice_Othello);

    init_BG_image(renderer, image_intro, texture_intro, mode);
    pts_bouttons = init_bouttons(window, renderer, image_bouttons, texture_bouttons);

    //EN COUR
    //barre_txt(window, renderer, surface_barre_txt, texture_txt, font);

    SDL_RenderPresent(renderer);
    //Jouer la musique d'ambiance
    Mix_PlayChannel(0, ambiance_sound, -1);
    Mix_Volume(0, MIX_MAX_VOLUME * 0.1);
    Mix_Volume(1, MIX_MAX_VOLUME * 0.1);
    //////////////////////////////////////////////////////////
    //-------------------------------------------------------
    /* || Code after init : Event Code  || */
    SDL_bool quit = SDL_FALSE;
    while (!quit)
    {
        if (mode == 2 && change_amb == 1)
        {
            change_amb = 0;
            //Mix_HaltChannel(0);
            Mix_PlayChannel(0, ambiance_sound_UwU, -1);
            Mix_PlayChannel(-1, sus_sound, 0);
        }
        if (isEndGame(matrice_Othello) && win == 0)
        {// FIN de partie
            count_score(matrice_Othello, &cnt_w, &cnt_b);
            if (cnt_w > cnt_b)
            {
                win = 1;
            }
            else if (cnt_b > cnt_w)
            {
                win = 2;
            }
            else if (cnt_w == cnt_b)
            {
                win = 3;
            }
            DisplayAll(window, renderer,
                image_BG, texture_BG, image_base, texture_base,
                image_mode, texture_mode, image_pion, texture_pion,
                texture_txt, font, matrice_Othello, mat_rect_Othello,
                cnt_w, cnt_b, win, team, mode);
            Mix_PlayChannel(1, fin_sound, 0);
        }
        while (SDL_PollEvent(&e))
        {
            if (intro == SDL_TRUE)
            {// Page d'intro / choix de jeu      
                switch (e.type)
                {
                case SDL_MOUSEBUTTONDOWN: // Click de souris
                    SDL_GetMouseState(&mouse_x, &mouse_y);
                    //Clic dans le premier boutton : VS joueurs
                    if ((pts_bouttons[0].x1 < mouse_x && mouse_x < pts_bouttons[0].x2) &&
                        (pts_bouttons[0].y1 < mouse_y && mouse_y < pts_bouttons[0].y2))
                    {
                        intro = SDL_FALSE;
                        choix = 1;
                    }
                    //Clic dans le premier boutton : VS IA
                    else if ((pts_bouttons[1].x1 < mouse_x && mouse_x < pts_bouttons[1].x2) &&
                        (pts_bouttons[1].y1 < mouse_y && mouse_y < pts_bouttons[1].y2))
                    {
                        intro = SDL_FALSE;
                        choix = 2;
                    }
                    break;
                default:
                    break;
                }

                if (intro == SDL_FALSE)
                {
                    mode = 2;
                    DisplayAll(window, renderer,
                        image_BG, texture_BG, image_base, texture_base,
                        image_mode, texture_mode, image_pion, texture_pion,
                        texture_txt, font, matrice_Othello, mat_rect_Othello,
                        cnt_w, cnt_b, win, team, mode);
                }
            }
            else if (intro == SDL_FALSE)
            {// Page de jeux
                if (e.type != 1024)
                {
                    switch (e.type)
                    {
                    case SDL_MOUSEBUTTONDOWN: // Click de souris placement des pions sur les cases disponibles
                        get_coord(mat_rect_Othello, &i, &j);
                        if (show_valid(matrice_Othello, team) > 0)
                        {
                            if ((0 <= i && i <= 7) && (0 <= j && j <= 7) && (is_valid(matrice_Othello, i, j, team)))
                            {
                                fill(matrice_Othello, i, j, team);
                                push(&head, matrice_Othello);
                                printBoard(matrice_Othello);

                                if (team == BLANC)
                                    team = NOIR;
                                else
                                    team = BLANC;

                                Mix_PlayChannel(-1, click_sound, 0);
                                DisplayAll(window, renderer,
                                    image_BG, texture_BG, image_base, texture_base,
                                    image_mode, texture_mode, image_pion, texture_pion,
                                    texture_txt, font, matrice_Othello, mat_rect_Othello,
                                    cnt_w, cnt_b, win, team, mode);

                                printf("\njoueur1 : %d\n\n", team);
                                ////////////////////////////////////// VS IA //////////////////////////////////////
                                if (choix == 2)
                                {
                                    reset_valid(matrice_Othello);
                                    IA_p = easy_mode(matrice_Othello, team);
                                    push(&head, matrice_Othello);
                                    printBoard(matrice_Othello);

                                    if (IA_p != 0)
                                    {
                                        if (team == BLANC)
                                            team = NOIR;
                                        else
                                            team = BLANC;

                                        printf("\njoueur2 : %d\n\n", team);
                                        DisplayAll(window, renderer,
                                            image_BG, texture_BG, image_base, texture_base,
                                            image_mode, texture_mode, image_pion, texture_pion,
                                            texture_txt, font, matrice_Othello, mat_rect_Othello,
                                            cnt_w, cnt_b, win, team, mode);
                                    }
                                }
                                ////////////////////////////////////// VS IA //////////////////////////////////////
                            }                           
                        }
                        if (show_valid(matrice_Othello, team) == 0)
                        {
                            if (team == BLANC)
                                team = NOIR;
                            else
                                team = BLANC;
                            DisplayAll(window, renderer,
                                image_BG, texture_BG, image_base, texture_base,
                                image_mode, texture_mode, image_pion, texture_pion,
                                texture_txt, font, matrice_Othello, mat_rect_Othello,
                                cnt_w, cnt_b, win, team, mode);

                        }
                        break;

                    default:
                        break;
                    }
                }
            }

            switch (e.type)
            {// Touche pressée

            case SDL_QUIT:
                quit = SDL_TRUE;
                continue;

            case SDL_KEYDOWN: 
                switch (e.key.keysym.sym)
                {
                case SDLK_q:
                    quit = SDL_TRUE;
                    continue;
                case SDLK_n:
                    // Retourne a la séléction du mode de jeu
                    if (key_press_ctrl == SDL_TRUE)
                    {
                        freeBoard(matrice_Othello);
                        free_linked_list(head);
                        matrice_Othello = initializeBoard();
                        head = newList(matrice_Othello);
                        team = BLANC;

                        intro = SDL_TRUE;
                        mode = 0;
                        DisplayAll_clear(window, renderer, image_BG, texture_BG, image_base, texture_base, image_mode, texture_mode, image_pion, texture_pion, texture_txt);
                        init_BG_image(renderer, image_intro, texture_intro, mode);
                        pts_bouttons = init_bouttons(window, renderer, image_bouttons, texture_bouttons);
                        SDL_RenderPresent(renderer);
                    }
                    break;
                case SDLK_z:
                    if (key_press_ctrl == SDL_TRUE)
                    {// Effectue un retour en arrière
                        //printf("CTRL_Z\n");
                        if (check_next(&head) == 1)
                        {
                            DisplayAll_clear(window, renderer, image_BG, texture_BG, image_base, texture_base, image_mode, texture_mode, image_pion, texture_pion, texture_txt);
                            if (choix == 1)
                            {// Version joueur vs joueur
                                go_back(&head);
                                display_linked_list(head);
                                backBoard(matrice_Othello, head->board);

                                if (team == BLANC)
                                    team = NOIR;
                                else
                                    team = BLANC;
                            }
                            else if (choix == 2)
                            {// Version joueur vs IA
                                for (int i = 2; i > 0; i--)
                                {
                                    go_back(&head);
                                    display_linked_list(head);
                                    backBoard(matrice_Othello, head->board);
                                }
                            }
                            DisplayAll(window, renderer,
                                image_BG, texture_BG, image_base, texture_base,
                                image_mode, texture_mode, image_pion, texture_pion,
                                texture_txt, font, matrice_Othello, mat_rect_Othello,
                                cnt_w, cnt_b, win, team, mode);
                        }
                    }
                    break;
                case SDLK_s:
                    if (key_press_ctrl == SDL_TRUE)
                    {
                        // cas de la sauvegarde du plateau dans un fichier txt
                        printf("CTRL_S\n");
                        FILE* f;
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
                    FILE* f;

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
                    DisplayAll_clear(window, renderer, image_BG, texture_BG, image_base, texture_base, image_mode, texture_mode, image_pion, texture_pion, texture_txt);
                    DisplayAll(window, renderer,
                        image_BG, texture_BG, image_base, texture_base,
                        image_mode, texture_mode, image_pion, texture_pion,
                        texture_txt, font, matrice_Othello, mat_rect_Othello,
                        cnt_w, cnt_b, win, team, mode);
                    break;

                case SDLK_LCTRL: // Touche CTRL gauche pressée
                    key_press_ctrl = SDL_TRUE;
                    break;
                }
                break;

            case SDL_KEYUP: // Touche relachée
                switch (e.key.keysym.sym)
                {
                case SDLK_LCTRL: // Touche CTRL gauche pressée
                    key_press_ctrl = SDL_FALSE;
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }
            DisplayAll_clear(window, renderer, image_BG, texture_BG, image_base, texture_base, image_mode, texture_mode, image_pion, texture_pion, texture_txt);
        }
    }
    printf("sortie\n");
    //-----------Desttruction des variables pointeurs-----------//
    SDL_RenderClear(renderer);
    /* Deinit TTF */
    SDL_DestroyTexture(texture_txt);
    

    /* Deinit Audio */
    Mix_HaltChannel(0);
    Mix_HaltChannel(1);
    Mix_HaltChannel(2);
    Mix_FreeChunk(ambiance_sound_UwU);
    Mix_FreeChunk(ambiance_sound);
    Mix_FreeChunk(click_sound);
    Mix_FreeChunk(fin_sound);
    Mix_CloseAudio();
    Mix_Quit();

    /* denit textures d'images */
    SDL_DestroyTexture(texture_BG);
    SDL_DestroyTexture(texture_mode);
    SDL_DestroyTexture(texture_base);

    /* denit surfaces d'images */
    SDL_FreeSurface(image_BG);
    SDL_FreeSurface(image_mode);
    SDL_FreeSurface(image_base);

    /* denit pointeurs */
    freeBoard(matrice_Othello);
    freeMat(mat_rect_Othello);
    free_linked_list(head);

    /* denit renderer */
    
    TTF_Quit();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return EXIT_SUCCESS;
}