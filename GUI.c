#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "GUI.h"
#include "GUI_init.h"
#include "othello.h"


void Affiche_Othello(SDL_Window* window, SDL_Renderer* renderer,
    SDL_Surface* image_BG, SDL_Texture* texture_BG,
    SDL_Surface* image_base, SDL_Texture* texture_base,
    SDL_Surface* image_mode, SDL_Texture* texture_mode, int mode)
{
    // Affichage de l'image de fond
    init_BG_image(renderer, image_BG, texture_BG, mode);

    // Affichage de l'image de l'Othello
    if (init_base_Othello(window, renderer, image_base, texture_base, mode))
        Error("Affichage de l'image de l'Othello échouée.");

    SDL_FreeSurface(image_mode);
    SDL_FreeSurface(image_base);
    SDL_FreeSurface(image_BG);
    SDL_DestroyTexture(texture_mode);
    SDL_DestroyTexture(texture_base);
    SDL_DestroyTexture(texture_BG);
    
}

void Place_pion(SDL_Window* window, SDL_Renderer* renderer,
    SDL_Surface* image_pion, SDL_Texture* texture_pion,
    cell** matrice_Othello, points** mat_rect_Othello, int mode)
{
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            if (matrice_Othello[x][y].color == 1 || matrice_Othello[x][y].color == 2)
            {
                Dessine_pion(window, renderer, image_pion, texture_pion, mat_rect_Othello[x][y].x1, mat_rect_Othello[x][y].y1, matrice_Othello[x][y].color, mode);
                SDL_DestroyTexture(texture_pion);
                SDL_FreeSurface(image_pion);
            }
        }
    }
}

void Place_pion_border(SDL_Window* window, SDL_Renderer* renderer,
    SDL_Surface* image_pion, SDL_Texture* texture_pion,
    cell** matrice_Othello, points** mat_rect_Othello,
    int team, int mode)
{
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            if (matrice_Othello[x][y].valide == 1)
            {
                Dessine_pion_border(window, renderer, image_pion, texture_pion, mat_rect_Othello[x][y].x1, mat_rect_Othello[x][y].y1, team, mode);
                SDL_DestroyTexture(texture_pion);
                SDL_FreeSurface(image_pion);
            }
        }
    }
}

void get_coord(points** mat_rect_Othello, int* i, int* j)
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

void Dessine_pion(SDL_Window* window, SDL_Renderer* renderer,
    SDL_Surface* image_pion, SDL_Texture* texture_pion,
    int x, int y, int team, int mode)
{
    char* fichier = NULL;
    partie ecran100 = slice_screen_100(get_screen_size(window).w, get_screen_size(window).h);
    if (mode == 1)
    {
        if (team == 1)
        {
            fichier = "Pictures/White.png";
        }
        else if (team == 2)
        {
            fichier = "Pictures/Black.png";
        }
    }
    else if (mode == 2)
    {
        if (team == 1)
        {
            fichier = "Pictures/White1.png";
        }
        else if (team == 2)
        {
            fichier = "Pictures/Black1.png";
        }
    }
    // Récupération de l'image
    image_pion = IMG_Load(fichier);
    if (image_pion == NULL)
        Error("Récupération de l'image_pion échoué !");

    // Créer la texture avec l'image
    texture_pion = SDL_CreateTextureFromSurface(renderer, image_pion);
    if (texture_pion == NULL)
        Error("Chargement de la texture_poin échoué !");

    // Définir un rectcangle pour l'emplacement et la taille de l'image
    SDL_Rect rect_pion = { x + (int)(0.39 * ecran100.w), y + (int)(0.27 * ecran100.h), (int)(4.3 * ecran100.w), (int)(8.1 * ecran100.h) };
    // Dessiner la texture dans le rendue
    SDL_RenderCopy(renderer, texture_pion, NULL, &rect_pion);

    SDL_FreeSurface(image_pion);
    SDL_DestroyTexture(texture_pion);
}

