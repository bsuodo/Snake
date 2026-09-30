#include "engine.h"
#include "mid_game.h"

#include "slang.h"

unsigned char MAP[HEIGHT / 80][WIDTH / 80];

SDL_FRect appel = (SDL_FRect){2 + 1 * 80 , 2 + 0 * 80, 76, 76};

void mid_game_init()
{
    slang_reset();

    memset(MAP, 0, sizeof(unsigned char) * (WIDTH / 80) * (HEIGHT / 80));
}

void mid_game_update()
{
    slang_beweeg();

    if ((int)(slang.staart[0].rect.x - 2) % 80 == 0 && (int)(slang.staart[0].rect.y - 2) % 80 == 0)
    {
        slang.x+=slang.staart[0].current_dir[0];
        slang.y+=slang.staart[0].current_dir[1];

        for (int count = slang.lengte - 1; count >= 1; count--)
        {
            slang.staart[count].current_dir[0] = slang.staart[count - 1].current_dir[0];
            slang.staart[count].current_dir[1] = slang.staart[count - 1].current_dir[1];
        }

        memcpy(slang.staart[0].current_dir, slang.will_dir_head, sizeof(slang.staart[0].current_dir));

        memset(MAP, 0, sizeof(unsigned char) * (WIDTH / 80) * (HEIGHT / 80));

        for (int count = 0; count < slang.lengte; count++)
        {
            MAP[((int)slang.staart[count].rect.y - 2) / 80][((int)slang.staart[count].rect.x - 2) / 80] = 1;
        }
    }
    else if  (slang_raakt_rand() ||
    MAP[slang.y + slang.staart[0].current_dir[1]][slang.x + slang.staart[0].current_dir[0]]) {
        
        MIX_PlayAudio(mixer, foutG);
        sceneInit = true;
        scene = MAIN_MENU;
    }

    int hoofd_x = slang.staart[0].rect.x - 2; int hoofd_w = slang.staart[0].rect.w + 4;
    int hoofd_y = slang.staart[0].rect.y - 2; int hoofd_h = slang.staart[0].rect.h + 4;
    if (hoofd_x <= appel.x + appel.w - 2 &&
        hoofd_x + hoofd_w >= appel.x + 2 &&
        hoofd_y <= appel.y + appel.h - 2 &&
        hoofd_y + hoofd_h >= appel.y + 2 )
    {
        if (slang.lengte == 80)
            quit = true;

        do {
            appel.y = (int)SDL_rand(10) * 80 + 2;
            appel.x = (int)SDL_rand(8) * 80 + 2;
        } while (MAP[((int)appel.y - 2) / 80][((int)appel.x - 2) / 80] == 1);

        slang_wordt_langer();

        MIX_PlayAudio(mixer, goedG);
    }

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

    SDL_SetTextureColorMod(TileTEX, 180, 20, 0);
    SDL_RenderTexture(Renderer, TileTEX, NULL, &appel);

    SDL_SetTextureColorMod(TileTEX, 0, 180, 66);
    for (int count = 0; count < slang.lengte; count++)
    {
        SDL_RenderTexture(Renderer, TileTEX, NULL, &slang.staart[count].rect);
    }

    TEXT_renderint(slang.lengte, 640 / 2, 92, DEFAULT, true);

    SDL_RenderPresent(Renderer);

    return;
}

void mid_game_event(SDL_Event* event)
{
    if (event->type == SDL_EVENT_KEY_DOWN)
    {
        if (event->key.key == SDLK_LEFT && slang.staart[0].current_dir[0] != 1)
        {
            slang.will_dir_head[1] = 0;
            slang.will_dir_head[0] = -1;
        }
        if (event->key.key == SDLK_RIGHT && slang.staart[0].current_dir[0] != -1)
        {
            slang.will_dir_head[1] = 0;
            slang.will_dir_head[0] = 1;
        }
        if (event->key.key == SDLK_DOWN && slang.staart[0].current_dir[1] != -1)
        {
            slang.will_dir_head[0] = 0;
            slang.will_dir_head[1] = 1;
        }
        if (event->key.key == SDLK_UP && slang.staart[0].current_dir[1] != 1)
        {
            slang.will_dir_head[0] = 0;
            slang.will_dir_head[1] = -1;
        }
    }
}