#include "control.h"
#include "GUI_init.h"

points* Exten_Fichier(SDL_Window* window, SDL_Renderer* renderer, points pts_barre)
{
    /* nouveau (CTRL - N) + ouvrir (CTRL - O) + enregistrer (CTRL - S) + enregistrer_sous (CTRL - GMAJ - S) + quitter (q) */
    // On a 5 sous categories !
    // Fichier est pts_barre[0]

    partie ecran100 = slice_screen_100(get_screen_size(window).w, get_screen_size(window).h);
    points* pts_selec = malloc(6*sizeof(points));
    int rect_weight = ecran100.w * 25;
    int rect_height = pts_barre.y2 * 6;
    int decalage_x = (int)(ecran100.w * 0.75);
    int decalage_y = (int)(ecran100.h * 0.75);
    TTF_Font* font = TTF_OpenFont("arial.ttf", (int)(ecran100.h * 2));

    // Chargement du rectangle en fond
    SDL_SetRenderDrawColor(renderer, LIGHT_BLACK_COLOR.r, LIGHT_BLACK_COLOR.g, LIGHT_BLACK_COLOR.b, LIGHT_BLACK_COLOR.a); // On change la couleur de dessin en gris
    SDL_Rect rect_ext  = { pts_barre.x1, pts_barre.y2, rect_weight, rect_height }; // Pour le fond de la barre
    SDL_RenderFillRect(renderer, &rect_ext); // On charge le bandeau de la barre
    Dessine_coter_rect(renderer, rect_ext, BLUE_COLOR); // colore les bords du rectangle
    SDL_SetRenderDrawColor(renderer, BLACK_COLOR.r, BLACK_COLOR.g, BLACK_COLOR.b, BLACK_COLOR.a); // On reinitialise la couleur de dessin en noir

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
    // On a 4 sous categories !
    // Fichier est pts_barre[1]

    partie ecran100 = slice_screen_100(get_screen_size(window).w, get_screen_size(window).h);
    points* pts_selec = malloc(5*sizeof(points));
    int rect_weight = pts_barre.x1 + (int)(ecran100.w * 20);
    int rect_height = pts_barre.y2 * 4;
    int decalage_x = (int)(ecran100.w * 0.75);
    int decalage_y = (int)(ecran100.h * 0.75);
    TTF_Font* font = TTF_OpenFont("arial.ttf", (int)(ecran100.h * 2));

    // Chargement du rectangle en fond
    SDL_SetRenderDrawColor(renderer, LIGHT_BLACK_COLOR.r, LIGHT_BLACK_COLOR.g, LIGHT_BLACK_COLOR.b, LIGHT_BLACK_COLOR.a); // On change la couleur de dessin en gris
    SDL_Rect rect_ext  = { pts_barre.x1, pts_barre.y2, rect_weight - pts_barre.x1, rect_height }; // Pour le fond de la barre
    SDL_RenderFillRect(renderer, &rect_ext); // On charge le bandeau de la barre
    Dessine_coter_rect(renderer, rect_ext, BLUE_COLOR); // colore les bords du rectangle
    SDL_SetRenderDrawColor(renderer, BLACK_COLOR.r, BLACK_COLOR.g, BLACK_COLOR.b, BLACK_COLOR.a); // On reinitialise la couleur de dessin en noir

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
             (pts_selec[1].x2 - 100), 
             (pts_selec[1].y1 + decalage_y), 
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
             (pts_selec[3].x2 - 20), 
             (pts_selec[3].y1 + decalage_y), 
             ">", font, BLUE_COLOR);

    TTF_CloseFont(font);
    return pts_selec;
}
points* Exten_Option_Mode(SDL_Window* window, SDL_Renderer* renderer, points pts_barre)
{
    /* Elden Ring + UwU */
    // On a 2 sous categories !
    // Fichier est pts_barre[3] qui est pts_selec[3] de Option

    partie ecran100 = slice_screen_100(get_screen_size(window).w, get_screen_size(window).h);
    points* pts_selec = malloc(3*sizeof(points));
    int rect_weight =(int)(10 * ecran100.w);
    int rect_height =(int)(4 * ecran100.h) * 2;
    int decalage_x = (int)(ecran100.w * 0.75);
    int decalage_y = (int)(ecran100.h * 0.75);
    TTF_Font* font = TTF_OpenFont("arial.ttf", (int)(ecran100.h * 2));

    // Chargement du rectangle en fond
    SDL_SetRenderDrawColor(renderer, LIGHT_BLACK_COLOR.r, LIGHT_BLACK_COLOR.g, LIGHT_BLACK_COLOR.b, LIGHT_BLACK_COLOR.a); // On change la couleur de dessin en gris
    SDL_Rect rect_ext  = { pts_barre.x2, pts_barre.y1, rect_weight, rect_height }; // Pour le fond de la barre
    SDL_RenderFillRect(renderer, &rect_ext); // On charge le bandeau de la barre
    Dessine_coter_rect(renderer, rect_ext, BLUE_COLOR); // colore les bords du rectangle
    SDL_SetRenderDrawColor(renderer, BLACK_COLOR.r, BLACK_COLOR.g, BLACK_COLOR.b, BLACK_COLOR.a); // On reinitialise la couleur de dessin en noir

    /*------------------------------------------------------1------------------------------------------------------*/
    // Definit Les limites d'emplacement du boutton
    pts_selec[0].x1 = pts_barre.x2;
    pts_selec[0].y1 = pts_barre.y1;
    pts_selec[0].x2 = rect_weight; // definit la longueur clicable
    pts_selec[0].y2 = pts_selec[0].y1 + (int)(ecran100.h * 4);
    Ecrit_txt(renderer, 
             (pts_selec[0].x1 + decalage_x), 
             (pts_selec[0].y1 + decalage_y), 
             "Mode Elden Ring", font, BLUE_COLOR);
    /*------------------------------------------------------2------------------------------------------------------*/
    // Definit Les limites d'emplacement du boutton
    pts_selec[1].x1 = pts_barre.x2;
    pts_selec[1].y1 = pts_selec[0].y2;
    pts_selec[1].x2 = rect_weight; // definit la longueur clicable
    pts_selec[1].y2 = pts_selec[0].y2 + (int)(ecran100.h * 4);
    Ecrit_txt(renderer, 
             (pts_selec[1].x1 + decalage_x), 
             (pts_selec[1].y1 + decalage_y), 
             "Mode UwU", font, BLUE_COLOR);

    TTF_CloseFont(font);
    return pts_selec;
}