void Dessine_pion_border(SDL_Window* window, SDL_Renderer* renderer,
    SDL_Surface* image_pion, SDL_Texture* texture_pion,
    int x, int y, int team, int mode)
{
    partie ecran100 = slice_screen_100(get_screen_size(window).w, get_screen_size(window).h);
    char* fichier = NULL;
    if (mode == 1)
    {
        if (team == 1)
        {
            fichier = "Pictures/White_Border.png";
        }
        else if (team == 2)
        {
            fichier = "Pictures/Black_Border.png";
        }
    }
    else if (mode == 2)
    {
        if (team == 1)
        {
            fichier = "Pictures/White1_Border.png";
        }
        else if (team == 2)
        {
            fichier = "Pictures/Black1_Border.png";
        }
    }
    // Récupération de l'image
    image_pion = IMG_Load(fichier);
    if (image_pion == NULL)
        Error("Récupération de l'image_pion échoué !");

    // Créer la texture avec l'image
    texture_pion = SDL_CreateTextureFromSurface(renderer, image_pion);
    if (texture_pion == NULL)
        Error("Chargement de la texture_pion échoué !");

    // Définir un rectangle pour l'emplacement et la taille de l'image
    SDL_Rect rect_pion = { x + (int)(0.39 * ecran100.w), y + (int)(0.27 * ecran100.h), (int)(4.3 * ecran100.w), (int)(8.1 * ecran100.h) };
    // Dessiner la texture dans le rendue
    SDL_RenderCopy(renderer, texture_pion, NULL, &rect_pion);
    
    SDL_FreeSurface(image_pion);
    SDL_DestroyTexture(texture_pion);
}

void get_text_in_rect(SDL_Renderer* renderer, int x, int y, char* text,
    TTF_Font* font, SDL_Texture** texture)
{
    int text_width;
    int text_height;
    SDL_Rect rect;
    SDL_Surface* surface;
    SDL_Color textColor = { 0, 0, 0, 0 };
    
    surface = TTF_RenderText_Solid(font, text, textColor);
    *texture = SDL_CreateTextureFromSurface(renderer, surface);
    text_width = surface->w;
    text_height = surface->h;
    
    
    rect.x = x;
    rect.y = y;
    rect.w = text_width;
    rect.h = text_height;

    SDL_RenderCopy(renderer, *texture, NULL, &rect);    

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(*texture);
}

char* int_to_char(int num)
{ 
    int i = 0;
    char* str = NULL;
    // compte le nombre de digit
    int temp = num;
    while (temp != 0) {
        i++;
        temp /= 10;
    }
    // Allocate memoire pour la chaine
    str = (char*)malloc(sizeof(char) * (i + 1));
    // convertir en chaine
    str[i] = '\0';
    while (i > 0) {
        str[i - 1] = (num % 10) + '0';
        num /= 10;
        i--;
    }
    return str;
}

void place_image(SDL_Window* window,      SDL_Renderer* renderer,
                 SDL_Surface* image_pion, SDL_Texture* texture_pion,
                 int x, int y, int team, int mode)
{
    partie ecran100 = slice_screen_100(get_screen_size(window).w, get_screen_size(window).h);
    char* fichier = NULL;
    if (mode == 1)
    {
        if (team == 1)
        {
            fichier ="Pictures/White.png";
        }
        else if (team == 2)
        {
            fichier="Pictures/Black.png";
        }
    }
    /* UwU */
    else if (mode == 2)
    {
        if (team == 1)
        {
            fichier="Pictures/White1.png";
        }
        else if (team == 2)
        {
            fichier="Pictures/Black1.png";
        }
    }
    /* UwU */

    //Récupération de l'image
    image_pion = IMG_Load(fichier);
    if (image_pion == NULL)
        Error("Récupération de l'image_pion échoué !");

    // Créer la texture avec l'image
    texture_pion = SDL_CreateTextureFromSurface(renderer, image_pion);
    if (texture_pion == NULL)
        Error("Chargement de la texture_pion échoué !");

    // Définir un rectangle pour l'emplacement et la taille de l'image
    SDL_Rect rect_pion = { x, y, (int)(4.3 * ecran100.w), (int)(8.1 * ecran100.h) };
    // Dessiner la texture dans le rendue
    SDL_RenderCopy(renderer, texture_pion, NULL, &rect_pion);

    SDL_FreeSurface(image_pion);
    SDL_DestroyTexture(texture_pion);
}


