#include "slang.h"

struct slang slang;

void set_slang_speed(char speed)
{
    if (speed == '1') { slang.speed = 4; }
    else if (speed == '3') { slang.speed = 8; }
    else { slang.speed = 5; }
}

void slang_reset()
{
    slang.x = 4; slang.y = 0;
    slang.lengte = 1;
    slang.staart = SDL_malloc(sizeof(blocks));
    slang.staart[0].rect = (SDL_FRect){
        .x = 2 + 80 * 4,
        .y = 2,
        .w = 76,
        .h = 76,
    };
    slang.staart[0].current_dir[0] = 1;
    slang.staart[0].current_dir[1] = 0;
    slang.will_dir_head[0] = 1;
    slang.will_dir_head[1] = 0;
}

bool slang_raakt_rand()
{
    if ((int)slang.staart[0].rect.x < 2 ||
        (int)slang.staart[0].rect.y < 2 ||
        (int)slang.staart[0].rect.w + (int)slang.staart[0].rect.x > 638 ||
        (int)slang.staart[0].rect.h + (int)slang.staart[0].rect.y > 798)
        return true;
    
    return false;       
}

void slang_wordt_langer()
{
    // terug rekenen, is onhandig
    int new_x = slang.x; int new_y = slang.y;
    for (int count = 1; count < slang.lengte; count++)
    {
        new_x -= slang.staart[count].current_dir[0];
        new_y -= slang.staart[count].current_dir[1];
    }

    slang.lengte++;
    slang.staart = SDL_realloc(slang.staart, slang.lengte * sizeof(blocks));
    slang.staart[slang.lengte - 1].rect = (SDL_FRect){
        .x = new_x * 80 + 2,
        .y = new_y * 80 + 2,
        .w = 76,
        .h = 76,
    };

    slang.staart[slang.lengte - 1].current_dir[0] = 0;
    slang.staart[slang.lengte - 1].current_dir[1] = 0;
}

void slang_beweeg()
{
    for (int count = 0; count < slang.lengte; count++)
    {
        slang.staart[count].rect.x += slang.staart[count].current_dir[0] * slang.speed;
        slang.staart[count].rect.y += slang.staart[count].current_dir[1] * slang.speed;
    }
}