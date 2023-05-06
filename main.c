#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "GUI.h"
#include "GUI_init.h"
#include "control.h"
#include "othello.h"
#include "linked_list.h"
#include "GUI.h"
#include "PVC.h"

int main(int argc, char *argv[])
{
    srand(time(0));

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    SDL_Event e;

    cell **matrice_Othello;
    list *head;
    cell ***memory_z = malloc(sizeof(cell *) * 10);
    points **mat_rect_Othello;
    points *pts_barre;
    points *pts_bouttons;

    int mode = 0, menu_barre = -1, tag_val, tag_sound = 1;
    int i, j, IA_p = 0, mouse_x, mouse_y;
    int ctrl_z = 0;
    int team = BLANC, cnt_b = 0, cnt_w = 0, win = 0;
    int intro = SDL_TRUE, choix = 0;
    int key_press_ctrl = SDL_FALSE;
    int key_press_shift = SDL_FALSE;

    ////////////////////////////////////////////////////////// INITIALISATION DE L'INTERFACE GRAPHIQUE //////////////////////////////////////////////////////////
    TTF_Init();
    Init_package();
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_Chunk *click_sound = Mix_LoadWAV("Sound/placer_pion.wav");
    Mix_Chunk *fin_sound = Mix_LoadWAV("Sound/bravo.wav");
    Mix_Chunk *ambiance_sound = Mix_LoadWAV("Sound/ambiance1.wav");
    Mix_Chunk *ambiance_sound_UwU = Mix_LoadWAV("Sound/ambiance2.wav");
    Mix_Chunk *ambiance_sound_Elden_Ring = Mix_LoadWAV("Sound/ambiance3.wav");
    // Mix_Chunk *sus_sound = Mix_LoadWAV("Sound/sus.wav");
    // Creation de la fenetre
    SDL_DisplayMode current;
    SDL_GetCurrentDisplayMode(0, &current);
    window = SDL_CreateWindow("Othello", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, current.w, current.h, SDL_WINDOW_SHOWN);
    if (window == NULL)
        Error("Creation fenetre echouee !");
    // Creation du rendue
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
        Error("Creation du rendu echoue !");

    mat_rect_Othello = Cree_mat(window);
    matrice_Othello = initializeBoard();
    head = newList(matrice_Othello);

    // Init de l'affichage de presentation
    SDL_RenderClear(renderer);
    BG_image(renderer, mode);                                       // Charge l'image de fond
    pts_bouttons = Intro_bouttons(window, renderer);                // Charge les bouttons
    pts_barre = Barre_txt(window, renderer);                        // Charge la barre de menu
    Aff_interaction_barre(window, renderer, pts_barre, menu_barre); // Charge les extentions de la barre de menu
    SDL_RenderPresent(renderer);

    // Jouer la musique d'ambiance
    Mix_PlayChannel(0, ambiance_sound, -1);
    Mix_Volume(0, MIX_MAX_VOLUME * 0.1);
    Mix_Volume(1, MIX_MAX_VOLUME * 0.1);
    //////////////////////////////////////////////////////////
    //-------------------------------------------------------

    SDL_bool quit = SDL_FALSE;
    while (!quit)
    {
        if (menu_barre == -4) // MUSIQUE ON/OFF----------------------------------------
        {
            if (tag_sound == 1)
            {
                Mix_HaltChannel(0); // Stopper la musique en cours
                tag_sound = 0;
            }
            else
            {
                if (mode == 1)
                    Mix_PlayChannel(0, ambiance_sound, -1); // Relancer la musique mode 1
                else if (mode == 2)
                    Mix_PlayChannel(0, ambiance_sound_Elden_Ring, -1); // Relancer la musique mode 2
                else if (mode == 3)
                    Mix_PlayChannel(0, ambiance_sound_UwU, -1); // Relancer la musique mode 3
                tag_sound = 1;
            }
            menu_barre = -1;
        }
        else if (menu_barre == -5) // MODIFICATION DE LA FENETRE ----------------------------------------
        {
            // Remise a 0 des parametres graphiques
            freeMat(mat_rect_Othello);
            mat_rect_Othello = NULL;
            pts_barre = NULL;
            // Recreation des parametres graphique avec la nouvelle dimention
            mat_rect_Othello = Cree_mat(window); // Charge la grille
            // Reaffichage avec les nouveaux parametres graphiques
            if (intro == SDL_TRUE) // si on est dans l'intro
            {
                // Init de l'affichage de presentation
                SDL_RenderClear(renderer);
                BG_image(renderer, mode);                        // Ccharge l'image de fond
                pts_bouttons = Intro_bouttons(window, renderer); // Charge les bouttons
                pts_barre = Barre_txt(window, renderer);         // Charge la barre de menu
                SDL_RenderPresent(renderer);
            }
            else // sinon si on est en jeu
                DisplayAll(window, renderer,
                           matrice_Othello, mat_rect_Othello, pts_barre,
                           cnt_w, cnt_b, win, team, mode, menu_barre);

            menu_barre = -1;
        }
        else if (menu_barre == -8 && intro == SDL_FALSE) // MODE SELECTIONNE : 2 ----------------------------------------
        {
            mode = 2;
            Mix_PlayChannel(0, ambiance_sound_Elden_Ring, -1);
            DisplayAll(window, renderer,
                       matrice_Othello, mat_rect_Othello, pts_barre,
                       cnt_w, cnt_b, win, team, mode, menu_barre);
            menu_barre = -1;
        }
        else if (menu_barre == -9 && intro == SDL_FALSE) // MODE SELECTIONNE : 3 ----------------------------------------
        {
            mode = 3;
            Mix_PlayChannel(0, ambiance_sound_UwU, -1);
            // Mix_PlayChannel(-1, sus_sound, 0); // Pour rigoler un peu
            DisplayAll(window, renderer,
                       matrice_Othello, mat_rect_Othello, pts_barre,
                       cnt_w, cnt_b, win, team, mode, menu_barre);
            menu_barre = -1;
        }

        if (isEndGame(matrice_Othello) && win == 0) // FIN DE PARTIE ----------------------------------------
        {
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
                case SDL_MOUSEBUTTONDOWN: // Clic de souris
                    SDL_GetMouseState(&mouse_x, &mouse_y);
                    tag_val = menu_barre;
                    // printf("x : %d\ty : %d\n", mouse_x, mouse_y);

                    /////////////////// L'utilisateur interagit avec la barre de menu ///////////////////
                    interaction_barre(window, renderer, &e, pts_barre, &menu_barre);
                    // printf("\t%d\t%d\n",e.type == SDL_KEYDOWN, e.key.keysym.sym == SDLK_n);
                    printf("menu_barre = %d\n", menu_barre);
                    if (menu_barre != tag_val)
                    {
                        SDL_RenderClear(renderer);
                        BG_image(renderer, mode);                                       // Charge l'image de fond
                        pts_bouttons = Intro_bouttons(window, renderer);                // Charge les bouttons
                        pts_barre = Barre_txt(window, renderer);                        // Charge la barre de menu
                        Aff_interaction_barre(window, renderer, pts_barre, menu_barre); // Charge les extentions de la barre de menu
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
            { // Page de jeu

                if (e.type != 1024)
                {
                    switch (e.type)
                    {
                    case SDL_MOUSEBUTTONDOWN:

                        // SDL_GetMouseState(&mouse_x, &mouse_y);
                        // printf("x : %d\ty : %d\n", mouse_x, mouse_y);
                        tag_val = menu_barre;

                        /////////////////// L'utilisateur interagie avec la menu barre ///////////////////
                        interaction_barre(window, renderer, &e, pts_barre, &menu_barre);

                        if (menu_barre != tag_val)
                            DisplayAll(window, renderer,
                                       matrice_Othello, mat_rect_Othello, pts_barre,
                                       cnt_w, cnt_b, win, team, mode, menu_barre);

                        /////////////////// L'utilisateur selectionne une case ///////////////////
                        // Clic de souris placement des pions sur les cases disponibles
                        // printf("i : %d\tj : %d",i,j);
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
                                    IA_p = easy_mode(matrice_Othello, team);
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
                    if ((key_press_ctrl == SDL_TRUE || menu_barre == -2) && intro == SDL_FALSE)
                    { // L'utilisateur fait un CTRL - N
                        freeBoard(matrice_Othello);
                        free_linked_list(head);
                        matrice_Othello = initializeBoard();
                        head = newList(matrice_Othello);
                        team = BLANC;
                        intro = SDL_TRUE;
                        mode = 0;

                        // Init de l'affichage de presentation
                        SDL_RenderClear(renderer);
                        BG_image(renderer, mode);                                       // Charge l'image de fond
                        pts_bouttons = Intro_bouttons(window, renderer);                // Charge les bouttons
                        pts_barre = Barre_txt(window, renderer);                        // Charge la barre de menu
                        Aff_interaction_barre(window, renderer, pts_barre, menu_barre); // Charge les extensions de la barre de menu
                        SDL_RenderPresent(renderer);
                    }
                    break;
                case SDLK_r:
                    // Retourne a la selection du mode de jeu
                    if ((key_press_ctrl == SDL_TRUE || menu_barre == -2) && intro == SDL_FALSE)
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
                    if ((key_press_ctrl == SDL_TRUE || menu_barre == -6) && intro == SDL_FALSE)
                    { // L'utilisateur fait un CTRL - Z
                        if (check_next(&head) == 1)
                        {
                            ctrl_z++;
                            if (ctrl_z < 11)
                                memory_z[ctrl_z - 1] = matrice_Othello;
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
                    if ((key_press_ctrl == SDL_TRUE || menu_barre == -2) && intro == SDL_FALSE)
                    { // L'utilisateur fait un CTRL - S
                        // cas de la sauvegarde du plateau dans un fichier txt
                        FILE *f;
                        f = fopen("Saves/save.oth", "wb");
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
                    if (((key_press_ctrl == SDL_TRUE && key_press_shift == SDL_TRUE) || menu_barre == -3) && intro == SDL_FALSE)
                    { // L'utilisateur fait un CTRL - MAJ - S
                        // cas de la sauvegarde du plateau dans un fichier txt
                        FILE *f;
                        char *name_file;
                        demande_fichier(&name_file); //////////////////////// ICI OUVERTURE DE FENETRE, FERMETURE BUG... ////////////////////////----------------------
                        ajout_extension(&name_file, ".oth");
                        printf("fichier : %s", name_file);
                        f = fopen(name_file, "wb");

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
                        DisplayAll(window, renderer,
                                   matrice_Othello, mat_rect_Othello, pts_barre,
                                   cnt_w, cnt_b, win, team, mode, menu_barre);
                    }
                    break;
                case SDLK_o:
                    if ((key_press_ctrl == SDL_TRUE || menu_barre == -2) && intro == SDL_FALSE)
                    { // L'utilisateur fait un CTRL - O
                        // cas de l'ouverture du fichier sauvegarde
                        FILE *f;

                        f = fopen("Saves/save.oth", "rb");
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
                case SDLK_LSHIFT: // Touche MAJ gauche pressee
                    key_press_shift = SDL_TRUE;
                    break;
                }
                break;

            case SDL_KEYUP: // Touche relachee
                switch (e.key.keysym.sym)
                {
                case SDLK_LCTRL: // Touche CTRL gauche pressee
                    key_press_ctrl = SDL_FALSE;
                    break;
                case SDLK_LSHIFT: // Touche MAJ gauche pressee
                    key_press_shift = SDL_FALSE;
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
    //-----------Destruction des variables pointeurs-----------//
    SDL_RenderClear(renderer);

    /* Deinitialisation Audio */
    Mix_HaltChannel(0);
    Mix_HaltChannel(1);
    Mix_HaltChannel(2);
    Mix_FreeChunk(ambiance_sound_UwU);
    Mix_FreeChunk(ambiance_sound);
    Mix_FreeChunk(click_sound);
    Mix_FreeChunk(fin_sound);
    Mix_CloseAudio();

    /* Deinitialisation pointeurs */
    free(pts_barre);
    free(pts_bouttons);
    freeBoard(matrice_Othello);
    freeMat(mat_rect_Othello);
    free_linked_list(head);

    /* Deinitialisation renderer */
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    /* Deinitialisation fenetres */
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}