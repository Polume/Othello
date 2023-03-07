#include "othello.h"

int **initializeBoard()
{
    int **board = calloc(8, sizeof(int *));
    for (int i = 0; i < 8; i++)
    {
        board[i] = calloc(8, sizeof(int));
    }
    board[3][3] = 2;
    board[3][4] = 1;
    board[4][4] = 2;
    board[4][3] = 1;

    return board;
}

void printBoard(int **board)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

void freeBoard(int **board)
{
    for (int i = 0; i < 8; i++)
    {
        free(board[i]);
    }
    free(board);
}

void createWindow(int width, int height)
{
    int open = 1; // sert à garder la fenetre ouverte
    SDL_Window *window = SDL_CreateWindow("Othello",
                                          0,
                                          0,
                                          width, height,
                                          0); // fenetre placee en haut a gauche de l'ecran
    if (!window)
    {
        printf("Creation de la fenetre impossible\n");
        exit(1);
    }

    SDL_Surface *window_surface = SDL_GetWindowSurface(window);

    if (!window_surface)
    {
        printf("Recuperation de la surface de la fenetre impossible\n");
        exit(1);
    }

    while (open)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e) > 0)
        {
            if (e.type == SDL_QUIT)
            {
                open = 0;
            }
            SDL_UpdateWindowSurface(window);
        }
    }
}

SDL_Rect newSDL_Rect(int x, int y, int width, int height)
{
    SDL_Rect rectangular;
    rectangular.x = x;
    rectangular.y = y;
    rectangular.w = width;
    rectangular.h = height;
    return rectangular;
}

void fillBoard()
{
    SDL_Window *window = SDL_GL_GetCurrentWindow();
    SDL_Renderer *renderer = NULL;
    renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED); // renderer utilise pour les couleurs

    SDL_SetRenderDrawColor(renderer, 51, 102, 153, 255);
    SDL_RenderClear(renderer);

    SDL_Rect rect = newSDL_Rect(20, 20, 40, 40);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // code RGB
    SDL_RenderFillRect(renderer, &rect);
    SDL_UpdateWindowSurface(window);
}