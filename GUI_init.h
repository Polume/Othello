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

void init_pakage(void);

int init_BG_image       (SDL_Window * window, SDL_Renderer * renderer, SDL_Surface* image_BG,      SDL_Texture* texture_BG, int mode);
int init_sides_Othello  (SDL_Window * window, SDL_Renderer * renderer, SDL_Surface* image_sides,   SDL_Texture* texture_sides);
int init_Othello        (SDL_Window * window, SDL_Renderer * renderer, int mode);

void Destroy_texture(SDL_Surface* image, SDL_Texture* texture);
void Quit_GUI(SDL_Window * window, SDL_Renderer * renderer);

void Error(char *chaine);
int Rect_in_Othello(SDL_Window * window, SDL_Renderer * renderer);
points ** Cree_mat();

#endif