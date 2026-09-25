#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>

#include <string.h>

SDL_Window* Window = NULL;
SDL_Renderer* Renderer = NULL;

const unsigned char FPS_TARGET = 1000 / 60;

SDL_Texture* TileTEX = NULL;

unsigned long long last_time = 0;
unsigned long long current_time = 0;

SDL_FRect appel = (SDL_FRect){2 + 1 * 80 , 2 + 0 * 80, 76, 76};

typedef struct {
    signed char current_dir[2];
    SDL_FRect rect;
} blocks;

struct typdef {
    blocks* staart;
    char lengte;
    char speed;
    signed char will_dir_head[2];
} slang;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    Window = SDL_CreateWindow("Snake - Amin Boutakmanti (C) 2026", 640, 800, 0);
    Renderer = SDL_CreateRenderer(Window, NULL);
    
    char assets_path[1024];
    const char* base_path = SDL_GetBasePath();
    int size_base_path = strlen(base_path);

    strcpy(assets_path, base_path);
    strcpy(assets_path + size_base_path, "../assets/tile.png");
    TileTEX = IMG_LoadTexture(Renderer, assets_path);

    slang.lengte = 1;
    slang.speed = 5;
    slang.staart = SDL_malloc(sizeof(blocks));
    slang.staart->rect = (SDL_FRect){
        .x = 2,
        .y = 2,
        .w = 76,
        .h = 76,
    };
    slang.staart[0].current_dir[0] = 1;
    slang.staart[0].current_dir[1] = 0;
    slang.will_dir_head[0] = 1;
    slang.will_dir_head[1] = 0;

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    last_time = SDL_GetTicks();

    for (int count = 0; count < slang.lengte; count++)
    {
        slang.staart[count].rect.x += slang.staart[count].current_dir[0] * slang.speed;
        slang.staart[count].rect.y += slang.staart[count].current_dir[1] * slang.speed;
    }

    if ((int)(slang.staart[0].rect.x - 2) % 80 == 0 && (int)(slang.staart[0].rect.y - 2) % 80 == 0)
    {
        for (int count = slang.lengte - 1; count >= 1; count--)
        {
            slang.staart[count].current_dir[0] = slang.staart[count - 1].current_dir[0];
            slang.staart[count].current_dir[1] = slang.staart[count - 1].current_dir[1];
        }

        memcpy(slang.staart[0].current_dir, slang.will_dir_head, sizeof(slang.staart[0].current_dir));
    }

    int hoofd_x = slang.staart[0].rect.x - 2; int hoofd_w = slang.staart[0].rect.w + 4;
    int hoofd_y = slang.staart[0].rect.y - 2; int hoofd_h = slang.staart[0].rect.h + 4;
    if (hoofd_x <= appel.x + appel.w - 2 &&
        hoofd_x + hoofd_w >= appel.x + 2 &&
        hoofd_y <= appel.y + appel.h - 2 &&
        hoofd_y + hoofd_h >= appel.y + 2)
    {
        appel.x = (int)SDL_rand(8) * 80 + 2;
        appel.y = (int)SDL_rand(10) * 80 + 2;

        slang.lengte++;
        slang.staart = SDL_realloc(slang.staart, slang.lengte * sizeof(blocks));
        slang.staart[slang.lengte - 1].rect = (SDL_FRect){
            .x = slang.staart[slang.lengte - 2].rect.x,
            .y = slang.staart[slang.lengte - 2].rect.y,
            .w = 76,
            .h = 76,
        };

        slang.staart[slang.lengte - 1].rect.x -= slang.staart[slang.lengte - 2].current_dir[0] * slang.speed;
        slang.staart[slang.lengte - 1].rect.y -= slang.staart[slang.lengte - 2].current_dir[1] * slang.speed;

        slang.staart[slang.lengte - 1].current_dir[0] = 0;
        slang.staart[slang.lengte - 1].current_dir[1] = 0;
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

    SDL_RenderPresent(Renderer);

    current_time = SDL_GetTicks();
    unsigned long long deltaTime = current_time - last_time;
    if (deltaTime <= FPS_TARGET)
    {
        SDL_Delay(FPS_TARGET - deltaTime);
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT)
        return SDL_APP_SUCCESS;
    
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

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    return;
}