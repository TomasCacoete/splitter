#include "../../include/clayman.hpp"

#include "../splitter.hpp"
#include "../styles/styles.hpp"
#include "../elements/elements.hpp"

#include <windows.h>
#include <commdlg.h>

bool OpenPDFFileDialog(char* outPath, DWORD outPathSize) {
    OPENFILENAME ofn = { 0 };
    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;  // or pass your SDL window handle here if needed
    ofn.lpstrFilter = "PDF Files\0*.pdf\0";
    ofn.lpstrFile = outPath;
    ofn.nMaxFile = outPathSize;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    return GetOpenFileName(&ofn);
}

void sizeInput(SplitterData* splitterData){
    CLAY({.id = CLAY_ID_LOCAL("splitSizeContainer"),
        .layout = {
            .sizing = {
                .width = CLAY_SIZING_GROW(0),
            },
            .childGap = 4,
            .layoutDirection = CLAY_TOP_TO_BOTTOM,
        }
    }){
        CLAY_TEXT(CLAY_STRING("Tamanho"), CLAY_TEXT_CONFIG({ .textColor = font_color, .fontId = FONT_BOLD_24 }));

        CLAY({.id = CLAY_ID_LOCAL("label"),
            .layout = {
                .sizing = {
                    .width = CLAY_SIZING_GROW(0),
                },
                .padding = { 16, 16, 8, 8 },
            },
            .cornerRadius = { 20, 20, 20, 20 },
            .border = { .color = font_color, .width = { 3, 3, 3, 3, 0 } }
        }){
            Clay_String aux = {.length = (int32_t)strlen(splitterData->pdfPageData.sizeBuffer), .chars = splitterData->pdfPageData.sizeBuffer};
            CLAY_TEXT(aux, CLAY_TEXT_CONFIG({ .textColor = font_color, .fontId = FONT_BOLD_24 }));
            
            CLAY({.id = CLAY_ID_LOCAL("spacing"),
                .layout = {
                    .sizing = {
                        .width = CLAY_SIZING_GROW(0),
                    },
                }
            }){}

            CLAY_TEXT(CLAY_STRING("MB"), CLAY_TEXT_CONFIG({ .textColor = font_color, .fontId = FONT_BOLD_24 }));
        }
    }
}

Clay_RenderCommandArray pdfSplitterPage(SplitterData* splitterData){
    Clay_BeginLayout();

    CLAY({.id = CLAY_ID("pdfSplitterPage"),
        .layout = {
            .sizing = {
                .width = CLAY_SIZING_GROW(0),
                .height = CLAY_SIZING_GROW(0),
            },
        },
    }){
        CLAY({.id = CLAY_ID_LOCAL("leftSection"),
            .layout = {
                .sizing = {
                    .width = CLAY_SIZING_GROW(0),
                    .height = CLAY_SIZING_GROW(0),
                },
                .padding = CLAY_PADDING_ALL(40),
                .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
            },
        }){
            goBackButton(splitterData);

            CLAY({.id = CLAY_ID_LOCAL("addPdfButton"),
                .layout = {
                    .padding = CLAY_PADDING_ALL(20),
                    .childGap = 20,
                },
                .backgroundColor = orange_button_active_color,
                .cornerRadius = CLAY_CORNER_RADIUS(20),
            }){
                Clay_OnHover([](Clay_ElementId elementId, Clay_PointerData pointerData, intptr_t userData){
                    if(pointerData.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME){
                        SplitterData* data = reinterpret_cast<SplitterData*>(userData);

                        char filePath[MAX_PATH] = "";
                        if(OpenPDFFileDialog(filePath, MAX_PATH)){
                            printf("Selected file: %s\n", filePath);
                            // Load or process the PDF however you want
                        }
                    }
                }, reinterpret_cast<intptr_t>(splitterData));

                CLAY_TEXT(CLAY_STRING("Adiciona um PDF"), CLAY_TEXT_CONFIG({ .textColor = font_color, .fontId = FONT_BOLD_24 }));

                CLAY_TEXT(CLAY_STRING("+"), CLAY_TEXT_CONFIG({ .textColor = font_color, .fontId = FONT_BOLD_24 }));
            }
        }

        CLAY({.id = CLAY_ID_LOCAL("rightSection"),
            .layout = {
                .sizing = {
                    .width = CLAY_SIZING_FIXED(296),
                    .height = CLAY_SIZING_GROW(0),
                },
                .padding = CLAY_PADDING_ALL(40),
                .childGap = 16,
                .childAlignment = { .x = CLAY_ALIGN_X_CENTER },
                .layoutDirection = CLAY_TOP_TO_BOTTOM,
            },
            .cornerRadius = { 20, 0, 20, 0 },
            .border = { .color = font_color, .width = { 3, 3, 3, 3, 0 } }
        }){
            CLAY_TEXT(CLAY_STRING("PDF Splitter"), CLAY_TEXT_CONFIG({ .textColor = font_color, .fontId = FONT_BOLD_40 }));

            CLAY({.id = CLAY_ID_LOCAL("paramenters"),
                .layout = {
                    .sizing = {
                        .width = CLAY_SIZING_GROW(0),
                        .height = CLAY_SIZING_GROW(0),
                    },
                    .layoutDirection = CLAY_TOP_TO_BOTTOM,
                }
            }){
                sizeInput(splitterData);
            }

            CLAY({.id = CLAY_ID_LOCAL("splitPdfButton"),
                .layout = {
                    .sizing = {
                        .width = CLAY_SIZING_GROW(0),
                    },
                    .padding = CLAY_PADDING_ALL(20),
                    .childAlignment = { .x = CLAY_ALIGN_X_CENTER }
                },
                .backgroundColor = orange_button_disabled_color,
                .cornerRadius = CLAY_CORNER_RADIUS(20),
            })

            CLAY_TEXT(CLAY_STRING("Split PDF"), CLAY_TEXT_CONFIG({ .textColor = font_color, .fontId = FONT_BOLD_24 }));
        }
    }

    Clay_RenderCommandArray renderCommands = Clay_EndLayout();
    return renderCommands;
}