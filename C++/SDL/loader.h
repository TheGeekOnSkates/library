#ifndef _LOADER_H_
#define _LOADER_H_

#include "include/SDL.h"

SDL_Window *window = NULL;
SDL_Surface* screen = NULL;

char LoadSDL(const char *title) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_Log("Error starting SDL: %s", SDL_GetError());
        return 0;
    }
    window = SDL_CreateWindow(title, 0, 0, 320, 240, SDL_WINDOW_FULLSCREEN);
    if (window == NULL) {
        SDL_Log("Error creating window: %s", SDL_GetError());
        return 0;
    }
    screen = SDL_GetWindowSurface(window);
    if (screen == NULL) {
        SDL_Log("Error creating screen surface: %s", SDL_GetError());
        return 0;
    }
    if (!SDL_ShowCursor(0))
        SDL_Log("Unable to hide mouse cursor");
    return 1;
}

void UnloadSDL() {
    if (screen != NULL) SDL_FreeSurface(screen);
    if (window != NULL) SDL_DestroyWindow(window);
    SDL_Quit();
}

#endif // _LOADER_H_
