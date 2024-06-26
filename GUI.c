#include "GUI.h"
#include "GUI_init.h"
#include "othello.h"
#include "control.h"

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
/* - - - - - - - - - - - - - Fonctions de dessins - - - - - - - - - - - - -*/
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

void Dessine_pion(SDL_Window *window, SDL_Renderer *renderer, int x, int y, int team, int mode)
{ // dessine un pion la ou l'utilisateur a clique
    partie ecran100 = slice_screen_100(get_screen_size(window).w, get_screen_size(window).h);
    int decalage_x = (int)(0.39 * ecran100.w);
    int decalage_y = (int)(0.27 * ecran100.h);
    // Definir un rectcangle pour l'emplacement et la taille de l'image
    SDL_Rect rect_pion = {x + decalage_x, y + decalage_y, (int)(4.3 * ecran100.w), (int)(8.1 * ecran100.h)};
    char *fichier = NULL;
    switch (mode)
    {
    case 1:
        if (team == 1)
            fichier = "Pictures/White.png";
        else if (team == 2)
            fichier = "Pictures/Black.png";
        break;
    case 2:
        if (team == 1)
            fichier = "Pictures/White2.png";
        else if (team == 2)
            fichier = "Pictures/Black2.png";
        break;
    case 3:
        if (team == 1)
            fichier = "Pictures/White3.png";
        else if (team == 2)
            fichier = "Pictures/Black3.png";
        break;
    default:
        break;
    }

    if (fichier == NULL)
        Error("Recuperation de l'image echoue !");
    Place_image(renderer, &rect_pion, fichier);
}

void Dessine_pion_valid(SDL_Window *window, SDL_Renderer *renderer,
                        int x, int y, int team, int mode)
{ // Permet de placer les endroits possibles ou placer un pion
    partie ecran100 = slice_screen_100(get_screen_size(window).w, get_screen_size(window).h);
    int decalage_x = (int)(0.39 * ecran100.w);
    int decalage_y = (int)(0.27 * ecran100.h);
    // Definir un rectangle pour l'emplacement et la taille de l'image
    SDL_Rect rect_pion = {x + decalage_x, y + decalage_y, (int)(4.3 * ecran100.w), (int)(8.1 * ecran100.h)};
    char *fichier = NULL;
    switch (mode)
    {
    case 1:
        if (team == 1)
            fichier = "Pictures/White_Border.png";
        else if (team == 2)
            fichier = "Pictures/Black_Border.png";
        break;
    case 2:
        if (team == 1)
            fichier = "Pictures/White_Border2.png";
        else if (team == 2)
            fichier = "Pictures/Black_Border2.png";
        break;
    case 3:
        if (team == 1)
            fichier = "Pictures/White_Border3.png";
        else if (team == 2)
            fichier = "Pictures/Black_Border3.png";
        break;
    default:
        break;
    }

    if (fichier == NULL)
        Error("Recuperation de l'image echoue !");
    Place_image(renderer, &rect_pion, fichier);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
/* - - - - - - - - - - - - - Fonctions de placements - - - - - - - - - - - - -*/
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void BG_image(SDL_Renderer *renderer, int mode)
{
    // Recuperation de l'image
    char *fichier = NULL;
    if (mode == 0)
        fichier = "Pictures/Oth.png";
    else if (mode == 1)
        fichier = "Pictures/BG_Othello.png";
    else if (mode == 2)
        fichier = "Pictures/BG_Othello2.png";
    else if (mode == 3)
        fichier = "Pictures/BG_Othello3.png";
    if (fichier == NULL)
        Error("Recuperation de l'image echoue !");

    Place_image(renderer, NULL, fichier);
}

void Base_Othello(SDL_Window *window, SDL_Renderer *renderer, int mode)
{
    // Definir un rectangle pour l'emplacement et la taille de l'image
    partie ecran10 = slice_screen_10(get_screen_size(window).w, get_screen_size(window).h);
    SDL_Rect rect_sides = {(int)(3 * ecran10.w), (int)(1.5 * ecran10.h), (int)(8 * ecran10.h), (int)(8 * ecran10.h)};
    char *fichier = NULL;
    switch (mode)
    {
    case 1:
        fichier = "Pictures/Base_Othello.png";
        break;
    case 2:
        fichier = "Pictures/Base_Othello2.png";
        break;
    case 3:
        fichier = "Pictures/Base_Othello3.png";
        break;
    default:
        break;
    }

    if (fichier == NULL)
        Error("Recuperation de l'image_base echoue !");

    Place_image(renderer, &rect_sides, fichier);
}

void Place_pion(SDL_Window *window, SDL_Renderer *renderer,
                cell **matrice_Othello, points **mat_rect_Othello, int mode)
{ // Permet de placer tout les pions
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            if (matrice_Othello[x][y].color == 1 || matrice_Othello[x][y].color == 2)
            {
                Dessine_pion(window, renderer, mat_rect_Othello[x][y].x1, mat_rect_Othello[x][y].y1, matrice_Othello[x][y].color, mode);
            }
        }
    }
}

