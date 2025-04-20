#ifndef SPLITTER_H
#define SPLITTER_H

#include <SDL2/SDL.h>

struct pdfSplitterData {
    bool editingSize;
    char sizeBuffer[11];  // 10 digits + 1 null terminator
};

struct SplitterData {
    //Routing
    uint8_t currentPage;

    //homePage
    SDL_Surface* logo;
    SDL_Surface* pdfImage;
    SDL_Surface* videoImage;

    pdfSplitterData pdfPageData;
};

const uint8_t homePageId = 0;
const uint8_t pdfSplitterPageId = 1;

#endif