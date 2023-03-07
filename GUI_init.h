#ifndef GUI_INIT_H
#define GUI_INIT_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

SDL_Window *createWindow(int width, int height);
SDL_Rect newRect(int x, int y, int width, int height);
int Place_Rect(SDL_Window * window, SDL_Renderer * renderer, int width, int height, int * BG_color);
void Quit_GUI(SDL_Window * window, SDL_Renderer * renderer);
int init_GUI(SDL_Window * window,SDL_Renderer * renderer, int * BG_color); //On devra placer le tableau de matrice representant les cases de l'othello.


void Error(char *chaine);

#endif