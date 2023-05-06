#ifndef MOUSE_CTRL_H
#define MOUSE_CTRL_H

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "GUI_init.h"
#include "GUI.h"

char * explorateur_de_fichier();
void demande_fichier(char** filename);
void ajout_extension(char** filename, const char* extension);

points* Exten_Fichier(SDL_Window* window, SDL_Renderer* renderer, points pts_barre);
points* Exten_Option(SDL_Window* window, SDL_Renderer* renderer, points pts_barre);
points* Exten_Affichage(SDL_Window* window, SDL_Renderer* renderer, points pts_barre);

points* Exten_Option_Mode(SDL_Window* window, SDL_Renderer* renderer, points pts_barre);
points *Exten_Option_Difficulte(SDL_Window *window, SDL_Renderer *renderer, points pts_barre);

void interaction_barre(SDL_Window* window, SDL_Renderer* renderer, SDL_Event * event, points * pts_barre, int * menu_barre);
void Aff_interaction_barre(SDL_Window* window, SDL_Renderer* renderer, points * pts_barre, int menu_barre);

#endif