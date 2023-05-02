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
                    int x, int y, int team, int mode);
void Place_pion(SDL_Window *window, SDL_Renderer *renderer, 
                    cell **matrice_Othello, points **mat_rect_Othello, int mode);
void Dessine_pion_border(SDL_Window *window, SDL_Renderer *renderer,
                    int x, int y, int team, int mode);
void Place_pion_border(SDL_Window *window, SDL_Renderer *renderer,
                    cell **matrice_Othello, points **mat_rect_Othello, int team, int mode);
void Affiche_Othello(SDL_Window* window, SDL_Renderer* renderer,
                    int mode);
void get_coord(points** mat_rect_Othello, int* i, int* j);
void ecrit_txt(SDL_Renderer* renderer, 
                    int x, int y, char* text, TTF_Font* font);

void barre_txt(SDL_Window* window, SDL_Renderer* renderer);

void interface_txt(SDL_Window* window, SDL_Renderer* renderer,
                TTF_Font* font, int cnt_w, int cnt_b, int team, int mode, int fin);
void DisplayAll(SDL_Window* window, SDL_Renderer* renderer,
                cell** matrice_Othello, points** mat_rect_Othello,
                int cnt_w, int cnt_b, int win, int team, int mode);


#endif
