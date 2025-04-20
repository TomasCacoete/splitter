#ifndef HOME_PAGE_H
#define HOME_PAGE_H

#include <SDL2/SDL.h>
#include "../../include/clayman.hpp"

#include "../splitter.hpp"

Clay_RenderCommandArray homePage(SplitterData* splitterData);
Clay_RenderCommandArray pdfSplitterPage(SplitterData* splitterData);

#endif