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
    fillBoard();
    SDL_Quit();
    return 0;
}