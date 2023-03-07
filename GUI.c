#include "GUI.h"
#include "GUI_init.h"

void run()
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    int * BG_color = NULL;
    //int BG_color[3] = {255,0,255};
    SDL_Event e;

    if(init_GUI(window, renderer, BG_color)!=0)
        Error("init_GUI.");

    SDL_RenderPresent(renderer);

    //-------------------------------------------------------
    /* || Code after init : Event Code  || */
    SDL_Delay(5000);
    //-------------------------------------------------------

    SDL_RenderClear(renderer);
    Quit_GUI(window, renderer);
}