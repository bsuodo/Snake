#ifndef ENGINE_H
#define ENGINE_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#define SDL_MAIN_USE_CALLBACKS

#include <string.h>
#include <stdio.h>

#define WIDTH 640 
#define HEIGHT 800

#define FPS_TARGET 1000 / 60

extern SDL_Window* Window;
extern SDL_Renderer* Renderer;

extern enum scene {
    MAIN_MENU,
    MID_GAME,
};

extern enum scene scene;

extern SDL_Texture* TileTEX;

#endif//ENGINE_H