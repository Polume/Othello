#include "othello.h"

int main(int argc, char *argv[])
{
    int **board = initializeBoard();
    printf("Othello !\n");
    printBoard(board);
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("Erreur %s", SDL_GetError());
        exit(1);
    }
    createWindow(700, 700);
    SDL_Window *window = SDL_GL_GetCurrentWindow();
    fillBoard(window);
    SDL_UpdateWindowSurface(window);
    SDL_Quit();
    return 0;
}