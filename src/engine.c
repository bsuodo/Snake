#include "engine.h"

enum scene scene = MID_GAME;
bool sceneInit = true;

SDL_Window* Window = NULL;
SDL_Renderer* Renderer = NULL;

// assets
SDL_Texture* TileTEX = NULL;
TTF_Font* font = NULL;
MIX_Audio* geluid = NULL;
MIX_Mixer* mixer = NULL;