void Place_pion_valid(SDL_Window *window, SDL_Renderer *renderer,
                      cell **matrice_Othello, points **mat_rect_Othello, int mode, int team)
{ // Permet de placer tout les pions possibles a la selection
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            if (matrice_Othello[x][y].valide == 1)
            {
                Dessine_pion_valid(window, renderer, mat_rect_Othello[x][y].x1, mat_rect_Othello[x][y].y1, team, mode);
            }
        }
    }
}

points *Intro_bouttons(SDL_Window *window, SDL_Renderer *renderer)
{ // Permet de placer les boutons de la phase d'intro
    // On prepare la variable de retour et le placement
    points *pts_bouttons = malloc(2 * sizeof(points));
    partie ecran10 = slice_screen_10(get_screen_size(window).w, get_screen_size(window).h);
    char *fichier = NULL;

    //////////////// Premier Boutton ////////////////
    fichier = "Pictures/Contre_Joueur.png";
    // Definit Les limites d'emplacement du boutton
    pts_bouttons[0].x1 = (int)(ecran10.w * 2);
    pts_bouttons[0].y1 = (int)(ecran10.h * 5);
    pts_bouttons[0].x2 = (int)((ecran10.w * 2) + (ecran10.w * 2));
    pts_bouttons[0].y2 = (int)((ecran10.h * 5) + (ecran10.h * 2));
    // Definit un rectangle pour l'emplacement et la taille de l'image
    SDL_Rect rect_boutton_Joueurs = {pts_bouttons[0].x1, pts_bouttons[0].y1, (int)(ecran10.w * 2), (int)(ecran10.h * 2)};
    Place_image(renderer, &rect_boutton_Joueurs, fichier);

    //////////////// Second Boutton ////////////////
    fichier = "Pictures/Contre_IA.png";
    // Definit Les limites d'emplacement du boutton
    pts_bouttons[1].x1 = (int)(ecran10.w * 6);
    pts_bouttons[1].y1 = (int)(ecran10.h * 5);
    pts_bouttons[1].x2 = (int)((ecran10.w * 6) + (ecran10.w * 2));
    pts_bouttons[1].y2 = (int)((ecran10.h * 5) + (ecran10.h * 2));
    // Definir un rectangle pour l'emplacement et la taille de l'image
    SDL_Rect rect_boutton_IA = {pts_bouttons[1].x1, pts_bouttons[1].y1, (int)(ecran10.w * 2), (int)(ecran10.h * 2)};
    Place_image(renderer, &rect_boutton_IA, fichier);

    return pts_bouttons;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
/* - - - - - - - - - - - - - Fonction d'imbrication de dessins/affichage - - - - - - - - - - - - - -*/
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

void Interface_txt(SDL_Window *window, SDL_Renderer *renderer,
                   int cnt_w, int cnt_b, int team, int mode, int fin)
{ // ecrit un texte dans un rectangle
    partie ecran10 = slice_screen_10(get_screen_size(window).w, get_screen_size(window).h);
    TTF_Font *font = TTF_OpenFont("arial.ttf", (int)(ecran10.h * 0.47));
    char *score_w = int_to_char(cnt_w);
    char *score_b = int_to_char(cnt_b);

    Ecrit_txt(renderer, (int)(1.8 * ecran10.w), (int)(4 * ecran10.h), score_w, font, BLACK_COLOR);
    Ecrit_txt(renderer, (int)(1.8 * ecran10.w), (int)(6 * ecran10.h), score_b, font, WHITE_COLOR);
    Dessine_pion(window, renderer, (int)(1 * ecran10.w), (int)(4 * ecran10.h), 1, mode);
    Dessine_pion(window, renderer, (int)(1 * ecran10.w), (int)(6 * ecran10.h), 2, mode);
    if (fin == 0)
    {
        Ecrit_txt(renderer, (int)(3.7 * ecran10.w), (int)(0.8 * ecran10.h), "Au tour du joueur", font, BLACK_COLOR);
        Dessine_pion(window, renderer, (int)(6.0 * ecran10.w), (int)(0.66 * ecran10.h), team, mode);
    }
    else if (fin == 1 || fin == 2)
    {
        Ecrit_txt(renderer, (int)(3.8 * ecran10.w), (int)(0.8 * ecran10.h), "Le vainqueur est", font, BLACK_COLOR);
        Dessine_pion(window, renderer, (int)(6.0 * ecran10.w), (int)(0.66 * ecran10.h), fin, mode);
    }
    else if (fin == 3)
    {
        Ecrit_txt(renderer, (int)(3.7 * ecran10.w), (int)(0.8 * ecran10.h), "Pas de vainqueur, egalite.", font, BLACK_COLOR);
    }

    TTF_CloseFont(font);
    free(score_w);
    free(score_b);
}

points *Barre_txt(SDL_Window *window, SDL_Renderer *renderer)
{
    partie ecran100 = slice_screen_100(get_screen_size(window).w, get_screen_size(window).h);
    points *pts_barre = malloc(3 * sizeof(points));
    char *fichier = "Pictures/logo.png";
    int text_weight = 0;
    TTF_Font *font = TTF_OpenFont("arial.ttf", (int)(ecran100.h * 2));

    SDL_SetRenderDrawColor(renderer, DARK_GRAY_COLOR.r, DARK_GRAY_COLOR.g, DARK_GRAY_COLOR.b, DARK_GRAY_COLOR.a); // On change la couleur de dessin en gris
    SDL_Rect rect_fill_barre = {0, 0, get_screen_size(window).w, (ecran100.h * 4)};                               // Pour le fond de la barre
    SDL_RenderFillRect(renderer, &rect_fill_barre);                                                               // On charge le bandeau de la barre
    SDL_SetRenderDrawColor(renderer, BLACK_COLOR.r, BLACK_COLOR.g, BLACK_COLOR.b, BLACK_COLOR.a);                 // On réinitialise la couleur de dessin en noir

    //////////////// Logo ////////////////
    SDL_Rect rect_image_barre_L = {(ecran100.w * 0.5), (ecran100.h * 0.25), (ecran100.w * 2), (ecran100.h * 3.55)}; // Pour placer le logo
    Place_image(renderer, &rect_image_barre_L, fichier);

    int decalage_x = (int)(ecran100.w * 0.75);
    int decalage_y = (int)(ecran100.h * 0.75);
    //////////////// Fichier ////////////////
    // Definit Les limites d'emplacement du boutton
    pts_barre[0].y1 = (int)(0);
    pts_barre[0].y2 = (int)(ecran100.h * 4);
    pts_barre[0].x1 = (int)(ecran100.w * 3);
    text_weight = Ecrit_txt(renderer,
                            (pts_barre[0].x1 + decalage_x),
                            (pts_barre[0].y1 + decalage_y),
                            "Fichier", font, BLUE_COLOR);
    pts_barre[0].x2 = pts_barre[0].x1 + (text_weight + (2 * decalage_x)); // definit la longueur clicable
    // Definit un rectangle pour l'emplacement et la taille de l'image
    SDL_Rect rect_boutton_barre_F = {pts_barre[0].x1,
                                     pts_barre[0].y1,
                                     pts_barre[0].x2 - pts_barre[0].x1,
                                     pts_barre[0].y2};
    Dessine_coter_rect(renderer, rect_boutton_barre_F, BLUE_COLOR); // colore les bords du rectangle

    //////////////// Options ////////////////
    pts_barre[1].y1 = (int)(0);
    pts_barre[1].y2 = pts_barre[0].y2;
    pts_barre[1].x1 = pts_barre[0].x2;
    /// On charge le texte et sa place
    text_weight = Ecrit_txt(renderer,
                            (pts_barre[1].x1 + decalage_x),
                            (pts_barre[1].y1 + decalage_y),
                            "Option", font, BLUE_COLOR);
    pts_barre[1].x2 = pts_barre[1].x1 + (text_weight + (2 * decalage_x)); // definit la longueur clicable
    // Definit un rectangle pour l'emplacement et la taille de l'image
    SDL_Rect rect_boutton_barre_O = {pts_barre[1].x1,
                                     pts_barre[1].y1,
                                     pts_barre[1].x2 - pts_barre[1].x1,
                                     pts_barre[1].y2};
    Dessine_coter_rect(renderer, rect_boutton_barre_O, BLUE_COLOR); // colorie les bords du rectangle

    //////////////// Affichage ////////////////
    pts_barre[2].y1 = (int)(0);
    pts_barre[2].y2 = pts_barre[0].y2;
    pts_barre[2].x1 = pts_barre[1].x2;
    /// On charge le texte et sa place
    text_weight = Ecrit_txt(renderer,
                            (pts_barre[2].x1 + decalage_x),
                            (pts_barre[2].y1 + decalage_y),
                            "Affichage", font, BLUE_COLOR);
    pts_barre[2].x2 = pts_barre[2].x1 + (text_weight + (2 * decalage_x)); // definit la longueur clicable
    // Definit un rectangle pour l'emplacement et la taille de l'image
    SDL_Rect rect_boutton_barre_A = {pts_barre[2].x1,
                                     pts_barre[2].y1,
                                     pts_barre[2].x2 - pts_barre[2].x1,
                                     pts_barre[2].y2};
    Dessine_coter_rect(renderer, rect_boutton_barre_A, BLUE_COLOR); // colorie les bords du rectangle

    TTF_CloseFont(font);
    return pts_barre;
}

void DisplayAll(SDL_Window *window, SDL_Renderer *renderer,
                cell **matrice_Othello, points **mat_rect_Othello, points *pts_barre,
                int cnt_w, int cnt_b, int win, int team, int mode, int menu_barre)
{
    SDL_RenderClear(renderer); // Efface le renderer actuel

    /* Charge de l'image de fond */
    BG_image(renderer, mode);
    /* Charge de la menu barre */
    pts_barre = Barre_txt(window, renderer);
    /* Charge de l'image de l'Othello */
    Base_Othello(window, renderer, mode);
    /*  Charge la totalite des pions poses sur l'othello */
    Place_pion(window, renderer, matrice_Othello, mat_rect_Othello, mode);
    /* Reinitialise les pions valides */
    reset_valid(matrice_Othello);
    /* Rend les cases possibles en pions valides */
    show_valid(matrice_Othello, team);
    /* Charge les pions valides au placement*/
    Place_pion_valid(window, renderer, matrice_Othello, mat_rect_Othello, mode, team);
    /* Compte le score actuel */
    count_score(matrice_Othello, &cnt_w, &cnt_b);
    /* Charge les textes de l'interface */
    Interface_txt(window, renderer, cnt_w, cnt_b, team, mode, win);
    /* Charge les extensions de la menu barre */
    Aff_interaction_barre(window, renderer, pts_barre, menu_barre);

    SDL_RenderPresent(renderer); // Affiche tous les elements charges
}