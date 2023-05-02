#ifndef GUI_INIT_H
#define GUI_INIT_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define SIZE_OTHELLO 8

typedef struct
{
    int x1, x2, y1, y2;
} points;

typedef struct
{
    float w, h;
} partie;

void init_package(void);

partie get_screen_size(SDL_Window* window);
partie slice_screen_10(float w, float h);
partie slice_screen_100(float w, float h);

void init_BG_image(SDL_Renderer *renderer, int mode);
int init_base_Othello(SDL_Window *window, SDL_Renderer *renderer, int mode);
points * init_bouttons(SDL_Window* window, SDL_Renderer* renderer);

void Error(char *chaine);
points **Cree_mat(SDL_Window* window);
void freeMat(points** board);

#endif