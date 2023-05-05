#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "GUI.h"
#include "GUI_init.h"
#include "control.h"
#include "othello.h"
#include "linked_list.h"
#include "GUI.h"
#include "PVP.h"
#include "PVC.h"

int main(int argc, char *argv[])
{
    srand(time(0));

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    SDL_Event e;

    cell **matrice_Othello;
    list *head;
    points **mat_rect_Othello;
    points *pts_barre;
    points *pts_bouttons;

    int mode = 0, change_amb = 1, menu_barre = 0, tag_val;
    int i, j, IA_p = 0, mouse_x, mouse_y;
    int team = BLANC, cnt_b = 0, cnt_w = 0, win = 0;
    int intro = SDL_TRUE, choix = 0;
    int key_press_ctrl = SDL_FALSE;

    ////////////////////////////////////////////////////////// INITIALISATION DE L'INTERFACE GRAPHIQUE //////////////////////////////////////////////////////////
    TTF_Init();
    Init_package();
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_Chunk *click_sound = Mix_LoadWAV("Sound/placer_pion.wav");
    Mix_Chunk *fin_sound = Mix_LoadWAV("Sound/bravo.wav");
    Mix_Chunk *ambiance_sound = Mix_LoadWAV("Sound/ambiance1.wav");
    Mix_Chunk *ambiance_sound_UwU = Mix_LoadWAV("Sound/ambiance2.wav");
    Mix_Chunk *sus_sound = Mix_LoadWAV("Sound/sus.wav");
    // Creation de la fenetre
    SDL_DisplayMode current;
    SDL_GetCurrentDisplayMode(0, &current);
    window = SDL_CreateWindow("Othello", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, current.w, current.h, SDL_WINDOW_FULLSCREEN /*SDL_WINDOW_SHOWN*/);
    if (window == NULL)
        Error("Creation fenetre echouee !");
    // Creation du rendue
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
        Error("Creation du rendu echoue !");

    mat_rect_Othello = Cree_mat(window);
    matrice_Othello = initializeBoard();
    head = newList(matrice_Othello);

    // Init du graphique de presentation
    BG_image(renderer, mode);
    SDL_RenderClear(renderer);
    BG_image(renderer, mode);                                       // Ccharge l'image de fond
    pts_bouttons = Intro_bouttons(window, renderer);                // charge les bouttons
    pts_barre = Barre_txt(window, renderer);                        // charge la menu barre
    Aff_interaction_barre(window, renderer, pts_barre, menu_barre); // Charge les extentions de la menu barre
    SDL_RenderPresent(renderer);

    // Jouer la musique d'ambiance
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
            // Mix_HaltChannel(0);
            Mix_PlayChannel(0, ambiance_sound_UwU, -1);
            Mix_PlayChannel(-1, sus_sound, 0);
        }
        if (isEndGame(matrice_Othello) && win == 0)
        { // FIN de partie
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
                       matrice_Othello, mat_rect_Othello, pts_barre,
                       cnt_w, cnt_b, win, team, mode, menu_barre);
            Mix_PlayChannel(1, fin_sound, 0);
        }
        while (SDL_PollEvent(&e))
        {
            if (intro == SDL_TRUE)
            { // Page d'intro / choix de jeu
                switch (e.type)
                {
                case SDL_MOUSEBUTTONDOWN: // Click de souris
                    SDL_GetMouseState(&mouse_x, &mouse_y);
                    tag_val = menu_barre;
                    // printf("x : %d\ty : %d\n", mouse_x, mouse_y);

                    /////////////////// L'utilisateur interagie avec la menu barre ///////////////////
                    e = interaction_barre(window, renderer, pts_barre, &menu_barre);
                    if (menu_barre != tag_val)
                    {
                        printf("barre : %d\n", menu_barre);
                        SDL_RenderClear(renderer);
                        BG_image(renderer, mode);                                       // Ccharge l'image de fond
                        pts_bouttons = Intro_bouttons(window, renderer);                // charge les bouttons
                        pts_barre = Barre_txt(window, renderer);                        // charge la menu barre
                        Aff_interaction_barre(window, renderer, pts_barre, menu_barre); // Charge les extentions de la menu barre
                        SDL_RenderPresent(renderer);
                    }

                    // Clic dans le premier boutton : VS joueurs
                    if ((pts_bouttons[0].x1 < mouse_x && mouse_x < pts_bouttons[0].x2) &&
                        (pts_bouttons[0].y1 < mouse_y && mouse_y < pts_bouttons[0].y2))
                    {
                        intro = SDL_FALSE;
                        choix = 1;
                    }
                    // Clic dans le premier boutton : VS IA
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
                    mode = 1;
                    DisplayAll(window, renderer,
                               matrice_Othello, mat_rect_Othello, pts_barre,
                               cnt_w, cnt_b, win, team, mode, menu_barre);
                }
            }
            else if (intro == SDL_FALSE)
            { // Page de jeux
                if (e.type != 1024)
                {
                    switch (e.type)
                    {
                    case SDL_MOUSEBUTTONDOWN:
                        // SDL_GetMouseState(&mouse_x, &mouse_y);
                        // printf("x : %d\ty : %d\n", mouse_x, mouse_y);
                        tag_val = menu_barre;

                        /////////////////// L'utilisateur interagie avec la menu barre ///////////////////
                        e = interaction_barre(window, renderer, pts_barre, &menu_barre);
                        if (menu_barre != tag_val)
                        {
                            printf("barre : %d\n", menu_barre);
                            DisplayAll(window, renderer,
                                       matrice_Othello, mat_rect_Othello, pts_barre,
                                       cnt_w, cnt_b, win, team, mode, menu_barre);
                        }

                        /////////////////// L'utilisateur selectionne une case ///////////////////
                        // Click de souris placement des pions sur les cases disponibles
                        get_coord(mat_rect_Othello, &i, &j);
                        if (show_valid(matrice_Othello, team) > 0)
                        {
                            if ((is_valid(matrice_Othello, i, j, team)))
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
                                           matrice_Othello, mat_rect_Othello, pts_barre,
                                           cnt_w, cnt_b, win, team, mode, menu_barre);

                                ////////////////////////////////////// VS IA //////////////////////////////////////
                                if (choix == 2)
                                {
                                    reset_valid(matrice_Othello);
                                    IA_p = hard_mode(matrice_Othello, team);
                                    push(&head, matrice_Othello);
                                    // printBoard(matrice_Othello); affiche sur le terminal l'othello

                                    if (IA_p != 0)
                                    {
                                        if (team == BLANC)
                                            team = NOIR;
                                        else
                                            team = BLANC;

                                        Mix_PlayChannel(-1, click_sound, 0);
                                        DisplayAll(window, renderer,
                                                   matrice_Othello, mat_rect_Othello, pts_barre,
                                                   cnt_w, cnt_b, win, team, mode, menu_barre);
                                    }
                                }
                                ////////////////////////////////////// VS IA //////////////////////////////////////
                            }
                        }
                        if (show_valid(matrice_Othello, team) == 0)
                        { // Passage de tour
                            if (team == BLANC)
                                team = NOIR;
                            else
                                team = BLANC;
                            DisplayAll(window, renderer,
                                       matrice_Othello, mat_rect_Othello, pts_barre,
                                       cnt_w, cnt_b, win, team, mode, menu_barre);
                        }
                        break;

                    default:
                        break;
                    }
                }
            }

            switch (e.type)
            { // Touche pressee
            case SDL_QUIT:
                // L'utilisateur ferme la fenetre
                quit = SDL_TRUE;
                continue;

            case SDL_KEYDOWN:
                switch (e.key.keysym.sym)
                {
                case SDLK_q:
                    quit = SDL_TRUE;
                    continue;
                case SDLK_n:
                    // Retourne a la selection du mode de jeu
                    if (key_press_ctrl == SDL_TRUE && menu_barre == -1 && intro == SDL_FALSE)
                    { // L'utilisateur fait un CTRL - N
                        freeBoard(matrice_Othello);
                        free_linked_list(head);
                        matrice_Othello = initializeBoard();
                        head = newList(matrice_Othello);
                        team = BLANC;

                        intro = SDL_TRUE;
                        mode = 0;
                        SDL_RenderClear(renderer);
                        BG_image(renderer, mode);
                        pts_bouttons = Intro_bouttons(window, renderer);
                        SDL_RenderPresent(renderer);
                    }
                    break;
                case SDLK_r:
                    // Retourne a la selection du mode de jeu
                    if (key_press_ctrl == SDL_TRUE && menu_barre == -1 && intro == SDL_FALSE)
                    { // L'utilisateur fait un CTRL - R
                        freeBoard(matrice_Othello);
                        free_linked_list(head);
                        matrice_Othello = initializeBoard();
                        head = newList(matrice_Othello);
                        team = BLANC;

                        DisplayAll(window, renderer,
                                   matrice_Othello, mat_rect_Othello, pts_barre,
                                   cnt_w, cnt_b, win, team, mode, menu_barre);
                    }
                    break;
                case SDLK_z:
                    if (key_press_ctrl == SDL_TRUE && menu_barre == -1 && intro == SDL_FALSE)
                    { // L'utilisateur fait un CTRL - Z
                        if (check_next(&head) == 1)
                        {
                            if (choix == 1)
                            { // Version joueur vs joueur
                                go_back(&head);
                                display_linked_list(head);
                                backBoard(matrice_Othello, head->board);

                                if (team == BLANC)
                                    team = NOIR;
                                else
                                    team = BLANC;
                            }
                            else if (choix == 2)
                            { // Version joueur vs IA
                                for (int i = 2; i > 0; i--)
                                {
                                    go_back(&head);
                                    display_linked_list(head);
                                    backBoard(matrice_Othello, head->board);
                                }
                            }
                            DisplayAll(window, renderer,
                                       matrice_Othello, mat_rect_Othello, pts_barre,
                                       cnt_w, cnt_b, win, team, mode, menu_barre);
                        }
                    }
                    break;
                case SDLK_s:
                    if (key_press_ctrl == SDL_TRUE && menu_barre == -1 && intro == SDL_FALSE)
                    { // L'utilisateur fait un CTRL - S
                        // cas de la sauvegarde du plateau dans un fichier txt
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
                    if (key_press_ctrl == SDL_TRUE && menu_barre == -1 && intro == SDL_FALSE)
                    { // L'utilisateur fait un CTRL - O
                        // cas de l'ouverture du fichier sauvegarde
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
                        DisplayAll(window, renderer,
                                   matrice_Othello, mat_rect_Othello, pts_barre,
                                   cnt_w, cnt_b, win, team, mode, menu_barre);
                    }
                    break;

                case SDLK_LCTRL: // Touche CTRL gauche pressee
                    key_press_ctrl = SDL_TRUE;
                    break;
                }
                break;

            case SDL_KEYUP: // Touche relachee
                switch (e.key.keysym.sym)
                {
                case SDLK_LCTRL: // Touche CTRL gauche pressee
                    key_press_ctrl = SDL_FALSE;
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }
            SDL_RenderClear(renderer);
        }
    }
    //-----------Desttruction des variables pointeurs-----------//
    SDL_RenderClear(renderer);

    /* Deinit Audio */
    Mix_HaltChannel(0);
    Mix_HaltChannel(1);
    Mix_HaltChannel(2);
    Mix_FreeChunk(ambiance_sound_UwU);
    Mix_FreeChunk(ambiance_sound);
    Mix_FreeChunk(click_sound);
    Mix_FreeChunk(fin_sound);
    Mix_CloseAudio();

    /* denit pointeurs */
    free(pts_barre);
    free(pts_bouttons);
    freeBoard(matrice_Othello);
    freeMat(mat_rect_Othello);
    free_linked_list(head);

    /* denit renderer */
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    /* denit fenetres */
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();

    // float final_array[15] = {AUX_VALUE, AUX_VALUE, AUX_VALUE, AUX_VALUE, AUX_VALUE, AUX_VALUE, AUX_VALUE, -1, 3, 5, 1, -6, -4, 0, 9};
    // tree *root = insertInTree(final_array, 0, 15);
    // minimax(root, height(root), MAX_EVAL, MIN_EVAL, BLANC);
    // printTree(root);

    // cell **board = initializeBoard();
    // board[7][0].color = BLANC;
    // board[7][1].color = BLANC;
    // board[7][2].color = BLANC;
    // board[7][4].color = NOIR;
    // board[7][5].color = NOIR;
    // board[7][6].color = NOIR;
    // board[7][7].color = NOIR;


    // hard_mode(board, NOIR);

    return EXIT_SUCCESS;
}