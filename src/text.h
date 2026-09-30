#ifndef TEXT_H
#define TEXT_H

#include "engine.h"

typedef enum
{
    DEFAULT,
} TEXT_size;

void TEXT_init();
void TEXT_renderint(int nummer, int x, int y, TEXT_size grootte, bool center);

#endif//TEXT_H