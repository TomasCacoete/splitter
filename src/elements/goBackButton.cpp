#include "../../include/clayman.hpp"

#include "../splitter.hpp"
#include "../styles/styles.hpp"

void goBackButton(SplitterData* splitterData){
    CLAY({.id = CLAY_ID_LOCAL("goBackButton"),
        .layout = {
            .sizing = {
                .width = CLAY_SIZING_FIXED(40),
                .height = CLAY_SIZING_FIXED(40),
            },
            .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
        },
        .cornerRadius = CLAY_CORNER_RADIUS(24),
        .floating = { .offset = {40, 40}, .attachTo = CLAY_ATTACH_TO_PARENT },
        .border = { .color = Clay_Hovered() ? hover_color : font_color, .width = { 3, 3, 3, 3, 0 } }
    }){
        Clay_OnHover([](Clay_ElementId elementId, Clay_PointerData pointerData, intptr_t userData){
            if(pointerData.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME){
                SplitterData* data = reinterpret_cast<SplitterData*>(userData);
                data->currentPage = homePageId;
            }
        }, reinterpret_cast<intptr_t>(splitterData));

        CLAY_TEXT(CLAY_STRING("<"), CLAY_TEXT_CONFIG({ .textColor = font_color, .fontId = FONT_BOLD_24 }));
    }
}