void ecrit_txt(SDL_Window* window, SDL_Renderer* renderer,
    SDL_Surface* image_pion, SDL_Texture* texture_pion, SDL_Texture* texture_txt,
    TTF_Font* font, int cnt_w, int cnt_b, int team, int mode, int fin)
{
    partie ecran10 = slice_screen_10(get_screen_size(window).w, get_screen_size(window).h);
    char* score_w = int_to_char(cnt_w);
    char* score_b = int_to_char(cnt_b);
    get_text_in_rect(renderer, (int)(0.5 * ecran10.w), (int)(5.0 * ecran10.h), "Scores : ", font, &texture_txt);
    get_text_in_rect(renderer, (int)(2.5 * ecran10.w), (int)(4.5 * ecran10.h), score_w, font, &texture_txt);
    get_text_in_rect(renderer, (int)(2.5 * ecran10.w), (int)(5.5 * ecran10.h), score_b, font, &texture_txt);
    place_image(window, renderer, image_pion, texture_pion, (int)(1.9 * ecran10.w), (int)(4.35 * ecran10.h), 1, mode);
    place_image(window, renderer, image_pion, texture_pion, (int)(1.9 * ecran10.w), (int)(5.35 * ecran10.h), 2, mode);
    if(fin == 0)
    {
        get_text_in_rect(renderer, (int)(3.7 * ecran10.w), (int)(0.8 * ecran10.h), "Au tour de l'équipe", font, &texture_txt);
        place_image(window, renderer, image_pion, texture_pion, (int)(6.0 * ecran10.w), (int)(0.69 * ecran10.h), team, mode);
    }
    else if(fin == 1 || fin == 2)
    {
        get_text_in_rect(renderer, (int)(3.7 * ecran10.w), (int)(0.8 * ecran10.h), "Le vainqueur est", font, &texture_txt);
        place_image(window, renderer, image_pion, texture_pion, (int)(6.0 * ecran10.w), (int)(0.69 * ecran10.h), fin, mode);
    }
    else if (fin == 3)
    {
        get_text_in_rect(renderer, (int)(3.7 * ecran10.w), (int)(0.8 * ecran10.h), "Pas de vainqueur, egalite.", font, &texture_txt);
    }

    SDL_FreeSurface(image_pion);
    SDL_DestroyTexture(texture_pion);
    SDL_DestroyTexture(texture_txt);
    free(score_w);
    free(score_b);
}

void DisplayAll_clear(SDL_Window* window, SDL_Renderer* renderer,
    SDL_Surface* image_BG, SDL_Texture* texture_BG,
    SDL_Surface* image_base, SDL_Texture* texture_base,
    SDL_Surface* image_mode, SDL_Texture* texture_mode,
    SDL_Surface* image_pion, SDL_Texture* texture_pion,
    SDL_Texture* texture_txt)
{
    SDL_FreeSurface(image_BG); SDL_DestroyTexture(texture_BG);
    SDL_FreeSurface(image_base); SDL_DestroyTexture(texture_base);
    SDL_FreeSurface(image_mode); SDL_DestroyTexture(texture_mode);
    SDL_FreeSurface(image_pion); SDL_DestroyTexture(texture_pion);
    SDL_DestroyTexture(texture_txt);
    SDL_RenderClear(renderer);
}

void DisplayAll(SDL_Window* window, SDL_Renderer* renderer,
    SDL_Surface* image_BG, SDL_Texture* texture_BG,
    SDL_Surface* image_base, SDL_Texture* texture_base,
    SDL_Surface* image_mode, SDL_Texture* texture_mode,
    SDL_Surface* image_pion, SDL_Texture* texture_pion,
    SDL_Texture* texture_txt, TTF_Font* font,
    cell** matrice_Othello, points** mat_rect_Othello,
    int cnt_w, int cnt_b, int win, int team, int mode)
{
    Affiche_Othello(window, renderer,
        image_BG, texture_BG,
        image_base, texture_base,
        image_mode, texture_mode, mode);
    Place_pion(window, renderer,
        image_pion, texture_pion,
        matrice_Othello, mat_rect_Othello, mode);
    reset_valid(matrice_Othello);
    show_valid(matrice_Othello, team);
    Place_pion_border(window, renderer,
        image_pion, texture_pion,
        matrice_Othello, mat_rect_Othello,
        team, mode);
    count_score(matrice_Othello, &cnt_w, &cnt_b);
    ecrit_txt(window, renderer,
        image_pion, texture_pion,
        texture_txt, font,
        cnt_w, cnt_b, team, mode, win);
    Place_pion_border(window, renderer,
        image_pion, texture_pion,
        matrice_Othello, mat_rect_Othello,
        team, mode);
    SDL_RenderPresent(renderer);

    SDL_FreeSurface(image_BG); SDL_DestroyTexture(texture_BG);
    SDL_FreeSurface(image_base); SDL_DestroyTexture(texture_base);
    SDL_FreeSurface(image_mode); SDL_DestroyTexture(texture_mode);
    SDL_FreeSurface(image_pion); SDL_DestroyTexture(texture_pion);
    SDL_DestroyTexture(texture_txt);
}

