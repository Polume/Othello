#ifndef GUI_INIT_H
#define GUI_INIT_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define WIDTH 1100
#define HEIGHT 1000
#define UwU 1

typedef struct
{
    int x1, x2, y1, y2;
} points;

void init_package(void);

int init_BG_image(SDL_Window *window, SDL_Renderer *renderer, SDL_Surface *image_BG, SDL_Texture *texture_BG, int mode);
int init_base_Othello(SDL_Window *window, SDL_Renderer *renderer, SDL_Surface *image_base, SDL_Texture *texture_base);
int init_Othello(SDL_Window *window, SDL_Renderer *renderer, SDL_Surface *image_mode, SDL_Texture *texture_mode, int mode);

void Quit_GUI(SDL_Window *window, SDL_Renderer *renderer);

void Error(char *chaine);
points **Cree_mat();

#endif