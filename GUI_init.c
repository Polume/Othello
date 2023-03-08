#include "GUI_init.h"

SDL_Window *createWindow(int width, int height)
{
    SDL_Window *window = SDL_CreateWindow("Othello",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          width, height,
                                          SDL_WINDOW_MAXIMIZED); // fenetre placee en haut a gauche de l'ecran
    if (!window)
        Error("createWindow");

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

int Place_BG(SDL_Window *window, SDL_Renderer *renderer, int width, int height, int * BG_color)
// Remplit une fenetre pour afficher le plateau de l'othello
{
    if (renderer == NULL)
        Error("Renderer");

    if (SDL_SetRenderDrawColor(renderer, BG_color[0], BG_color[1], BG_color[2], 255) != 0) // couleur de dessin
        Error("Couleur fond");

    SDL_Rect rect = newRect(0, 0, width, height);
    if (SDL_RenderFillRect(renderer, &rect) != 0)
        Error("Rectangle - Couleur de fond");

    SDL_RenderPresent(renderer);

    return EXIT_SUCCESS;
}

int Place_Rect(SDL_Window *window, SDL_Renderer *renderer, int place_x, int place_y, int width_rect, int height_rect, int * BG_color)
// Remplit une fenetre pour afficher le plateau de l'othello
{
    if (renderer == NULL)
        Error("Renderer");

    if (SDL_SetRenderDrawColor(renderer, BG_color[0], BG_color[1], BG_color[2], 255) != 0) // couleur de dessin
        Error("Couleur fond");

    SDL_Rect rect = newRect(place_x, place_y, width_rect, height_rect);
    if (SDL_RenderFillRect(renderer, &rect) != 0)
        Error("Rectangle - Couleur de fond");

    SDL_RenderPresent(renderer);

    return EXIT_SUCCESS;
}

void Error(char *chaine)
// Renvoie un message d'erreur en fonction de la fonction
{
    SDL_Log("%s %s\n", chaine, SDL_GetError());
    exit(EXIT_FAILURE);
}

void Quit_GUI(SDL_Window * window, SDL_Renderer * renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int get_ScreenSize(int * width, int * height) //Permet de récuperer la taille de l'écran (en pixel)
{
    SDL_DisplayMode dm;
    if (SDL_GetDesktopDisplayMode(0, &dm) != 0) //On récupère la taille de l'écran Utilisateur
        Error("SDL_GetDesktopDisplayMode.");

    *width = dm.w-75;
    *height = dm.h-25;

    return EXIT_SUCCESS;
}

int init_GUI(SDL_Window * window,SDL_Renderer * renderer, int * BG_color ) //On devra placer le tableau de matrice representant les cases de l'othello.
{
    int width, height, Border_Othello[3] = NOIR, Interior_Othello[3] = VERT;
    SDL_Texture * texture = NULL;
    SDL_Surface * BG_image = NULL;
    
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) //On initialise tous les paramètres SDL
        Error("Initialisation");

    if(get_ScreenSize(&width, &height) != 0)
        Error("get_ScreenSize faild.");

    window = createWindow(width, height); //On créé la fenetre
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); //On créé la surface de dessin

    if (BG_color == NULL)
    {//Utiliser pour mettre une image en fond
        BG_image = SDL_LoadBMP("BG_Othello.bmp");
        if (BG_image == NULL)
            Error("Image non trouvée.");

        texture = SDL_CreateTextureFromSurface (renderer,BG_image);
        if (texture == NULL)
            Error("Texture non chargée."); 

        SDL_FreeSurface(BG_image);
        Uint32 format;
        if(SDL_QueryTexture(texture, &format, NULL, &width, &height))
            Error("Texture non placée.");
    }
    else
    {//Utiliser pour mettre un fond de couleur unie
        if(Place_BG(window, renderer, width, height, BG_color) != 0) //On met un fond
            Error("Initialisation Place_Rect.");
    }

    //placement du fond de l'Othello On fractionne notre écran en 13x13 parties
    if(Place_Rect(window, renderer, 
                    (width * (float)(3/13)), 
                    (height * (float)(1.5/13)), 
                    (width * (float)(0.5/13)), 
                    (height * (float)(11/13)),
                    Border_Othello) != 0) //On met un fond
            Error("Placement du contour 1 de l'Othello.");

    

    return EXIT_SUCCESS;
}