#include "control.h"
#include "GUI_init.h"
#include <gtk/gtk.h>

void demande_fichier(char **filename)
{
    GtkWidget *dialog;
    GtkFileFilter *filter;

    gtk_init(NULL, NULL);

    // Cree une boite de dialogue pour demander le nom de fichier
    dialog = gtk_file_chooser_dialog_new("Enregistrer sous...",
                                         NULL,
                                         GTK_FILE_CHOOSER_ACTION_SAVE,
                                         "Annuler", GTK_RESPONSE_CANCEL,
                                         "Enregistrer", GTK_RESPONSE_ACCEPT,
                                         NULL);

    // Ajoute un filtre pour n afficher que les fichiers textes
    filter = gtk_file_filter_new();
    gtk_file_filter_set_name(filter, "fichier Othello (.oth)");
    gtk_file_filter_add_pattern(filter, "*.oth");
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter);

    // Afficher la boite de dialogue et attendre la reponse de l utilisateur
    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT)
    {
        // Recuperer le nom du fichier choisi par l utilisateur
        *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
    }

    // Ferme la boite de dialogue
    gtk_widget_destroy(dialog);
}

void ajout_extension(char **filename, const char *extension)
{
    // Cherche la derniere occurrence du caractere point
    char *dot = strrchr(*filename, '.');
    if (dot == NULL)
    {
        // Pas d'extension, ajoute l'extension a la fin
        strcat(*filename, extension);
    }
    else
    {
        // Verifie si l extension existe deja
        if (strcmp(dot, extension) != 0)
        {
            // Remplace l ancienne extension par la nouvelle
            strcpy(dot, extension);
        }
    }
}

