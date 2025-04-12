#include <SDL2/SDL.h>
#include "../../include/clayman.hpp"

#include "../splitter.hpp"
#include "../styles/styles.hpp"

void homepageCardComponent(SDL_Surface* img, Clay_String text){

    CLAY({.id = CLAY_SID(text),
        .layout = {
            .sizing = {
                .width = CLAY_SIZING_FIT(),
                .height = CLAY_SIZING_GROW(0),
            },
            .padding = { .left = 32, .right = 32, .top = 24, .bottom = 24 },
            .childGap = 24,
            .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
            .layoutDirection = CLAY_TOP_TO_BOTTOM
        },
        .backgroundColor = {255,255,0,255}
    }){

        CLAY_TEXT(text, CLAY_TEXT_CONFIG({ .textColor = font_color, .fontId = FONT_BOLD_40 }));
    }
}

Clay_RenderCommandArray homePage(SplitterData* splitterData){
    Clay_BeginLayout();

    CLAY({.id = CLAY_ID("homePage"),
        .layout = {
            .sizing = {
                .width = CLAY_SIZING_GROW(0),
                .height = CLAY_SIZING_GROW(0),
            },
            .padding = { .left = 32, .right = 32, .top = 32, .bottom = 80 },
            .childGap = 60,
            .childAlignment = { .x = CLAY_ALIGN_X_CENTER },
            .layoutDirection = CLAY_TOP_TO_BOTTOM
        },
    }){
        //header
        CLAY({.id = CLAY_ID("header"),
            .layout = {
                .sizing = {
                    .width = CLAY_SIZING_GROW(0),
                    .height = CLAY_SIZING_FIT(),
                },
                .childGap = 32,
                .childAlignment = { .y = CLAY_ALIGN_Y_CENTER }
            },
        }){
            CLAY({
                .id = CLAY_ID("logo"),
                .layout = {
                    .sizing = {
                        .width = (float)splitterData->logo->w,
                        .height = (float)splitterData->logo->h
                    }
                },
                .image = { .imageData = splitterData->logo, .sourceDimensions = {(float)splitterData->logo->w, (float)splitterData->logo->h} }
            }){}
    
            CLAY_TEXT(CLAY_STRING("Splitter"), CLAY_TEXT_CONFIG({ .textColor = font_color, .fontId = FONT_BOLD_40 }));
        }

        CLAY_TEXT(CLAY_STRING("Olá! O que pretendes fazer?"), CLAY_TEXT_CONFIG({ .textColor = font_color, .fontId = FONT_40 }));

        CLAY({.id = CLAY_ID("cardContainer"),
            .layout = {
                .sizing = {
                    .width = CLAY_SIZING_FIT(),
                    .height = CLAY_SIZING_GROW(0),
                },
                .childGap = 64,
            },
        }){

            homepageCardComponent(nullptr, CLAY_STRING("Boas"));
            homepageCardComponent(nullptr, CLAY_STRING("Boass"));
        }
    };

    Clay_RenderCommandArray renderCommands = Clay_EndLayout();
    return renderCommands;
}