points* Exten_Affichage(SDL_Window* window, SDL_Renderer* renderer, points pts_barre)
{
    /* fenetrer/plein_ecran + dimentions (144p, 240p, 360p, 480p, 720p, 1080p) */
    // On a 7 sous categories !
    // Fichier est pts_barre[2]

    partie ecran100 = slice_screen_100(get_screen_size(window).w, get_screen_size(window).h);
    points* pts_selec = malloc(7*sizeof(points));
    int rect_weight = pts_barre.x1 + (int)(ecran100.w * 20);
    int rect_height = pts_barre.y2 * 6;
    int decalage_x = (int)(ecran100.w * 0.75);
    int decalage_y = (int)(ecran100.h * 0.75);
    TTF_Font* font = TTF_OpenFont("arial.ttf", (int)(ecran100.h * 2));

    // Chargement du rectangle en fond
    SDL_SetRenderDrawColor(renderer, LIGHT_BLACK_COLOR.r, LIGHT_BLACK_COLOR.g, LIGHT_BLACK_COLOR.b, LIGHT_BLACK_COLOR.a); // On change la couleur de dessin en gris
    SDL_Rect rect_ext  = { pts_barre.x1, pts_barre.y2, rect_weight - pts_barre.x1, rect_height }; // Pour le fond de la barre
    SDL_RenderFillRect(renderer, &rect_ext); // On charge le bandeau de la barre
    Dessine_coter_rect(renderer, rect_ext, BLUE_COLOR); // colore les bords du rectangle
    SDL_SetRenderDrawColor(renderer, BLACK_COLOR.r, BLACK_COLOR.g, BLACK_COLOR.b, BLACK_COLOR.a); // On reinitialise la couleur de dessin en noir

    /*------------------------------------------------------1------------------------------------------------------*/
    // Definit Les limites d'emplacement du boutton
    pts_selec[0].x1 = pts_barre.x1;
    pts_selec[0].y1 = pts_barre.y2;
    pts_selec[0].x2 = rect_weight; // definit la longueur clicable
    pts_selec[0].y2 = (int)(pts_barre.y2 * 2);
    Ecrit_txt(renderer, 
             (pts_selec[0].x1 + decalage_x), 
             (pts_selec[0].y1 + decalage_y), 
             "Fenetrer/Plein ecran", font, BLUE_COLOR);
    Ecrit_txt(renderer, 
             (pts_selec[0].x2 - 100), 
             (pts_selec[0].y1 + decalage_y), 
             "(ON/OFF)", font, BLUE_COLOR);
    /*------------------------------------------------------2------------------------------------------------------*/
    // Definit Les limites d'emplacement du boutton
    // 426	240
    pts_selec[1].x1 = pts_barre.x1;
    pts_selec[1].y1 = pts_selec[0].y2;
    pts_selec[1].x2 = rect_weight; // definit la longueur clicable
    pts_selec[1].y2 = (int)(pts_barre.y2 * 3);
    Ecrit_txt(renderer, 
             (pts_selec[1].x1 + decalage_x), 
             (pts_selec[1].y1 + decalage_y), 
             "240p", font, BLUE_COLOR);
    /*------------------------------------------------------3------------------------------------------------------*/
    // Definit Les limites d'emplacement du boutton
    // 640	360
    pts_selec[2].x1 = pts_barre.x1;
    pts_selec[2].y1 = pts_selec[1].y2;
    pts_selec[2].x2 = rect_weight; // definit la longueur clicable
    pts_selec[2].y2 = (int)(pts_barre.y2 * 4);
    Ecrit_txt(renderer, 
             (pts_selec[2].x1 + decalage_x), 
             (pts_selec[2].y1 + decalage_y), 
             "360p", font, BLUE_COLOR);
    /*------------------------------------------------------4------------------------------------------------------*/
    // Definit Les limites d'emplacement du boutton
    // 854	480
    pts_selec[3].x1 = pts_barre.x1;
    pts_selec[3].y1 = pts_selec[2].y2;
    pts_selec[3].x2 = rect_weight; // definit la longueur clicable
    pts_selec[3].y2 = (int)(pts_barre.y2 * 5);
    Ecrit_txt(renderer, 
             (pts_selec[3].x1 + decalage_x), 
             (pts_selec[3].y1 + decalage_y), 
             "480p", font, BLUE_COLOR);
    /*------------------------------------------------------5------------------------------------------------------*/
    // Definit Les limites d'emplacement du boutton
    // 1280	720
    pts_selec[4].x1 = pts_barre.x1;
    pts_selec[4].y1 = pts_selec[3].y2;
    pts_selec[4].x2 = rect_weight; // definit la longueur clicable
    pts_selec[4].y2 = (int)(pts_barre.y2 * 6);
    Ecrit_txt(renderer, 
             (pts_selec[4].x1 + decalage_x), 
             (pts_selec[4].y1 + decalage_y), 
             "720p", font, BLUE_COLOR);
    /*------------------------------------------------------6------------------------------------------------------*/
    // Definit Les limites d'emplacement du boutton
    // 1920	1080
    pts_selec[5].x1 = pts_barre.x1;
    pts_selec[5].y1 = pts_selec[4].y2;
    pts_selec[5].x2 = rect_weight; // definit la longueur clicable
    pts_selec[5].y2 = (int)(pts_barre.y2 * 7);
    Ecrit_txt(renderer, 
             (pts_selec[5].x1 + decalage_x), 
             (pts_selec[5].y1 + decalage_y), 
             "1080p", font, BLUE_COLOR);

    TTF_CloseFont(font);
    return pts_selec;
}

