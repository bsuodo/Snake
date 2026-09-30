#include "engine.h"

// scenes
#include "mid_game.h"
#include "main_menu.h"

#include <SDL3/SDL_main.h>

unsigned long long last_time = 0;
unsigned long long current_time = 0;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    if (argc >= 3)
    {
        SDL_LogError(SDL_LOG_PRIORITY_ERROR, "invalid arguments");
        return 1;
    }

    set_slang_speed(argv[1][0]);

    TTF_Init();
    MIX_Init();

    Window = SDL_CreateWindow("kapol - Amin Boutakmanti (C) 2026", WIDTH, HEIGHT, 0);
    Renderer = SDL_CreateRenderer(Window, NULL);

    mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);

    const char* base_path = SDL_GetBasePath();
    int size_base_path = strlen(base_path);
    
    {
        char assets_path[1024];
        strcpy(assets_path, base_path);
        strcpy(assets_path + size_base_path, "../assets/textures/tile.png");
        TileTEX = IMG_LoadTexture(Renderer, assets_path);
    }
    
    {
        char assets_path[1024];
        strcpy(assets_path, base_path);
        strcpy(assets_path + size_base_path, "../assets/fonts/ARIALBD.TTF");
        font = TTF_OpenFont(assets_path, 64);
    }

    {
        char assets_path[1024];
        strcpy(assets_path, base_path);
        strcpy(assets_path + size_base_path, "../assets/sounds/pickup.mp3");
        goedG = MIX_LoadAudio(mixer, assets_path, false);
    }

    {
        char assets_path[1024];
        strcpy(assets_path, base_path);
        strcpy(assets_path + size_base_path, "../assets/sounds/fout.mp3");
        foutG = MIX_LoadAudio(mixer, assets_path, false);
    }

    TEXT_init();

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    last_time = SDL_GetTicksNS();

    if (quit) return SDL_APP_SUCCESS;
    
    if (sceneInit)
    {
        if (scene == MID_GAME)
            mid_game_init();
        if (scene == MAIN_MENU)
            main_menu_init();
        
        sceneInit = false;
    }

    if (scene == MID_GAME)
        mid_game_update();
    if (scene == MAIN_MENU)
        main_menu_update();

    current_time = SDL_GetTicksNS();
    unsigned long long deltaTime = current_time - last_time;
    if (deltaTime <= FPS_TARGET)
    {
        SDL_DelayNS(FPS_TARGET - deltaTime);
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT)
        return SDL_APP_SUCCESS;
    
    if (scene == MID_GAME)
        mid_game_event(event);
    if (scene == MAIN_MENU)
        main_menu_event(event);

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    return;
}