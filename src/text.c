#include "text.h"

SDL_Texture* alfaDown[26] = {0};
SDL_Texture* alfaUp[26] = {0};
SDL_Texture* num[10] = {0};

void TEXT_init()
{
    for (int count = 0; count < 26; count++)
    {
        char letterofnum[2] = {97 + count, '\0'};
        SDL_Surface* genfont = TTF_RenderText_Blended(font, letterofnum, 1, (SDL_Color){255, 255, 255, 255});
        alfaDown[count] = SDL_CreateTextureFromSurface(Renderer, genfont);
        SDL_DestroySurface(genfont);
    }
    for (int count = 0; count < 26; count++)
    {
        char letterofnum[2] = {65 + count, '\0'};
        SDL_Surface* genfont = TTF_RenderText_Blended(font, letterofnum, 1, (SDL_Color){255, 255, 255, 255});
        alfaUp[count] = SDL_CreateTextureFromSurface(Renderer, genfont);
        SDL_DestroySurface(genfont);
    }

    // num
    for (int count = 0; count < 10; count++)
    {
        char letterofnum[2] = {48 + count, '\0'};
        SDL_Surface* genfont = TTF_RenderText_Blended(font, letterofnum, 1, (SDL_Color){255, 255, 255, 255});
        num[count] = SDL_CreateTextureFromSurface(Renderer, genfont);
        SDL_DestroySurface(genfont);
    }
}

void TEXT_rendertext(char* text, int x, int y, TEXT_size grootte, bool center)
{
    int lengte = strlen(text);

    int width = 0;
    for (int count = 0; count < strlen(text); count++)
    {
        if (text[count] == ' ') {width+=8;}
        else if (text[count] <= 90) width += alfaUp[text[count] - 65]->w;
        else width += alfaDown[text[count] - 97]->w;
    }

    SDL_FRect rect = {
        .x = x - width / 2,
        .y = y - 32 / 2,
        .h = alfaUp[0]->h
    };

    for (int count = 0; count < strlen(text); count++)
    {
        if (text[count] == ' ') {rect.x += 8;}
        else if (text[count] > 90)
        {
            rect.w = alfaDown[text[count] - 97]->w;
            SDL_RenderTexture(Renderer, alfaDown[text[count] - 97], NULL, &rect);
            rect.x += alfaDown[text[count] - 97]->w;
        }
        else {
            rect.w = alfaUp[text[count] - 65]->w;
            SDL_RenderTexture(Renderer, alfaUp[text[count] - 65], NULL, &rect);
            rect.x += alfaUp[text[count] - 65]->w;
        }
    }
}

void TEXT_renderint(int nummer, int x, int y, TEXT_size grootte, bool center)
{
    char text[8];
    sprintf(text, "%d", nummer);

    int width = 0;
    for (int count = 0; count < strlen(text); count++)
    {
        width += num[text[count] - 48]->w;
    }
    
    SDL_FRect rect = {
        .x = x - width / 2,
        .y = y - 32 / 2,
        .h = num[0]->h
    };

    for (int count = 0; count < strlen(text); count++)
    {
        rect.w = num[text[count] - 48]->w;
        SDL_RenderTexture(Renderer, num[text[count] - 48], NULL, &rect);
        rect.x += num[text[count] - 48]->w;
    }
}