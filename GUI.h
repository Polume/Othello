#ifndef GUI_H
#define GUI_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

SDL_Window *createWindow(int width, int height);
SDL_Rect newRect(int x, int y, int width, int height);
void fillBoard(SDL_Window *window, SDL_Renderer *renderer);

void Error(char *chaine);

#endif
