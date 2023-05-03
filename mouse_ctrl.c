#include "mouse_ctrl.h"

points* Exten_Fichier(SDL_Window* window, SDL_Renderer* renderer, points pts_barre)
{
    /* nouveau (CTRL - N) + ouvrir (CTRL - O) + enregistrer (CTRL - S) + enregistrer_sous (CTRL - GMAJ - S) + quitter (q) */
    // On a 5 sous catégories !
    // Fichier est pts_barre[0]

    partie ecran100 = slice_screen_100(get_screen_size(window).w, get_screen_size(window).h);
    points* pts_selec = malloc(6*sizeof(points));
    int rect_weight = ecran100.w * 25;
    int rect_height = pts_barre.y2 * 6;
    int decalage_x = (int)(0.39 * ecran100.w);
    int decalage_y = (int)(0.27 * ecran100.h);
    TTF_Font* font = TTF_OpenFont("arial.ttf", (int)(ecran100.h * 2));

    SDL_SetRenderDrawColor(renderer, LIGHT_BLACK_COLOR.r, LIGHT_BLACK_COLOR.g, LIGHT_BLACK_COLOR.b, LIGHT_BLACK_COLOR.a); // On change la couleur de dessin en gris
    SDL_Rect rect_fill_ext  = { pts_barre.x1, pts_barre.y2, rect_weight, rect_height }; // Pour le fond de la barre
    SDL_RenderFillRect(renderer, &rect_fill_ext); // On charge le bandeau de la barre
    SDL_SetRenderDrawColor(renderer, BLACK_COLOR.r, BLACK_COLOR.g, BLACK_COLOR.b, BLACK_COLOR.a); // On réinitialise la couleur de dessin en noir

    /*------------------------------------------------------1------------------------------------------------------*/
    // Definit Les limites d'emplacement du boutton
    pts_selec[0].x1 = pts_barre.x1;
    pts_selec[0].y1 = pts_barre.y2;
    pts_selec[0].x2 = rect_weight; // definit la longueur clicable
    pts_selec[0].y2 = (int)(pts_barre.y2 * 2);
    Ecrit_txt(renderer, 
             (pts_selec[0].x1 + decalage_x), 
             (pts_selec[0].y1 + decalage_y), 
             "Nouvelle partie", font, BLUE_COLOR);
    Ecrit_txt(renderer, 
             (pts_selec[0].x2 - 100), 
             (pts_selec[0].y1 + decalage_y), 
             "(ctrl + N)", font, BLUE_COLOR);
    /*------------------------------------------------------2------------------------------------------------------*/
    // Definit Les limites d'emplacement du boutton
    pts_selec[1].x1 = pts_barre.x1;
    pts_selec[1].y1 = pts_selec[0].y2;
    pts_selec[1].x2 = rect_weight; // definit la longueur clicable
    pts_selec[1].y2 = (int)(pts_barre.y2 * 3);
    Ecrit_txt(renderer, 
             (pts_selec[1].x1 + decalage_x), 
             (pts_selec[1].y1 + decalage_y), 
             "Recommencer la partie", font, BLUE_COLOR);
    Ecrit_txt(renderer, 
             (pts_selec[2].x2 - 100), 
             (pts_selec[2].y1 + decalage_y), 
             "(ctrl + R)", font, BLUE_COLOR);
    /*------------------------------------------------------3------------------------------------------------------*/
    // Definit Les limites d'emplacement du boutton
    pts_selec[2].x1 = pts_barre.x1;
    pts_selec[2].y1 = pts_selec[1].y2;
    pts_selec[2].x2 = rect_weight; // definit la longueur clicable
    pts_selec[2].y2 = (int)(pts_barre.y2 * 4);
    Ecrit_txt(renderer, 
             (pts_selec[2].x1 + decalage_x), 
             (pts_selec[2].y1 + decalage_y), 
             "Ouvrir enregistrement", font, BLUE_COLOR);
    Ecrit_txt(renderer, 
             (pts_selec[2].x2 - 100), 
             (pts_selec[2].y1 + decalage_y), 
             "(ctrl + O)", font, BLUE_COLOR);
    /*------------------------------------------------------4------------------------------------------------------*/
    // Definit Les limites d'emplacement du boutton
    pts_selec[3].x1 = pts_barre.x1;
    pts_selec[3].y1 = pts_selec[2].y2;
    pts_selec[3].x2 = rect_weight; // definit la longueur clicable
    pts_selec[3].y2 = (int)(pts_barre.y2 * 5);
    Ecrit_txt(renderer, 
             (pts_selec[3].x1 + decalage_x), 
             (pts_selec[3].y1 + decalage_y), 
             "Enregistrer", font, BLUE_COLOR);
    Ecrit_txt(renderer, 
             (pts_selec[3].x2 - 100), 
             (pts_selec[3].y1 + decalage_y), 
             "(ctrl + S)", font, BLUE_COLOR);
    /*------------------------------------------------------5------------------------------------------------------*/
    // Definit Les limites d'emplacement du boutton
    pts_selec[4].x1 = pts_barre.x1;
    pts_selec[4].y1 = pts_selec[3].y2;
    pts_selec[4].x2 = rect_weight; // definit la longueur clicable
    pts_selec[4].y2 = (int)(pts_barre.y2 * 6);
    Ecrit_txt(renderer, 
             (pts_selec[4].x1 + decalage_x), 
             (pts_selec[4].y1 + decalage_y), 
             "Enregistrer sous ...", font, BLUE_COLOR);
    Ecrit_txt(renderer, 
             (pts_selec[4].x2 - 100), 
             (pts_selec[4].y1 + decalage_y), 
             "(ctrl + maj + s)", font, BLUE_COLOR);
    /*------------------------------------------------------6------------------------------------------------------*/
    // Definit Les limites d'emplacement du boutton
    pts_selec[5].x1 = pts_barre.x1;
    pts_selec[5].y1 = pts_selec[4].y2;
    pts_selec[5].x2 = rect_weight; // definit la longueur clicable
    pts_selec[5].y2 = (int)(pts_barre.y2 * 7);
    Ecrit_txt(renderer,
             (pts_selec[5].x1 + decalage_x),
             (pts_selec[5].y1 + decalage_y),
             "Quitter la fenetre", font, BLUE_COLOR);
    Ecrit_txt(renderer, 
             (pts_selec[5].x2 - 100),
             (pts_selec[5].y1 + decalage_y), 
             "(Q)", font, BLUE_COLOR);

    TTF_CloseFont(font);
    return pts_selec;
}

