#ifndef ENGINE_H
#define ENGINE_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>
#define SDL_MAIN_USE_CALLBACKS

#include <string.h>
#include <stdio.h>

#include "text.h"

#define WIDTH 640 
#define HEIGHT 800

#define FPS_TARGET 1000000000 / 60

extern SDL_Window* Window;
extern SDL_Renderer* Renderer;

extern enum scene {
    MAIN_MENU,
    MID_GAME,
};

extern enum scene scene;
extern bool sceneInit;

extern bool quit;

extern SDL_Texture* TileTEX;
extern TTF_Font* font;
extern MIX_Audio* goedG;
extern MIX_Audio* foutG;
extern MIX_Mixer* mixer;

#endif//ENGINE_H