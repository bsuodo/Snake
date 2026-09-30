#ifndef SLANG_H
#define SLANG_H

#include "engine.h"

typedef struct {
    signed char current_dir[2];
    SDL_FRect rect;
} blocks;

extern struct slang {
    int x, y;
    blocks* staart;
    char lengte;
    char speed;
    signed char will_dir_head[2];
};

extern struct slang slang;

void set_slang_speed(char speed);
void slang_reset();
bool slang_raakt_rand();
void slang_wordt_langer();
void slang_beweeg();

#endif//SLANG_H