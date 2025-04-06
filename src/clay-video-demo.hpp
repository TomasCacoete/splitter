#ifndef CLAY_VIDEO_DEMO_H
#define CLAY_VIDEO_DEMO_H

#include "../clayman.hpp"

const int FONT_ID_BODY_16 = 0;

void RenderHeaderButton(Clay_String text);
void RenderDropdownMenuItem(Clay_String text);

typedef struct {
    Clay_String title;
    Clay_String contents;
} Document;

typedef struct {
    Document *documents;
    uint32_t length;
} DocumentArray;

typedef struct {
    intptr_t offset;
    intptr_t memory;
} ClayVideoDemo_Arena;

typedef struct {
    int32_t selectedDocumentIndex;
    ClayVideoDemo_Arena frameArena;
} ClayVideoDemo_Data;

typedef struct {
    int32_t requestedDocumentIndex;
    int32_t* selectedDocumentIndex;
} SidebarClickData;

void HandleSidebarInteraction(
    Clay_ElementId elementId,
    Clay_PointerData pointerData,
    intptr_t userData
);

ClayVideoDemo_Data ClayVideoDemo_Initialize();
Clay_RenderCommandArray ClayVideoDemo_CreateLayout(ClayVideoDemo_Data *data);


#endif // CLAY_VIDEO_DEMO_H