#include "GUI.h"

SDL_Window *createWindow(int width, int height)
{
    SDL_Window *window = SDL_CreateWindow("Othello",
                                          0,
                                          0,
                                          width, height,
                                          SDL_WINDOW_RESIZABLE); // fenetre placee en haut a gauche de l'ecran
    if (!window)
    {
        Error("createWindow");
    }
    return window;
}

SDL_Rect newRect(int x, int y, int width, int height)
// Fonction qui permet de créer un rectangle sur un canvas
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;
    return rect;
}

void fillBoard(SDL_Window *window, SDL_Renderer *renderer)
// Remplit une fenetre pour afficher le plateau de l'othello
{
    if (renderer == NULL)
        Error("Renderer");

    if (SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255) != 0) // couleur de dessin, ici rouge
        Error("Couleur fond");

    // SDL_RenderClear(renderer);

    SDL_Rect rect = newRect(20, 20, 40, 40);
    if (SDL_RenderFillRect(renderer, &rect) != 0)
    {
        Error("Rectangle");
    }
    // SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // couleur des rectangles
    // SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);
}

void Error(char *chaine)
// Renvoie un message d'erreur en fonction de la fonction
{
    SDL_Log("%s %s\n", chaine, SDL_GetError());
    exit(1);
}