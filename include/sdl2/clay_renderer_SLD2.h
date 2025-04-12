#ifndef CLAY_RENDERER_SDL2_H
#define CLAY_RENDERER_SDL2_H

#include <SDL2/SDL_ttf.h>

typedef struct
{
    uint32_t fontId;
    TTF_Font *font;
} SDL2_Font;

#endif