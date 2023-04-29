#ifndef GUI_H
#define GUI_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "GUI_init.h"
#include "othello.h"

char* int_to_char(int nb);

void Dessine_pion(SDL_Window *window, SDL_Renderer *renderer,
                  SDL_Surface *image_pion, SDL_Texture *texture_poin,
                  int x, int y, int team, int mode);
void Place_pion(SDL_Window *window, SDL_Renderer *renderer,
                SDL_Surface *image_pion, SDL_Texture *texture_pion,
                cell **matrice_Othello, points **mat_rect_Othello, int mode);
void Dessine_pion_border(SDL_Window *window, SDL_Renderer *renderer,
                         SDL_Surface *image_pion, SDL_Texture *texture_pion,
                         int x, int y, int team, int mode);
void Place_pion_border(SDL_Window *window, SDL_Renderer *renderer,
                       SDL_Surface *image_pion, SDL_Texture *texture_pion,
                       cell **matrice_Othello, points **mat_rect_Othello,
                       int team, int mode);
void Affiche_Othello(SDL_Window* window, SDL_Renderer* renderer,
    SDL_Surface* image_BG, SDL_Texture* texture_BG,
    SDL_Surface* image_sides, SDL_Texture* texture_sides,
    SDL_Surface* image_mode, SDL_Texture* texture_mode, int mode);
void get_coord(points** mat_rect_Othello, int* i, int* j);
void get_text_in_rect(SDL_Renderer* renderer, int x, int y, char* text,
    TTF_Font* font, SDL_Texture** texture);

void barre_txt(SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* surface_barre_txt,
    SDL_Texture* texture_txt, TTF_Font* font);

void ecrit_txt(SDL_Window* window, SDL_Renderer* renderer,
    SDL_Surface* image_pion, SDL_Texture* texture_pion, SDL_Texture* texture_txt,
    TTF_Font* font, int cnt_w, int cnt_b, int team, int mode, int fin);
void DisplayAll(SDL_Window* window, SDL_Renderer* renderer,
    SDL_Surface* image_BG, SDL_Texture* texture_BG,
    SDL_Surface* image_base, SDL_Texture* texture_base,
    SDL_Surface* image_mode, SDL_Texture* texture_mode,
    SDL_Surface* image_pion, SDL_Texture* texture_pion,
    SDL_Texture* texture_txt, TTF_Font* font,
    cell** matrice_Othello, points** mat_rect_Othello,
    int cnt_w, int cnt_b, int win, int team, int mode);
void DisplayAll_clear(SDL_Window* window, SDL_Renderer* renderer,
    SDL_Surface* image_BG, SDL_Texture* texture_BG,
    SDL_Surface* image_base, SDL_Texture* texture_base,
    SDL_Surface* image_mode, SDL_Texture* texture_mode,
    SDL_Surface* image_pion, SDL_Texture* texture_pion,
    SDL_Texture* texture_txt);




#endif