void barre_txt(SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* surface_barre_txt,
    SDL_Texture* texture_txt, TTF_Font* font) //points*
{
    //EN COUR
    partie ecran10 = slice_screen_10(get_screen_size(window).w, get_screen_size(window).h);
    SDL_Rect rect_pion = { 0, 0, (int)(10 * ecran10.w), (int)(0.5 * ecran10.h) };
    Uint32 gris = SDL_MapRGB(surface_barre_txt->format, 100, 100, 100);
    SDL_FillRect(surface_barre_txt, &rect_pion, gris);

    char* fichier_txt = "Fichier";
    char* option_txt = "Option";
    char* affichage_txt = "Affichage";
    int a = 10;
    TTF_SizeText(font, fichier_txt, &a, &a);
    get_text_in_rect(renderer, (int)(0.05 * ecran10.w),(int)(0.05 * ecran10.h), "Fichier", font, &texture_txt);

    TTF_SizeText(font, option_txt, &a, &a);
    get_text_in_rect(renderer, (int)(0.1 * ecran10.w), (int)(0.05 * ecran10.h), "Option", font, &texture_txt);

    TTF_SizeText(font, affichage_txt, &a, &a);
    get_text_in_rect(renderer, (int)(2.5 * ecran10.w), (int)(0.05 * ecran10.h), "Affichage", font, &texture_txt);

    SDL_FreeSurface(surface_barre_txt);
    SDL_DestroyTexture(texture_txt);
}

////points* init_bouttons(SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* image_bouttons, SDL_Texture* texture_bouttons)
////{
////    points* pts_bouttons = malloc(2 * sizeof(points));
////    partie ecran10 = slice_screen_10(get_screen_size(window).w, get_screen_size(window).h);
////    // Premier Boutton 
////    image_bouttons = IMG_Load("Pictures/Contre_Joueur.png");
////    if (image_bouttons == NULL)
////        Error("Récupération de Contre_Joueur.png échoué !");
////    // Créer la texture avec l'image
////    texture_bouttons = SDL_CreateTextureFromSurface(renderer, image_bouttons);
////    if (texture_bouttons == NULL)
////        Error("Chargement de la texture de Contre_Joueur.png échoué !");
////    // Définir un rectangle pour l'emplacement et la taille de l'image
////    pts_bouttons[0].x1 = (int)(ecran10.w * 2);
////    pts_bouttons[0].y1 = (int)(ecran10.h * 5);
////    pts_bouttons[0].x2 = (int)((ecran10.w * 2) + (ecran10.w * 2));
////    pts_bouttons[0].y2 = (int)((ecran10.h * 5) + (ecran10.h * 2));
////    SDL_Rect rect_boutton_Joueurs = { pts_bouttons[0].x1, pts_bouttons[0].y1, (int)(ecran10.w * 2), (int)(ecran10.h * 2) };
////    // Dessiner la texture dans le rendue
////    SDL_RenderCopy(renderer, texture_bouttons, NULL, &rect_boutton_Joueurs);
////
////    // Second Boutton
////    image_bouttons = IMG_Load("Pictures/Contre_IA.png");
////    if (image_bouttons == NULL)
////        Error("Récupération de Contre_IA.png échoué !");
////    // Créer la texture avec l'image
////    texture_bouttons = SDL_CreateTextureFromSurface(renderer, image_bouttons);
////    if (texture_bouttons == NULL)
////        Error("Chargement de la texture de Contre_IA.png échoué !");
////    // Définir un rectangle pour l'emplacement et la taille de l'image
////    pts_bouttons[1].x1 = (int)(ecran10.w * 6);
////    pts_bouttons[1].y1 = (int)(ecran10.h * 5);
////    pts_bouttons[1].x2 = (int)((ecran10.w * 6) + (ecran10.w * 2));
////    pts_bouttons[1].y2 = (int)((ecran10.h * 5) + (ecran10.h * 2));
////    SDL_Rect rect_boutton_IA = { pts_bouttons[1].x1, pts_bouttons[1].y1, (int)(ecran10.w * 2), (int)(ecran10.h * 2) };
////    // Dessiner la texture dans le rendue
////    SDL_RenderCopy(renderer, texture_bouttons, NULL, &rect_boutton_IA);
////
////    return pts_bouttons;
////}