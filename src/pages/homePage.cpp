#include <SDL2/SDL.h>
#include "../../include/clayman.hpp"

#include "../splitter.hpp"
#include "../styles/styles.hpp"

void homepageCardComponent(SplitterData* splitterData, SDL_Surface* img, Clay_String text){

    CLAY({.id = CLAY_SID(text),
        .layout = {
            .sizing = {
                .width = CLAY_SIZING_FIXED(184),
                .height = CLAY_SIZING_GROW(0, 216),
            },
            .padding = { .left = 32, .right = 32, .top = 24, .bottom = 24 },
            .childGap = 24,
            .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
            .layoutDirection = CLAY_TOP_TO_BOTTOM
        },
        .cornerRadius = CLAY_CORNER_RADIUS(20),
        .border = { .color = Clay_Hovered() ? hover_color : font_color, .width = { 3, 3, 3, 3, 0 } }
    }){
        Clay_OnHover([](Clay_ElementId elementId, Clay_PointerData pointerData, intptr_t userData){
            if(pointerData.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME){
                SplitterData* data = reinterpret_cast<SplitterData*>(userData);
                data->currentPage = pdfSplitterPageId;
            }
        }, reinterpret_cast<intptr_t>(splitterData));

        CLAY({.id = CLAY_ID_LOCAL("cardImage"),
            .layout = {
                .sizing = {
                    .width = (float)img->w,
                    .height = (float)img->h
                }
            },
            .image = { .imageData = img, .sourceDimensions = {(float)img->w, (float)img->h} }
        }){};

        CLAY_TEXT(text, CLAY_TEXT_CONFIG({ .textColor = font_color, .fontId = FONT_BOLD_24, .textAlignment = CLAY_TEXT_ALIGN_CENTER }));
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
        CLAY({.id = CLAY_ID_LOCAL("header"),
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
                .id = CLAY_ID_LOCAL("logo"),
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

        CLAY({.id = CLAY_ID_LOCAL("cardsContainer"),
            .layout = {
                .sizing = {
                    .width = CLAY_SIZING_FIT(),
                    .height = CLAY_SIZING_GROW(0),
                },
                .childGap = 64,
                .childAlignment = { .y = CLAY_ALIGN_Y_CENTER }
            },
        }){
            homepageCardComponent(splitterData, splitterData->pdfImage, CLAY_STRING("Cortar um PDF"));
            homepageCardComponent(splitterData, splitterData->videoImage, CLAY_STRING("Cortar um vídeo"));
        }
    };

    Clay_RenderCommandArray renderCommands = Clay_EndLayout();
    return renderCommands;
}