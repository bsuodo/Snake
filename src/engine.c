#include "engine.h"

enum scene scene = MAIN_MENU;
bool sceneInit = true;

extern bool quit = false;

SDL_Window* Window = NULL;
SDL_Renderer* Renderer = NULL;

// assets
SDL_Texture* TileTEX = NULL;
TTF_Font* font = NULL;
MIX_Audio* goedG = NULL;
MIX_Audio* foutG = NULL;
MIX_Mixer* mixer = NULL;