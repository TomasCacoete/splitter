#include <SDL2/SDL.h>
#include "../../include/clayman.hpp"

#include "../splitter.hpp"

Clay_RenderCommandArray homePage(SplitterData* splitterData){
    Clay_BeginLayout();

    CLAY({
        .id = CLAY_ID("Header"),
        .layout = {
            .sizing = {
                .width = CLAY_SIZING_GROW(0),
                .height = CLAY_SIZING_FIXED(200),
            }
        },
        .backgroundColor = { 16, 14, 35, 255 },
        .cornerRadius = CLAY_CORNER_RADIUS(8)

    }){
        CLAY({
            .id = CLAY_ID("Logo"),
            .layout = {
                .sizing = {
                    .width = CLAY_SIZING_FIXED(102),
                    .height = CLAY_SIZING_FIXED(108)
                }
            },
            .image = { .imageData = splitterData->logo, .sourceDimensions = {102, 108} }
        }){}
    }

    Clay_RenderCommandArray renderCommands = Clay_EndLayout();
    return renderCommands;
}