// change menu_barre en fonction de l'interaction faite avec la menu barre
// SI une selection est faite renvoie un event en relation avec la selection et menue_barre prend la valeur -1
SDL_Event interaction_barre(SDL_Window* window, SDL_Renderer* renderer, points * pts_barre, int * menu_barre)
{
    SDL_Event event;
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);
    points * pts_ext = NULL;
    points * pts_sous_ext = NULL;

    // menu_barre Fichier = 1
    // pts_barre = 0
    if( (pts_barre[0].x1 < mouse_x && mouse_x < pts_barre[0].x2) &&
        (pts_barre[0].y1 < mouse_y && mouse_y < pts_barre[0].y2) )
        {
            *menu_barre = 1;
            // Afficher l'extention de Fichier
            pts_ext = Exten_Fichier(window, renderer, pts_barre[0]);
        }
    

    // menu_barre Option = 2
    // pts_barre = 1
    else if((pts_barre[1].x1 < mouse_x && mouse_x < pts_barre[1].x2) &&
            (pts_barre[1].y1 < mouse_y && mouse_y < pts_barre[1].y2) )
    {
        *menu_barre = 2;
        // Afficher l'extention de Fichier
        pts_ext = Exten_Option(window, renderer, pts_barre[1]);

        // Fichier->option est pts_selec[3] de Option
        // manu_barre Option->Mode = 4
        if( (pts_ext[3].x1 < mouse_x && mouse_x < pts_ext[3].x2) &&
            (pts_ext[3].y1 < mouse_y && mouse_y < pts_ext[3].y2) )
        {
            *menu_barre = 4;
            pts_sous_ext = Exten_Option_Mode(window, renderer, pts_ext[3]);
        }
        
    }

    // menu_barre Affichage = 3
    // pts_barre = 2
    else if((pts_barre[2].x1 < mouse_x && mouse_x < pts_barre[2].x2) &&
            (pts_barre[2].y1 < mouse_y && mouse_y < pts_barre[2].y2) )
    {
        // Afficher l'extention de Fichier
        pts_ext = Exten_Affichage(window, renderer, pts_barre[1]);
        *menu_barre = 3;
    }
    else{*menu_barre = -1;}
    printf("menu_barre : %d\n", *menu_barre);
    free(pts_sous_ext);
    free(pts_ext);
    return event;
}

void Aff_interaction_barre(SDL_Window* window, SDL_Renderer* renderer, points * pts_barre, int menu_barre)
{
    switch(menu_barre)
    {
        case 1 :
            // Afficher l'extention de Fichier
            Exten_Fichier(window, renderer, pts_barre[0]);
            break;
        case 2 :
            // Afficher l'extention de Option
            Exten_Option(window, renderer, pts_barre[1]);
            break;
        case 3 :
            // Afficher l'extention de Affichage
            Exten_Affichage(window, renderer, pts_barre[2]);
            break;
        case 4 :
            // Afficher l'extention de Option
            points * p_ext_Option = Exten_Option(window, renderer, pts_barre[1]);
            // Afficher l'extention de Option-->Mode
            Exten_Option_Mode(window, renderer, p_ext_Option[3]);
            free(p_ext_Option);
            break;
    }
}