points *Exten_Fichier(SDL_Window *window, SDL_Renderer *renderer, points pts_barre)
{
    /* nouveau (CTRL - N) + ouvrir (CTRL - O) + enregistrer (CTRL - S) + enregistrer_sous (CTRL - GMAJ - S) + quitter (q) */
    // On a 5 sous categories !
    // Fichier est pts_barre[0]

    partie ecran100 = slice_screen_100(get_screen_size(window).w, get_screen_size(window).h);
    points *pts_selec = malloc(6 * sizeof(points));
    int rect_weight = ecran100.w * 25;
    int rect_height = pts_barre.y2 * 6;
    int decalage_x = (int)(ecran100.w * 0.75);
    int decalage_y = (int)(ecran100.h * 0.75);
    TTF_Font *font = TTF_OpenFont("arial.ttf", (int)(ecran100.h * 2));

    // Chargement du rectangle en fond
    SDL_SetRenderDrawColor(renderer, LIGHT_BLACK_COLOR.r, LIGHT_BLACK_COLOR.g, LIGHT_BLACK_COLOR.b, LIGHT_BLACK_COLOR.a); // On change la couleur de dessin en gris
    SDL_Rect rect_ext = {pts_barre.x1, pts_barre.y2, rect_weight, rect_height};                                           // Pour le fond de la barre
    SDL_RenderFillRect(renderer, &rect_ext);                                                                              // On charge le bandeau de la barre
    Dessine_coter_rect(renderer, rect_ext, BLUE_COLOR);                                                                   // Colorie les bords du rectangle
    SDL_SetRenderDrawColor(renderer, BLACK_COLOR.r, BLACK_COLOR.g, BLACK_COLOR.b, BLACK_COLOR.a);                         // On reinitialise la couleur de dessin en noir

    /*------------------------------------------------------ 1 ------------------------------------------------------*/
    // Definit les limites d emplacement du bouton
    pts_selec[0].x1 = pts_barre.x1;
    pts_selec[0].y1 = pts_barre.y2;
    pts_selec[0].x2 = rect_weight; // Definit la longueur clicable
    pts_selec[0].y2 = (int)(pts_barre.y2 * 2);
    Ecrit_txt(renderer,
              (pts_selec[0].x1 + decalage_x),
              (pts_selec[0].y1 + decalage_y),
              "Nouvelle partie", font, BLUE_COLOR);
    Ecrit_txt(renderer,
              (pts_selec[0].x2 - 100),
              (pts_selec[0].y1 + decalage_y),
              "(ctrl + N)", font, BLUE_COLOR);
    /*------------------------------------------------------ 2 ------------------------------------------------------*/
    // Definit les limites d'emplacement du bouton
    pts_selec[1].x1 = pts_barre.x1;
    pts_selec[1].y1 = pts_selec[0].y2;
    pts_selec[1].x2 = rect_weight; // Definit la longueur clicable
    pts_selec[1].y2 = (int)(pts_barre.y2 * 3);
    Ecrit_txt(renderer,
              (pts_selec[1].x1 + decalage_x),
              (pts_selec[1].y1 + decalage_y),
              "Recommencer la partie", font, BLUE_COLOR);
    Ecrit_txt(renderer,
              (pts_selec[2].x2 - 100),
              (pts_selec[2].y1 + decalage_y),
              "(ctrl + R)", font, BLUE_COLOR);
    /*------------------------------------------------------ 3 ------------------------------------------------------*/
    // Definit Les limites d'emplacement du bouton
    pts_selec[2].x1 = pts_barre.x1;
    pts_selec[2].y1 = pts_selec[1].y2;
    pts_selec[2].x2 = rect_weight; // Definit la longueur clicable
    pts_selec[2].y2 = (int)(pts_barre.y2 * 4);
    Ecrit_txt(renderer,
              (pts_selec[2].x1 + decalage_x),
              (pts_selec[2].y1 + decalage_y),
              "Ouvrir enregistrement", font, BLUE_COLOR);
    Ecrit_txt(renderer,
              (pts_selec[2].x2 - 100),
              (pts_selec[2].y1 + decalage_y),
              "(ctrl + O)", font, BLUE_COLOR);
    /*------------------------------------------------------ 4 ------------------------------------------------------*/
    // Definit Les limites d'emplacement du bouton
    pts_selec[3].x1 = pts_barre.x1;
    pts_selec[3].y1 = pts_selec[2].y2;
    pts_selec[3].x2 = rect_weight; // Definit la longueur clicable
    pts_selec[3].y2 = (int)(pts_barre.y2 * 5);
    Ecrit_txt(renderer,
              (pts_selec[3].x1 + decalage_x),
              (pts_selec[3].y1 + decalage_y),
              "Enregistrer", font, BLUE_COLOR);
    Ecrit_txt(renderer,
              (pts_selec[3].x2 - 100),
              (pts_selec[3].y1 + decalage_y),
              "(ctrl + S)", font, BLUE_COLOR);
    /*------------------------------------------------------ 5 ------------------------------------------------------*/
    // Definit Les limites d'emplacement du bouton
    pts_selec[4].x1 = pts_barre.x1;
    pts_selec[4].y1 = pts_selec[3].y2;
    pts_selec[4].x2 = rect_weight; // Definit la longueur clicable
    pts_selec[4].y2 = (int)(pts_barre.y2 * 6);
    Ecrit_txt(renderer,
              (pts_selec[4].x1 + decalage_x),
              (pts_selec[4].y1 + decalage_y),
              "Enregistrer sous ...", font, BLUE_COLOR);
    Ecrit_txt(renderer,
              (pts_selec[4].x2 - 100),
              (pts_selec[4].y1 + decalage_y),
              "(ctrl + maj + s)", font, BLUE_COLOR);
    /*------------------------------------------------------ 6 ------------------------------------------------------*/
    // Definit Les limites d'emplacement du bouton
    pts_selec[5].x1 = pts_barre.x1;
    pts_selec[5].y1 = pts_selec[4].y2;
    pts_selec[5].x2 = rect_weight; // Definit la longueur clicable
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

points *Exten_Option(SDL_Window *window, SDL_Renderer *renderer, points pts_barre)
{
    /* retour_au_coup_precedent (CTRL - Z)  + musique (ON/OFF) + mode */
    // On a 4 sous categories !
    // Option est pts_barre[1]

    partie ecran100 = slice_screen_100(get_screen_size(window).w, get_screen_size(window).h);
    points *pts_selec = malloc(4 * sizeof(points));
    int rect_weight = pts_barre.x1 + (int)(ecran100.w * 20);
    int rect_height = pts_barre.y2 * 4;
    int decalage_x = (int)(ecran100.w * 0.75);
    int decalage_y = (int)(ecran100.h * 0.75);
    TTF_Font *font = TTF_OpenFont("arial.ttf", (int)(ecran100.h * 2));

    // Chargement du rectangle en fond
    SDL_SetRenderDrawColor(renderer, LIGHT_BLACK_COLOR.r, LIGHT_BLACK_COLOR.g, LIGHT_BLACK_COLOR.b, LIGHT_BLACK_COLOR.a); // On change la couleur de dessin en gris
    SDL_Rect rect_ext = {pts_barre.x1, pts_barre.y2, rect_weight - pts_barre.x1, rect_height};                            // Pour le fond de la barre
    SDL_RenderFillRect(renderer, &rect_ext);                                                                              // On charge le bandeau de la barre
    Dessine_coter_rect(renderer, rect_ext, BLUE_COLOR);                                                                   // Colorie les bords du rectangle
    SDL_SetRenderDrawColor(renderer, BLACK_COLOR.r, BLACK_COLOR.g, BLACK_COLOR.b, BLACK_COLOR.a);                         // On reinitialise la couleur de dessin en noir

    /*------------------------------------------------------ 1 ------------------------------------------------------*/
    // Definit Les limites d'emplacement du bouton
    pts_selec[0].x1 = pts_barre.x1;
    pts_selec[0].y1 = pts_barre.y2;
    pts_selec[0].x2 = rect_weight; // Definit la longueur clicable
    pts_selec[0].y2 = (int)(pts_barre.y2 * 2);
    Ecrit_txt(renderer,
              (pts_selec[0].x1 + decalage_x),
              (pts_selec[0].y1 + decalage_y),
              "Coup precedent", font, BLUE_COLOR);
    Ecrit_txt(renderer,
              (pts_selec[0].x2 - 100),
              (pts_selec[0].y1 + decalage_y),
              "(ctrl + Z)", font, BLUE_COLOR);
    /*------------------------------------------------------ 2 ------------------------------------------------------*/
    // Definit Les limites d'emplacement du bouton
    pts_selec[1].x1 = pts_barre.x1;
    pts_selec[1].y1 = pts_selec[0].y2;
    pts_selec[1].x2 = rect_weight; // Definit la longueur clicable
    pts_selec[1].y2 = (int)(pts_barre.y2 * 3);
    Ecrit_txt(renderer,
              (pts_selec[1].x1 + decalage_x),
              (pts_selec[1].y1 + decalage_y),
              "Musique & Son", font, BLUE_COLOR);
    Ecrit_txt(renderer,
              (pts_selec[1].x2 - 100),
              (pts_selec[1].y1 + decalage_y),
              "(ON/OFF)", font, BLUE_COLOR);
    /*------------------------------------------------------ 3 ------------------------------------------------------*/
    // Definit Les limites d'emplacement du bouton
    pts_selec[2].x1 = pts_barre.x1;
    pts_selec[2].y1 = pts_selec[1].y2;
    pts_selec[2].x2 = rect_weight; // Definit la longueur clicable
    pts_selec[2].y2 = (int)(pts_barre.y2 * 4);
    Ecrit_txt(renderer,
              (pts_selec[2].x1 + decalage_x),
              (pts_selec[2].y1 + decalage_y),
              "Mode", font, BLUE_COLOR);
    Ecrit_txt(renderer,
              (pts_selec[2].x2 - 20),
              (pts_selec[2].y1 + decalage_y),
              ">", font, BLUE_COLOR);
    /*------------------------------------------------------ 4 ------------------------------------------------------*/
    // Definit Les limites d'emplacement du bouton
    pts_selec[3].x1 = pts_barre.x1;
    pts_selec[3].y1 = pts_selec[2].y2;
    pts_selec[3].x2 = rect_weight; // Definit la longueur clicable
    pts_selec[3].y2 = (int)(pts_barre.y2 * 5);
    Ecrit_txt(renderer,
              (pts_selec[3].x1 + decalage_x),
              (pts_selec[3].y1 + decalage_y),
              "Difficulte", font, BLUE_COLOR);
    Ecrit_txt(renderer,
              (pts_selec[3].x2 - 20),
              (pts_selec[3].y1 + decalage_y),
              ">", font, BLUE_COLOR);

    TTF_CloseFont(font);
    return pts_selec;
}
points *Exten_Option_Mode(SDL_Window *window, SDL_Renderer *renderer, points pts_barre)
{
    /* Basique + Elden Ring + UwU */
    // On a 3 sous categories !
    // Fichier est pts_barre[2] qui est pts_selec[2] de Option

    partie ecran100 = slice_screen_100(get_screen_size(window).w, get_screen_size(window).h);
    points *pts_selec = malloc(3 * sizeof(points));
    int rect_weight = (int)(10 * ecran100.w);
    int rect_height = (int)(13 * ecran100.h);
    int decalage_x = (int)(ecran100.w * 0.75);
    int decalage_y = (int)(ecran100.h * 0.75);
    TTF_Font *font = TTF_OpenFont("arial.ttf", (int)(ecran100.h * 2));

    // Chargement du rectangle en fond
    SDL_SetRenderDrawColor(renderer, LIGHT_BLACK_COLOR.r, LIGHT_BLACK_COLOR.g, LIGHT_BLACK_COLOR.b, LIGHT_BLACK_COLOR.a); // On change la couleur de dessin en gris
    SDL_Rect rect_ext = {pts_barre.x2, pts_barre.y1, rect_weight, rect_height};                                           // Pour le fond de la barre
    SDL_RenderFillRect(renderer, &rect_ext);                                                                              // On charge le bandeau de la barre
    Dessine_coter_rect(renderer, rect_ext, BLUE_COLOR);                                                                   // Colorie les bords du rectangle
    SDL_SetRenderDrawColor(renderer, BLACK_COLOR.r, BLACK_COLOR.g, BLACK_COLOR.b, BLACK_COLOR.a);                         // On reinitialise la couleur de dessin en noir

    /*------------------------------------------------------ 1 ------------------------------------------------------*/
    // Definit Les limites d'emplacement du bouton
    pts_selec[0].x1 = pts_barre.x2;
    pts_selec[0].y1 = pts_barre.y1;
    pts_selec[0].x2 = pts_selec[0].x1 + rect_weight; // Definit la longueur clicable
    pts_selec[0].y2 = pts_selec[0].y1 + (int)(ecran100.h * 4);
    Ecrit_txt(renderer,
              (pts_selec[0].x1 + decalage_x),
              (pts_selec[0].y1 + decalage_y),
              "Mode Basique", font, BLUE_COLOR);
    /*------------------------------------------------------ 2 ------------------------------------------------------*/
    // Definit Les limites d'emplacement du bouton
    pts_selec[1].x1 = pts_barre.x2;
    pts_selec[1].y1 = pts_selec[0].y2;
    pts_selec[1].x2 = pts_selec[1].x1 + rect_weight; // Definit la longueur clicable
    pts_selec[1].y2 = pts_selec[1].y1 + (int)(ecran100.h * 4);
    Ecrit_txt(renderer,
              (pts_selec[1].x1 + decalage_x),
              (pts_selec[1].y1 + decalage_y),
              "Mode Elden Ring", font, BLUE_COLOR);
    /*------------------------------------------------------ 3 ------------------------------------------------------*/
    // Definit Les limites d'emplacement du bouton
    pts_selec[2].x1 = pts_barre.x2;
    pts_selec[2].y1 = pts_selec[1].y2;
    pts_selec[2].x2 = pts_selec[2].x1 + rect_weight; // Definit la longueur clicable
    pts_selec[2].y2 = pts_selec[2].y1 + rect_height;
    Ecrit_txt(renderer,
              (pts_selec[2].x1 + decalage_x),
              (pts_selec[2].y1 + decalage_y),
              "Mode UwU", font, BLUE_COLOR);
    TTF_CloseFont(font);
    return pts_selec;
}

points *Exten_Option_Difficulte(SDL_Window *window, SDL_Renderer *renderer, points pts_barre)
{
    /* Facile + Normal */
    // On a 2 sous categories !
    // Fichier est pts_barre[3] qui est pts_selec[3] de Option

    partie ecran100 = slice_screen_100(get_screen_size(window).w, get_screen_size(window).h);
    points *pts_selec = malloc(2 * sizeof(points));
    int rect_weight = (int)(10 * ecran100.w);
    int rect_height = (int)(4 * ecran100.h) * 2;
    int decalage_x = (int)(ecran100.w * 0.75);
    int decalage_y = (int)(ecran100.h * 0.75);
    TTF_Font *font = TTF_OpenFont("arial.ttf", (int)(ecran100.h * 2));

    // Chargement du rectangle en fond
    SDL_SetRenderDrawColor(renderer, LIGHT_BLACK_COLOR.r, LIGHT_BLACK_COLOR.g, LIGHT_BLACK_COLOR.b, LIGHT_BLACK_COLOR.a); // On change la couleur de dessin en gris
    SDL_Rect rect_ext = {pts_barre.x2, pts_barre.y1, rect_weight, rect_height};                                           // Pour le fond de la barre
    SDL_RenderFillRect(renderer, &rect_ext);                                                                              // On charge le bandeau de la barre
    Dessine_coter_rect(renderer, rect_ext, BLUE_COLOR);                                                                   // Colorie les bords du rectangle
    SDL_SetRenderDrawColor(renderer, BLACK_COLOR.r, BLACK_COLOR.g, BLACK_COLOR.b, BLACK_COLOR.a);                         // On reinitialise la couleur de dessin en noir

    /*------------------------------------------------------ 1 ------------------------------------------------------*/
    // Definit Les limites d'emplacement du bouton
    pts_selec[0].x1 = pts_barre.x2;
    pts_selec[0].y1 = pts_barre.y1;
    pts_selec[0].x2 = pts_selec[0].x1 + rect_weight; // Definit la longueur clicable
    pts_selec[0].y2 = pts_selec[0].y1 + (int)(ecran100.h * 4);
    Ecrit_txt(renderer,
              (pts_selec[0].x1 + decalage_x),
              (pts_selec[0].y1 + decalage_y),
              "IA Facile", font, BLUE_COLOR);
    /*------------------------------------------------------ 2 ------------------------------------------------------*/
    // Definit Les limites d'emplacement du bouton
    pts_selec[1].x1 = pts_barre.x2;
    pts_selec[1].y1 = pts_selec[0].y2;
    pts_selec[1].x2 = pts_selec[1].x1 + rect_weight; // Definit la longueur clicable
    pts_selec[1].y2 = pts_selec[1].y1 + (int)(ecran100.h * 6);
    Ecrit_txt(renderer,
              (pts_selec[1].x1 + decalage_x),
              (pts_selec[1].y1 + decalage_y),
              "AI Normal", font, BLUE_COLOR);
    TTF_CloseFont(font);
    return pts_selec;
}

points *Exten_Affichage(SDL_Window *window, SDL_Renderer *renderer, points pts_barre)
{
    /* fenetre/plein_ecran + dimensions (240p, 360p, 480p, 720p, 1080p) */
    // On a 7 sous categories !
    // Fichier est pts_barre[2]

    partie ecran100 = slice_screen_100(get_screen_size(window).w, get_screen_size(window).h);
    points *pts_selec = malloc(7 * sizeof(points));
    int rect_weight = pts_barre.x1 + (int)(ecran100.w * 20);
    int rect_height = pts_barre.y2 * 6;
    int decalage_x = (int)(ecran100.w * 0.75);
    int decalage_y = (int)(ecran100.h * 0.75);
    TTF_Font *font = TTF_OpenFont("arial.ttf", (int)(ecran100.h * 2));

    // Chargement du rectangle en fond
    SDL_SetRenderDrawColor(renderer, LIGHT_BLACK_COLOR.r, LIGHT_BLACK_COLOR.g, LIGHT_BLACK_COLOR.b, LIGHT_BLACK_COLOR.a); // On change la couleur de dessin en gris
    SDL_Rect rect_ext = {pts_barre.x1, pts_barre.y2, rect_weight - pts_barre.x1, rect_height};                            // Pour le fond de la barre
    SDL_RenderFillRect(renderer, &rect_ext);                                                                              // On charge le bandeau de la barre
    Dessine_coter_rect(renderer, rect_ext, BLUE_COLOR);                                                                   // Colorie les bords du rectangle
    SDL_SetRenderDrawColor(renderer, BLACK_COLOR.r, BLACK_COLOR.g, BLACK_COLOR.b, BLACK_COLOR.a);                         // On reinitialise la couleur de dessin en noir

    /*------------------------------------------------------ 1 ------------------------------------------------------*/
    // Definit Les limites d'emplacement du bouton
    pts_selec[0].x1 = pts_barre.x1;
    pts_selec[0].y1 = pts_barre.y2;
    pts_selec[0].x2 = rect_weight; // Definit la longueur clicable
    pts_selec[0].y2 = (int)(pts_barre.y2 * 2);
    Ecrit_txt(renderer,
              (pts_selec[0].x1 + decalage_x),
              (pts_selec[0].y1 + decalage_y),
              "Fenetrer/Plein ecran", font, BLUE_COLOR);
    Ecrit_txt(renderer,
              (pts_selec[0].x2 - 100),
              (pts_selec[0].y1 + decalage_y),
              "(ON/OFF)", font, BLUE_COLOR);
    /*------------------------------------------------------ 2 ------------------------------------------------------*/
    // Definit Les limites d'emplacement du bouton
    // 426	240
    pts_selec[1].x1 = pts_barre.x1;
    pts_selec[1].y1 = pts_selec[0].y2;
    pts_selec[1].x2 = rect_weight; // Definit la longueur clicable
    pts_selec[1].y2 = (int)(pts_barre.y2 * 3);
    Ecrit_txt(renderer,
              (pts_selec[1].x1 + decalage_x),
              (pts_selec[1].y1 + decalage_y),
              "240p", font, BLUE_COLOR);
    /*------------------------------------------------------ 3 ------------------------------------------------------*/
    // Definit Les limites d'emplacement du bouton
    // 640	360
    pts_selec[2].x1 = pts_barre.x1;
    pts_selec[2].y1 = pts_selec[1].y2;
    pts_selec[2].x2 = rect_weight; // Definit la longueur clicable
    pts_selec[2].y2 = (int)(pts_barre.y2 * 4);
    Ecrit_txt(renderer,
              (pts_selec[2].x1 + decalage_x),
              (pts_selec[2].y1 + decalage_y),
              "360p", font, BLUE_COLOR);
    /*------------------------------------------------------ 4 ------------------------------------------------------*/
    // Definit Les limites d'emplacement du bouton
    // 854	480
    pts_selec[3].x1 = pts_barre.x1;
    pts_selec[3].y1 = pts_selec[2].y2;
    pts_selec[3].x2 = rect_weight; // Definit la longueur clicable
    pts_selec[3].y2 = (int)(pts_barre.y2 * 5);
    Ecrit_txt(renderer,
              (pts_selec[3].x1 + decalage_x),
              (pts_selec[3].y1 + decalage_y),
              "480p", font, BLUE_COLOR);
    /*------------------------------------------------------ 5 ------------------------------------------------------*/
    // Definit Les limites d'emplacement du bouton
    // 1280	720
    pts_selec[4].x1 = pts_barre.x1;
    pts_selec[4].y1 = pts_selec[3].y2;
    pts_selec[4].x2 = rect_weight; // Definit la longueur clicable
    pts_selec[4].y2 = (int)(pts_barre.y2 * 6);
    Ecrit_txt(renderer,
              (pts_selec[4].x1 + decalage_x),
              (pts_selec[4].y1 + decalage_y),
              "720p", font, BLUE_COLOR);
    /*------------------------------------------------------ 6 ------------------------------------------------------*/
    // Definit Les limites d'emplacement du bouton
    // 1920	1080
    pts_selec[5].x1 = pts_barre.x1;
    pts_selec[5].y1 = pts_selec[4].y2;
    pts_selec[5].x2 = rect_weight; // Definit la longueur clicable
    pts_selec[5].y2 = (int)(pts_barre.y2 * 7);
    Ecrit_txt(renderer,
              (pts_selec[5].x1 + decalage_x),
              (pts_selec[5].y1 + decalage_y),
              "1080p", font, BLUE_COLOR);

    TTF_CloseFont(font);
    return pts_selec;
}

// change menu_barre en fonction de l'interaction faite avec la barre de menu
// Si une selection est faite renvoie un event en relation avec la selection et menu_barre = -2
// Si on clic a cote des affichages, on a menu_barre = -1
void interaction_barre(SDL_Window *window, SDL_Renderer *renderer, SDL_Event *e, points *pts_barre, int *menu_barre)
{
    SDL_Event event;
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);
    points *pts_ext = NULL;
    points *pts_sous_ext = NULL;

    // ------------------------------------------------------------- FICHIER - OPTION - AFFICHAGE
    // menu_barre Fichier = 1
    // pts_barre = 0
    if ((pts_barre[0].x1 < mouse_x && mouse_x < pts_barre[0].x2) &&
        (pts_barre[0].y1 < mouse_y && mouse_y < pts_barre[0].y2))
    {
        *menu_barre = 1;
    }
    // menu_barre Option = 2
    // pts_barre = 1
    else if ((pts_barre[1].x1 < mouse_x && mouse_x < pts_barre[1].x2) &&
             (pts_barre[1].y1 < mouse_y && mouse_y < pts_barre[1].y2))
    {
        *menu_barre = 2;
    }
    // menu_barre Affichage = 3
    // pts_barre = 2
    else if ((pts_barre[2].x1 < mouse_x && mouse_x < pts_barre[2].x2) &&
             (pts_barre[2].y1 < mouse_y && mouse_y < pts_barre[2].y2))
    {
        *menu_barre = 3;
    }
    else if (*menu_barre == 1) // Fichier : nouveau (CTRL - N) + ouvrir (CTRL - O) + enregistrer (CTRL - S) + enregistrer_sous (CTRL - GMAJ - S) + quitter (q) ----------------------------------
    {
        // Afficher l'extension de Fichier
        pts_ext = Exten_Fichier(window, renderer, pts_barre[0]);

        if ((pts_ext[0].x1 < mouse_x && mouse_x < pts_ext[0].x2) && // Fichier->nouveau
            (pts_ext[0].y1 < mouse_y && mouse_y < pts_ext[0].y2))   // pts_ext[0] de Fichier
        {
            event.type = SDL_KEYDOWN;
            event.key.keysym.sym = SDLK_n;
            *e = event;
            *menu_barre = -2;
            free(pts_ext);
        }
        else if ((pts_ext[1].x1 < mouse_x && mouse_x < pts_ext[1].x2) && // Fichier->Recommencer
                 (pts_ext[1].y1 < mouse_y && mouse_y < pts_ext[1].y2))   // pts_ext[1] de Fichier
        {
            event.type = SDL_KEYDOWN;
            event.key.keysym.sym = SDLK_r;
            *e = event;
            *menu_barre = -2;
            free(pts_ext);
        }
        else if ((pts_ext[2].x1 < mouse_x && mouse_x < pts_ext[2].x2) && // Fichier->ouvrir
                 (pts_ext[2].y1 < mouse_y && mouse_y < pts_ext[2].y2))   // pts_ext[2] de Fichier
        {
            event.type = SDL_KEYDOWN;
            event.key.keysym.sym = SDLK_o;
            *e = event;
            *menu_barre = -2;
            free(pts_ext);
        }
        else if ((pts_ext[3].x1 < mouse_x && mouse_x < pts_ext[3].x2) && // Fichier->enregistrer
                 (pts_ext[3].y1 < mouse_y && mouse_y < pts_ext[3].y2))   // pts_ext[3] de Fichier
        {
            event.type = SDL_KEYDOWN;
            event.key.keysym.sym = SDLK_s;
            *e = event;
            *menu_barre = -2;
            free(pts_ext);
        }
        else if ((pts_ext[4].x1 < mouse_x && mouse_x < pts_ext[4].x2) && // Fichier->enregistrer sous
                 (pts_ext[4].y1 < mouse_y && mouse_y < pts_ext[4].y2))   // pts_ext[4] de Fichier
        {
            event.type = SDL_KEYDOWN;
            event.key.keysym.sym = SDLK_s;
            *e = event;
            *menu_barre = -3;
            free(pts_ext);
        }
        else if ((pts_ext[5].x1 < mouse_x && mouse_x < pts_ext[5].x2) && // Fichier->quitter
                 (pts_ext[5].y1 < mouse_y && mouse_y < pts_ext[5].y2))   // pts_ext[5] de Fichier
        {
            event.type = SDL_KEYDOWN;
            event.key.keysym.sym = SDLK_q;
            *e = event;
            *menu_barre = -2;
            free(pts_ext);
        }
        else
        {
            *menu_barre = -1;
            free(pts_ext);
        }
    }
    else if (*menu_barre == 2) // Option : retour_au_coup_precedent (CTRL - Z) + musique (ON/OFF) + mode + difficulte ----------------------------------
    {
        // Afficher l'extension de Option
        pts_ext = Exten_Option(window, renderer, pts_barre[1]);

        if ((pts_ext[0].x1 < mouse_x && mouse_x < pts_ext[0].x2) && // Option->retour_au_coup_precedent
            (pts_ext[0].y1 < mouse_y && mouse_y < pts_ext[0].y2))   // pts_ext[0] de Option
        {
            event.type = SDL_KEYDOWN;
            event.key.keysym.sym = SDLK_z;
            *e = event;
            *menu_barre = -6;
            free(pts_ext);
        }
        else if ((pts_ext[1].x1 < mouse_x && mouse_x < pts_ext[1].x2) && // Option->musique
                 (pts_ext[1].y1 < mouse_y && mouse_y < pts_ext[1].y2))   // pts_ext[1] de Option
        {
            event.type = SDL_KEYDOWN;
            event.key.keysym.sym = SDLK_z;
            *e = event;
            *menu_barre = -4;
            free(pts_ext);
        }
        else if ((pts_ext[2].x1 < mouse_x && mouse_x < pts_ext[2].x2) && // Option->Mode
                 (pts_ext[2].y1 < mouse_y && mouse_y < pts_ext[2].y2))   // pts_selec[2] de Option
        {
            *menu_barre = 4;
            free(pts_ext);
        }
        else if ((pts_ext[3].x1 < mouse_x && mouse_x < pts_ext[3].x2) && // Option->Difficulte
                 (pts_ext[3].y1 < mouse_y && mouse_y < pts_ext[3].y2))   // pts_selec[3] de Option
        {
            *menu_barre = 5;
            free(pts_ext);
        }
        else
        {
            *menu_barre = -1;
            free(pts_ext);
        }
    }
    else if (*menu_barre == 3) // Affichage : fenetrer/plein_ecran + dimentions (144p, 240p, 360p, 480p, 720p, 1080p) --------------------------------------------------------------------
    {
        // Afficher l'extension de Affichage
        pts_ext = Exten_Affichage(window, renderer, pts_barre[1]);
        if ((pts_ext[0].x1 < mouse_x && mouse_x < pts_ext[0].x2) && // Affichage->fenetrer/plein_ecran
            (pts_ext[0].y1 < mouse_y && mouse_y < pts_ext[0].y2))   // pts_selec[0] de Affichage
        {
            if (SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN) // fenetrer/plein_ecran
            {
                SDL_SetWindowFullscreen(window, 0);
            }
            else // Sinon, on passe en fullscreen
            {
                SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
            }
            *menu_barre = -1;
            free(pts_ext);
        }
        else if ((pts_ext[1].x1 < mouse_x && mouse_x < pts_ext[1].x2) && // Affichage->240p
                 (pts_ext[1].y1 < mouse_y && mouse_y < pts_ext[1].y2))   // pts_selec[1] de Option
        {
            // Redimensionner la fenetre a 426x240 pixels
            SDL_SetWindowSize(window, 426, 240);
            *menu_barre = -5;
            free(pts_ext);
        }
        else if ((pts_ext[2].x1 < mouse_x && mouse_x < pts_ext[2].x2) && // Affichage->360p
                 (pts_ext[2].y1 < mouse_y && mouse_y < pts_ext[2].y2))   // pts_selec[2] de Option
        {
            // Redimensionner la fenetre a 640x360 pixels
            SDL_SetWindowSize(window, 640, 360);
            *menu_barre = -5;
            free(pts_ext);
        }
        else if ((pts_ext[3].x1 < mouse_x && mouse_x < pts_ext[3].x2) && // Affichage-> 480p
                 (pts_ext[3].y1 < mouse_y && mouse_y < pts_ext[3].y2))   // pts_selec[3] de Option
        {
            // Redimensionner la fenetre a 854x480 pixels
            SDL_SetWindowSize(window, 854, 480);
            *menu_barre = -5;
            free(pts_ext);
        }
        else if ((pts_ext[4].x1 < mouse_x && mouse_x < pts_ext[4].x2) && // Affichage->720p
                 (pts_ext[4].y1 < mouse_y && mouse_y < pts_ext[4].y2))   // pts_selec[4] de Option
        {
            // Redimensionner la fenetre a 1280x720 pixels
            SDL_SetWindowSize(window, 1280, 720);
            *menu_barre = -5;
            free(pts_ext);
        }
        else if ((pts_ext[5].x1 < mouse_x && mouse_x < pts_ext[5].x2) && // Affichage->1080p
                 (pts_ext[5].y1 < mouse_y && mouse_y < pts_ext[5].y2))   // pts_selec[5] de Option
        {
            // Redimensionner la fenetre a 1920x1080 pixels
            SDL_SetWindowSize(window, 1920, 1080);
            *menu_barre = -5;
            free(pts_ext);
        }
        else
        {
            *menu_barre = -1;
            free(pts_ext);
        }
    }
    else if (*menu_barre == 4) // Option->Mode : Normal + Elden Ring + UwU ------------------------------------------------------------------------------------------------------
    {
        // Afficher l'extension de Option
        pts_ext = Exten_Option(window, renderer, pts_barre[1]);
        // Afficher l'extension de Mode
        pts_sous_ext = Exten_Option_Mode(window, renderer, pts_ext[2]);
        if ((pts_sous_ext[0].x1 < mouse_x && mouse_x < pts_sous_ext[0].x2) && // Option->Mod->Basique
            (pts_sous_ext[0].y1 < mouse_y && mouse_y < pts_sous_ext[0].y2))   // pts_selec[0] de Affichage
        {
            *menu_barre = -10;
            free(pts_sous_ext);
            free(pts_ext);
        }
        else if ((pts_sous_ext[1].x1 < mouse_x && mouse_x < pts_sous_ext[1].x2) && // Option->Mod->Elden Ring
                 (pts_sous_ext[1].y1 < mouse_y && mouse_y < pts_sous_ext[1].y2))   // pts_selec[1] de Option
        {
            *menu_barre = -11;
            free(pts_sous_ext);
            free(pts_ext);
        }
        else if ((pts_sous_ext[2].x1 < mouse_x && mouse_x < pts_sous_ext[2].x2) && // Option->Mod->UwU
                 (pts_sous_ext[2].y1 < mouse_y && mouse_y < pts_sous_ext[2].y2))   // pts_selec[1] de Option
        {
            *menu_barre = -12;
            free(pts_sous_ext);
            free(pts_ext);
        }
        else
        {
            *menu_barre = -1;
            free(pts_sous_ext);
            free(pts_ext);
        }
    }
    else if (*menu_barre == 5) // Option->Difficulte : Facile + Normal ------------------------------------------------------------------------------------------------------
    {
        // Afficher l'extension de Option
        pts_ext = Exten_Option(window, renderer, pts_barre[1]);
        // Afficher l'extension de Mode
        pts_sous_ext = Exten_Option_Difficulte(window, renderer, pts_ext[3]);

        if ((pts_sous_ext[0].x1 < mouse_x && mouse_x < pts_sous_ext[0].x2) && // Option->Difficulte->Facile
            (pts_sous_ext[0].y1 < mouse_y && mouse_y < pts_sous_ext[0].y2))   // pts_selec[0] de Affichage
        {
            *menu_barre = -7;
            free(pts_sous_ext);
            free(pts_ext);
        }
        else if ((pts_sous_ext[1].x1 < mouse_x && mouse_x < pts_sous_ext[1].x2) && // Option->Difficulte->Normal
                 (pts_sous_ext[1].y1 < mouse_y && mouse_y < pts_sous_ext[1].y2))   // pts_selec[1] de Option
        {
            *menu_barre = -8;
            free(pts_sous_ext);
            free(pts_ext);
        }
        else
        {
            *menu_barre = -1;
            free(pts_sous_ext);
            free(pts_ext);
        }
    }
    else
    {
        *menu_barre = -1;
    }
}

void Aff_interaction_barre(SDL_Window *window, SDL_Renderer *renderer, points *pts_barre, int menu_barre)
{
    switch (menu_barre)
    {
    case 1:
        // Afficher l'extension de Fichier
        Exten_Fichier(window, renderer, pts_barre[0]);
        break;
    case 2:
        // Afficher l'extension de Option
        Exten_Option(window, renderer, pts_barre[1]);
        break;
    case 3:
        // Afficher l'extension de Affichage
        Exten_Affichage(window, renderer, pts_barre[2]);
        break;
    case 4:
        // Afficher l'extension de Option
        points *p_ext_Option_mode = Exten_Option(window, renderer, pts_barre[1]);
        // Afficher l'extension de Option-->Mode
        Exten_Option_Mode(window, renderer, p_ext_Option_mode[2]);
        free(p_ext_Option_mode);
        break;
    case 5:
        // Afficher l'extension de Option
        points *p_ext_Option_difficulte = Exten_Option(window, renderer, pts_barre[1]);
        // Afficher l'extension de Option-->Difficulte
        Exten_Option_Difficulte(window, renderer, p_ext_Option_difficulte[3]);
        free(p_ext_Option_difficulte);
        break;
    }
}