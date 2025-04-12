#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "../../include/sdl2/clay_renderer_SLD2.h"

#include "../splitter.hpp"
#include "../styles/styles.hpp"

int load_font(SDL2_Font* fonts, const std::string& filename, int size, uint32_t fontId) {
    std::string fullPath = "assets/fonts/" + filename;

    TTF_Font* font = TTF_OpenFont(fullPath.c_str(), size);
    if (!font) {
        fprintf(stderr, "Error: could not load font '%s': %s\n", fullPath.c_str(), TTF_GetError());
        return 1;
    }

    fonts[fontId] = (SDL2_Font){
        .fontId = fontId,
        .font = font,
    };

    return 0;
}

int load_assets(SplitterData* splitterData, SDL2_Font* fonts){
    splitterData->logo = IMG_Load("assets/images/logo.png");
    if(!splitterData->logo){
        fprintf(stderr, "Error: Couldn't read logo.png: %s\n", IMG_GetError());
        return 1;
    }

    //Loading fonts
    if(load_font(fonts, "calibri-regular.ttf", 40, FONT_40) != 0){
        return 1;
    }

    if(load_font(fonts, "calibri-bold.ttf", 40, FONT_BOLD_40) != 0){
        return 1;
    }

    return 0;
}