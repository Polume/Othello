#ifndef GUI_H
#define GUI_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "GUI_init.h"
#include "othello.h"

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
/* - - - - - - - - - - - - - Fonctions de dessins - - - - - - - - - - - - -*/
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void Dessine_pion(SDL_Window *window, SDL_Renderer *renderer, 
                    int x, int y, int team, int mode);
void Dessine_pion_border(SDL_Window *window, SDL_Renderer *renderer,
                    int x, int y, int team, int mode);

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
/* - - - - - - - - - - - - - Fonctions de placements - - - - - - - - - - - - -*/
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void BG_image(SDL_Renderer *renderer, int mode);
void Base_Othello(SDL_Window *window, SDL_Renderer *renderer, int mode);;
void Place_pion(SDL_Window *window, SDL_Renderer *renderer, 
                    cell **matrice_Othello, points **mat_rect_Othello, int mode);
void Place_pion_valid(SDL_Window *window, SDL_Renderer *renderer,
                    cell **matrice_Othello, points **mat_rect_Othello, int mode, int team);

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
/* - - - - - - - - - - - - - Fonction d'imbrication de dessins/d'affichage - - - - - - - - - - - - -*/
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void Interface_txt(SDL_Window* window, SDL_Renderer* renderer,
                    int cnt_w, int cnt_b, int team, int mode, int fin);
points* Intro_bouttons(SDL_Window* window, SDL_Renderer* renderer);
points* Barre_txt(SDL_Window* window, SDL_Renderer* renderer);
void DisplayAll(SDL_Window* window, SDL_Renderer* renderer,
                    cell** matrice_Othello, points** mat_rect_Othello, points* pts_barre,
                    int cnt_w, int cnt_b, int win, int team, int mode, int menu_barre);







#endif