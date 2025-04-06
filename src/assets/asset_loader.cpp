#include <SDL2/SDL_image.h>
#include "../splitter.hpp"

void load_assets(SplitterData* splitterData){
    splitterData->logo = IMG_Load("assets/images/logo.png");
    if(!splitterData->logo){
        fprintf(stderr, "Error: Couldn't read logo.png: %s\n", IMG_GetError());
    }
}