points* Exten_Option(SDL_Window* window, SDL_Renderer* renderer, points pts_barre)
{
    /* retour_au_coup_precedent (CTRL - Z) + musique (ON/OFF) + mode */
    // On a 4 sous catégories !
    // Fichier est pts_barre[1]

    partie ecran100 = slice_screen_100(get_screen_size(window).w, get_screen_size(window).h);
    points* pts_selec = malloc(6*sizeof(points));
    int rect_weight = ecran100.w * 25;
    int rect_height = pts_barre.y2 * 6;
    int decalage_x = (int)(0.39 * ecran100.w);
    int decalage_y = (int)(0.27 * ecran100.h);
    TTF_Font* font = TTF_OpenFont("arial.ttf", (int)(ecran100.h * 2));

    /*------------------------------------------------------1------------------------------------------------------*/
    // Definit Les limites d'emplacement du boutton
    pts_selec[0].x1 = pts_barre.x1;
    pts_selec[0].y1 = pts_barre.y2;
    pts_selec[0].x2 = rect_weight; // definit la longueur clicable
    pts_selec[0].y2 = (int)(pts_barre.y2 * 2);
    Ecrit_txt(renderer, 
             (pts_selec[0].x1 + decalage_x), 
             (pts_selec[0].y1 + decalage_y), 
             "Coup precedent", font, BLUE_COLOR);
    Ecrit_txt(renderer, 
             (pts_selec[0].x2 - 100), 
             (pts_selec[0].y1 + decalage_y), 
             "(ctrl + Z)", font, BLUE_COLOR);
    /*------------------------------------------------------2------------------------------------------------------*/
    // Definit Les limites d'emplacement du boutton
    pts_selec[1].x1 = pts_barre.x1;
    pts_selec[1].y1 = pts_selec[0].y2;
    pts_selec[1].x2 = rect_weight; // definit la longueur clicable
    pts_selec[1].y2 = (int)(pts_barre.y2 * 3);
    Ecrit_txt(renderer, 
             (pts_selec[1].x1 + decalage_x), 
             (pts_selec[1].y1 + decalage_y), 
             "Coup suivant", font, BLUE_COLOR);
    Ecrit_txt(renderer, 
             (pts_selec[2].x2 - 100), 
             (pts_selec[2].y1 + decalage_y), 
             "(ctrl + Y)", font, BLUE_COLOR);
    /*------------------------------------------------------3------------------------------------------------------*/
    // Definit Les limites d'emplacement du boutton
    pts_selec[2].x1 = pts_barre.x1;
    pts_selec[2].y1 = pts_selec[1].y2;
    pts_selec[2].x2 = rect_weight; // definit la longueur clicable
    pts_selec[2].y2 = (int)(pts_barre.y2 * 4);
    Ecrit_txt(renderer, 
             (pts_selec[2].x1 + decalage_x), 
             (pts_selec[2].y1 + decalage_y), 
             "Musique & Son", font, BLUE_COLOR);
    Ecrit_txt(renderer, 
             (pts_selec[2].x2 - 100), 
             (pts_selec[2].y1 + decalage_y), 
             "(ON/OFF)", font, BLUE_COLOR);
    /*------------------------------------------------------4------------------------------------------------------*/
    // Definit Les limites d'emplacement du boutton
    pts_selec[3].x1 = pts_barre.x1;
    pts_selec[3].y1 = pts_selec[2].y2;
    pts_selec[3].x2 = rect_weight; // definit la longueur clicable
    pts_selec[3].y2 = (int)(pts_barre.y2 * 5);
    Ecrit_txt(renderer, 
             (pts_selec[3].x1 + decalage_x), 
             (pts_selec[3].y1 + decalage_y), 
             "Mode", font, BLUE_COLOR);
    Ecrit_txt(renderer, 
             (pts_selec[3].x2 - 100), 
             (pts_selec[3].y1 + decalage_y), 
             "( --> )", font, BLUE_COLOR);

    TTF_CloseFont(font);
    return pts_selec;
}

void Exten_Affichage(SDL_Window* window, SDL_Renderer* renderer, points pts_barre)
{
    /* fenetrer/plein_ecran + dimentions (144p, 240p, 360p, 480p, 720p, 1080p,) */
    // On a 9 sous catégories !
    // Fichier est pts_barre[2]

}