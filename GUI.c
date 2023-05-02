#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "GUI.h"
#include "GUI_init.h"
#include "othello.h"


void Affiche_Othello(SDL_Window* window, SDL_Renderer* renderer, int mode)
{// Permet d'afficher l'othello et son etat actuelle
    // Affichage de l'image de fond
    init_BG_image(renderer, mode);

    // Affichage de l'image de l'Othello
    if (init_base_Othello(window, renderer, mode))
        Error("Affichage de l'image de l'Othello �chou�e.");    
}

void Place_pion(SDL_Window* window, SDL_Renderer* renderer,
    cell** matrice_Othello, points** mat_rect_Othello, int mode)
{// Permet de placer tous les pions
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

void Place_pion_border(SDL_Window* window, SDL_Renderer* renderer,
    cell** matrice_Othello, points** mat_rect_Othello, int team, int mode)
{// permet de placer tous les pions possible a la selection
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            if (matrice_Othello[x][y].valide == 1)
            {
                Dessine_pion_border(window, renderer, mat_rect_Othello[x][y].x1, mat_rect_Othello[x][y].y1, team, mode);
            }
        }
    }
}

void get_coord(points** mat_rect_Othello, int* i, int* j)
{ // Fonction permettant d'avoir les coordon�es du carr� a l'intereur duquel le joueur a cliquer.
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

void Dessine_pion(SDL_Window* window, SDL_Renderer* renderer, int x, int y, int team, int mode)
{// dessine un pion là ou l'utilisateur ca cliquer
    SDL_Surface* image_pion = NULL;
    SDL_Texture* texture_pion = NULL;
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
    // R�cup�ration de l'image
    image_pion = IMG_Load(fichier);
    if (image_pion == NULL)
        Error("R�cup�ration de l'image_pion �chou� !");

    // Cr�er la texture avec l'image
    texture_pion = SDL_CreateTextureFromSurface(renderer, image_pion);
    if (texture_pion == NULL)
        Error("Chargement de la texture_poin �chou� !");

    // D�finir un rectcangle pour l'emplacement et la taille de l'image
    SDL_Rect rect_pion = { x + (int)(0.39 * ecran100.w), y + (int)(0.27 * ecran100.h), (int)(4.3 * ecran100.w), (int)(8.1 * ecran100.h) };
    // Dessiner la texture dans le rendue
    SDL_RenderCopy(renderer, texture_pion, NULL, &rect_pion);

    SDL_DestroyTexture(texture_pion);
    SDL_FreeSurface(image_pion);
}

void Dessine_pion_border(SDL_Window* window, SDL_Renderer* renderer,
    int x, int y, int team, int mode)
{// Permet de placer les endroits possible ou placer un pion
    SDL_Surface* image_pion = NULL;
    SDL_Texture* texture_pion = NULL;
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
    // R�cup�ration de l'image
    image_pion = IMG_Load(fichier);
    if (image_pion == NULL)
        Error("R�cup�ration de l'image_pion �chou� !");

    // Cr�er la texture avec l'image
    texture_pion = SDL_CreateTextureFromSurface(renderer, image_pion);
    if (texture_pion == NULL)
        Error("Chargement de la texture_pion �chou� !");

    // D�finir un rectangle pour l'emplacement et la taille de l'image
    SDL_Rect rect_pion = { x + (int)(0.39 * ecran100.w), y + (int)(0.27 * ecran100.h), (int)(4.3 * ecran100.w), (int)(8.1 * ecran100.h) };
    // Dessiner la texture dans le rendue
    SDL_RenderCopy(renderer, texture_pion, NULL, &rect_pion);
    
    SDL_DestroyTexture(texture_pion);
    SDL_FreeSurface(image_pion);
}

void ecrit_txt(SDL_Renderer* renderer, int x, int y, char* text,
    TTF_Font* font)
{// ecrit du texte a un emplacement
    SDL_Texture* texture = NULL;
    int text_width;
    int text_height;
    SDL_Rect rect;
    SDL_Surface* surface;
    SDL_Color textColor = { 0, 0, 0, 0 };
    
    surface = TTF_RenderText_Solid(font, text, textColor);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    text_width = surface->w;
    text_height = surface->h;
    
    
    rect.x = x;
    rect.y = y;
    rect.w = text_width;
    rect.h = text_height;

    SDL_RenderCopy(renderer, texture, NULL, &rect);    

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

char* int_to_char(int num)
{ // permet de passer un entier en chaine de caractère
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

void interface_txt(SDL_Window* window, SDL_Renderer* renderer,
    int cnt_w, int cnt_b, int team, int mode, int fin)
{// ecrit un texte dans un rectangle    
    partie ecran10 = slice_screen_10(get_screen_size(window).w, get_screen_size(window).h);
    TTF_Font* font = TTF_OpenFont("arial.ttf", (int)(ecran10.h * 47));
    char* score_w = int_to_char(cnt_w);
    char* score_b = int_to_char(cnt_b);
    get_text_in_rect(renderer, (int)(0.5 * ecran10.w), (int)(5.0 * ecran10.h), "Scores : ", font);
    get_text_in_rect(renderer, (int)(2.5 * ecran10.w), (int)(4.5 * ecran10.h), score_w, font);
    get_text_in_rect(renderer, (int)(2.5 * ecran10.w), (int)(5.5 * ecran10.h), score_b, font);
    Dessine_pion(window, renderer, (int)(1.9 * ecran10.w), (int)(4.35 * ecran10.h), 1, mode);
    Dessine_pion(window, renderer, (int)(1.9 * ecran10.w), (int)(5.35 * ecran10.h), 2, mode);
    if(fin == 0)
    {
        get_text_in_rect(renderer, (int)(3.7 * ecran10.w), (int)(0.8 * ecran10.h), "Au tour du joueur", font);
        Dessine_pion(window, renderer, (int)(6.0 * ecran10.w), (int)(0.69 * ecran10.h), team, mode);
    }
    else if(fin == 1 || fin == 2)
    {
        get_text_in_rect(renderer, (int)(3.8 * ecran10.w), (int)(0.8 * ecran10.h), "Le vainqueur est", font);
        Dessine_pion(window, renderer, (int)(6.0 * ecran10.w), (int)(0.69 * ecran10.h), fin, mode);
    }
    else if (fin == 3)
    {
        get_text_in_rect(renderer, (int)(3.7 * ecran10.w), (int)(0.8 * ecran10.h), "Pas de vainqueur, egalite.", font);
    }

    free(score_w);
    free(score_b);
}

void DisplayAll(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font,
    cell** matrice_Othello, points** mat_rect_Othello,
    int cnt_w, int cnt_b, int win, int team, int mode)
{
    SDL_RenderClear(renderer);
    Affiche_Othello(window, renderer, mode);
    Place_pion(window, renderer, matrice_Othello, mat_rect_Othello, mode);
    reset_valid(matrice_Othello);
    show_valid(matrice_Othello, team);
    Place_pion_border(window, renderer, 
    matrice_Othello, mat_rect_Othello, team, mode);
    count_score(matrice_Othello, &cnt_w, &cnt_b);
    ecrit_txt(window, renderer, font,
        cnt_w, cnt_b, team, mode, win);
    Place_pion_border(window, renderer,
        matrice_Othello, mat_rect_Othello,
        team, mode);
    SDL_RenderPresent(renderer);
}

void barre_txt(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font) //points*
{
    //EN COUR
    SDL_Surface* surface_barre_txt = NULL;
    SDL_Texture* texture_txt = NULL;

    partie ecran10 = slice_screen_10(get_screen_size(window).w, get_screen_size(window).h);
    SDL_Rect rect_pion = { 0, 0, (int)(10 * ecran10.w), (int)(0.5 * ecran10.h) };
    Uint32 gris = SDL_MapRGB(surface_barre_txt->format, 100, 100, 100);
    SDL_FillRect(surface_barre_txt, &rect_pion, gris);

    char* fichier_txt = "Fichier";
    char* option_txt = "Option";
    char* affichage_txt = "Affichage";
    int a = 10;
    TTF_SizeText(font, fichier_txt, &a, &a);
    get_text_in_rect(renderer, (int)(0.05 * ecran10.w),(int)(0.05 * ecran10.h), "Fichier", font);

    TTF_SizeText(font, option_txt, &a, &a);
    get_text_in_rect(renderer, (int)(0.1 * ecran10.w), (int)(0.05 * ecran10.h), "Option", font);

    TTF_SizeText(font, affichage_txt, &a, &a);
    get_text_in_rect(renderer, (int)(2.5 * ecran10.w), (int)(0.05 * ecran10.h), "Affichage", font);

    SDL_DestroyTexture(texture_txt);
    SDL_FreeSurface(surface_barre_txt);
}