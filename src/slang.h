#ifndef SLANG_H
#define SLANG_H

#include "engine.h"

typedef struct {
    signed char current_dir[2];
    SDL_FRect rect;
} blocks;

extern struct slang {
    blocks* staart;
    char lengte;
    char speed;
    signed char will_dir_head[2];
};

extern struct slang slang;

void slang_reset();
bool slang_raakt_rand();
void slang_wordt_langer();
void slang_beweeg();

#endif//SLANG_H