#ifndef GUI_H
#define GUI_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "GUI_init.h"


void run();
void Affiche_Othello(SDL_Window * window, SDL_Renderer * renderer, 
                     SDL_Surface * image_BG, SDL_Texture * texture_BG,
                     SDL_Surface * image_sides, SDL_Texture * texture_sides, int mode);

points get_coord(points ** mat_rect_Othello);

#endif
