#ifndef GUI_H
#define GUI_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "GUI_init.h"
#include "othello.h"

void run();
void Affiche_Othello(SDL_Window *window, SDL_Renderer *renderer,
                     SDL_Surface *image_BG, SDL_Texture *texture_BG,
                     SDL_Surface *image_sides, SDL_Texture *texture_sides,
                     SDL_Surface *image_mode, SDL_Texture *texture_mode, int mode);

void init_pion(SDL_Window *window, SDL_Renderer *renderer,
               SDL_Surface *image_pion, SDL_Texture *texture_pion,
               cell **matrice_Othello, points **mat_rect_Othello, int mode);

void Update_Othello(SDL_Window *window, SDL_Renderer *renderer,
                    SDL_Surface *image_pion, SDL_Texture *texture_pion,
                    cell **matrice_Othello, points **mat_rect_Othello,
                    int x, int y, int mode);
void test(SDL_Renderer *renderer);

void get_coord(points **mat_rect_Othello, int *i, int *j);
void draw_board(SDL_Window *window, SDL_Renderer *renderer,
                SDL_Surface *image_pion, SDL_Texture *texture_pion,
                cell **matrice_Othello, int pos_x, int pos_y, int mode);
void draw_circle(SDL_Window *window, SDL_Renderer *renderer,
                 SDL_Surface *image_pion, SDL_Texture *texture_poin,
                 int x, int y, int team, int mode);

void ctrl_z(SDL_Event e);

#endif
