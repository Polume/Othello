#include "GUI.h"
#include "GUI_init.h"

void run()
{
    // int * BG_color = NULL;
    int BG_color[3] = {60,60,60};

    int run = 1;
    SDL_Event e;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    
    

    if(init_GUI(window, renderer, BG_color)!=0)
        Error("init_GUI.");

    
    SDL_RenderPresent(renderer);
    //-------------------------------------------------------
    /* || Code after init : Event Code  || */
    while(run)
    {
        while(SDL_PollEvent(&e))
        {
            switch(e.type)
            {
                case SDL_QUIT:
                    run = 0;
                    break;
                
            }
        }
    }
    //-------------------------------------------------------

    SDL_RenderClear(renderer);
    Quit_GUI(window, renderer);
}