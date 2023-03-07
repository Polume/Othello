#include "othello.h"
#include "GUI.h"
#include "PVP.h"
#include "PVC.h"

int main(int argc, char *argv[])
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event e;
    int open = 1; // sert à garder la fenetre ouverte

    int **board = initializeBoard();
    printBoard(board);

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        Error("Initialisation");
    }
    window = createWindow(700, 700);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    fillBoard(window, renderer);

    //-------------------------------------------------------
    SDL_Delay(5000);
    //-------------------------------------------------------

    // while (open)
    // {
    //     while (SDL_PollEvent(&e) > 0)
    //     {
    //         if (e.type == SDL_QUIT)
    //         {
    //             open = 0;
    //         }
    //     }

    // }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}