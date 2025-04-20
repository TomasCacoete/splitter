#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../include/clayman.hpp"
#include "../include/sdl2/clay_renderer_SDL2.c"

#include "splitter.hpp"
#include "assets/asset_loader.hpp"
#include "styles/styles.hpp"
#include "pages/pages.hpp"

#include <poppler/cpp/poppler-document.h>

Clay_RenderCommandArray renderPage(SplitterData *splitterData){
    switch(splitterData->currentPage){
        case homePageId:
            return homePage(splitterData);

        case pdfSplitterPageId:
            return pdfSplitterPage(splitterData);
            
        default:
            return homePage(splitterData);
    }
}

void HandleClayErrors(Clay_ErrorData errorData) {
    printf("%s", errorData.errorText.chars);
}

struct ResizeRenderData_ {
    SDL_Window* window;
    int windowWidth;
    int windowHeight;
    SDL_Renderer* renderer;
    SDL2_Font* fonts;
    SplitterData* splitterData;
};
typedef struct ResizeRenderData_ ResizeRenderData;

int resizeRendering(void* userData, SDL_Event* event) {
    ResizeRenderData *actualData = (ResizeRenderData*)userData;
    if (event->type == SDL_WINDOWEVENT && event->window.event == SDL_WINDOWEVENT_EXPOSED) {
        SDL_Window* window          = actualData->window;
        int windowWidth             = actualData->windowWidth;
        int windowHeight            = actualData->windowHeight;
        SDL_Renderer* renderer      = actualData->renderer;
        SDL2_Font* fonts            = actualData->fonts;
        SplitterData* splitterData  = actualData->splitterData;

        SDL_GetWindowSize(window, &windowWidth, &windowHeight);
        Clay_SetLayoutDimensions((Clay_Dimensions) {
            (float)windowWidth,
            (float)windowHeight 
        });

        Clay_RenderCommandArray renderCommands = renderPage(splitterData);
        SDL_SetRenderDrawColor(renderer, background_color.r, background_color.g, background_color.b, background_color.a);
        SDL_RenderClear(renderer);

        Clay_SDL2_Render(renderer, renderCommands, fonts);

        SDL_RenderPresent(renderer);
    }
    return 0;
}

int handlePdfPageTextInput(void* userData, SDL_Event* event) {
    ResizeRenderData *data = (ResizeRenderData*)userData;
    if(data->splitterData->currentPage != 1){
        return 0;
    }

    char* sizeBuffer = data->splitterData->pdfPageData.sizeBuffer;

    if(event->type == SDL_TEXTINPUT){
        const char* txt = event->text.text;

        if (txt[0] >= '0' && txt[0] <= '9' && txt[1] == '\0') {
            if(strlen(sizeBuffer) < sizeof(data->splitterData->pdfPageData.sizeBuffer) - 1){
                strcat(sizeBuffer, txt);
            }
        }
    }

    if (event->type == SDL_KEYDOWN) {
        SDL_Keycode key = event->key.keysym.sym;

        if (key == SDLK_BACKSPACE) {
            size_t len = strlen(sizeBuffer);
            if (len > 0) {
                sizeBuffer[len - 1] = '\0';
            }
        }
    }

    return 0;
}

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Error: could not initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    if (TTF_Init() < 0) {
        fprintf(stderr, "Error: could not initialize TTF: %s\n", TTF_GetError());
        return 1;
    }
    
    if (IMG_Init(IMG_INIT_PNG) < 0) {
        fprintf(stderr, "Error: could not initialize IMG: %s\n", IMG_GetError());
        return 1;
    }
    
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
  
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl"); //for antialiasing
    window = SDL_CreateWindow("SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4); //for antialiasing
    bool enableVsync = true;
    if(enableVsync){
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); //"SDL_RENDERER_ACCELERATED" is for antialiasing
    
    } else{
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    }
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); //for alpha blending

    uint64_t totalMemorySize = Clay_MinMemorySize();
    Clay_Arena clayMemory = Clay_CreateArenaWithCapacityAndMemory(totalMemorySize, malloc(totalMemorySize));

    int windowWidth = 0;
    int windowHeight = 0;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    Clay_Initialize(clayMemory, (Clay_Dimensions) {
        (float)windowWidth,
        (float)windowHeight
    },(Clay_ErrorHandler) { HandleClayErrors });

    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    double deltaTime = 0;

    SDL2_Font fonts[3];

    SplitterData splitterData;
    load_assets(&splitterData, fonts);
    splitterData.currentPage = homePageId;
    splitterData.pdfPageData.editingSize = false;
    strcpy(splitterData.pdfPageData.sizeBuffer, "20");
    

    ResizeRenderData userData = {
        window, // SDL_Window*
        windowWidth, // int
        windowHeight, // int
        renderer, // SDL_Renderer*
        fonts, // SDL2_Font[1]
        &splitterData
    };

    
    Clay_SetMeasureTextFunction(SDL2_MeasureText, &fonts);

    // add an event watcher that will render the screen while youre dragging the window to different sizes
    SDL_AddEventWatch(resizeRendering, &userData);
    SDL_AddEventWatch(handlePdfPageTextInput, &userData);

    SDL_StartTextInput();

    while (true) {
        Clay_Vector2 scrollDelta = {};
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: {
                    goto quit;
                }

                case SDL_MOUSEWHEEL: {
                    scrollDelta.x = event.wheel.x;
                    scrollDelta.y = event.wheel.y;
                    break;
                }
            }
        }
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();
        deltaTime = (double)((NOW - LAST)*1000 / (double)SDL_GetPerformanceFrequency() );
        //printf("%f\n", deltaTime);

        double fps = 1000.0 / deltaTime;
        char title[128];
        snprintf(title, sizeof(title), "FPS: %.2f", fps);
        SDL_SetWindowTitle(window, title);

        int mouseX = 0;
        int mouseY = 0;
        Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);
        Clay_Vector2 mousePosition = (Clay_Vector2){ (float)mouseX, (float)mouseY };
        Clay_SetPointerState(mousePosition, mouseState & SDL_BUTTON(1));
        Clay_UpdateScrollContainers(
            true,
            (Clay_Vector2) { scrollDelta.x, scrollDelta.y },
            deltaTime
        );
        
        SDL_GetWindowSize(window, &windowWidth, &windowHeight);
        Clay_SetLayoutDimensions((Clay_Dimensions) {
            (float)windowWidth, (float)windowHeight
        });

        Clay_RenderCommandArray renderCommands = renderPage(&splitterData);
        SDL_SetRenderDrawColor(renderer, background_color.r, background_color.g, background_color.b, background_color.a);
        SDL_RenderClear(renderer);

        Clay_SDL2_Render(renderer, renderCommands, fonts);

        SDL_RenderPresent(renderer);
    }
    quit:
        SDL_StopTextInput();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();
        return 0;
}