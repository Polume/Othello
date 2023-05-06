#ifndef GUI_INIT_H
#define GUI_INIT_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#define SIZE_OTHELLO 8
#define WHITE_COLOR \
    (SDL_Color) { 255, 255, 255, 255 }
#define BLACK_COLOR \
    (SDL_Color) { 0, 0, 0, 255 }
#define DARK_GRAY_COLOR \
    (SDL_Color) { 60, 60, 60, 255 }
#define LIGHT_BLACK_COLOR \
    (SDL_Color) { 33, 37, 43, 255 }
#define BLUE_COLOR \
    (SDL_Color) { 0, 100, 170, 255 } // Utile pour les tests (car le fond est blanc/noir)

typedef struct
{
    int x1, x2, y1, y2;
} points;

typedef struct
{
    float w, h;
} partie;

// INIT
void Init_package(void);
void Error(char *chaine);

// MATRICE
points **Cree_mat(SDL_Window *window);
void freeMat(points **board);

// UTILITAIRE
char *int_to_char(int num);
void get_coord(points **mat_rect_Othello, int *i, int *j);
char *add_to_end_str(char *str, char *str_add, int place);
// ECRAN - TAILLE
partie get_screen_size(SDL_Window *window);
partie slice_screen_10(float w, float h);
partie slice_screen_100(float w, float h);
// CHARGEMENT SDL
void Dessine_coter_rect(SDL_Renderer *renderer, SDL_Rect rect, SDL_Color couleur);
void Place_image(SDL_Renderer *renderer, void *rect_place, char *fichier);
int Ecrit_txt(SDL_Renderer *renderer, int x, int y, char *text, TTF_Font *font, SDL_Color textColor);

#endif