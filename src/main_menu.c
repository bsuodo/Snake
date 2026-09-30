#include "main_menu.h"

void main_menu_init() {}

void main_menu_update()
{
    SDL_SetRenderDrawColor(Renderer, 44, 44, 44, 255);
    SDL_RenderClear(Renderer);

    SDL_SetTextureColorMod(TileTEX, 66, 66, 66);
    for (char y = 0; y < 10; y++)
    {
        for (char x = 0; x < 8; x++)
        {
            SDL_FRect rect_tile = {
                .x = 2 + x * 80,
                .y = 2 + y * 80,
                .w = 76,
                .h = 76,
            };
    
            SDL_RenderTexture(Renderer, TileTEX, NULL, &rect_tile);
        }
    }

    TEXT_rendertext("kapol", WIDTH / 2, 192, 32, true);

    TEXT_rendertext("Press to start", WIDTH / 2, 512 + 1, 32, true);

    SDL_RenderPresent(Renderer);
}

void main_menu_event(SDL_Event* event)
{
    if (event->type == SDL_EVENT_KEY_DOWN)
    {
        scene = MID_GAME;
        sceneInit = true;
    }
}