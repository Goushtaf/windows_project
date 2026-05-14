#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "utils.h"


#define WIDTH 800
#define HEIGHT 600
#define NBOFWINDOWS 5


int main(void){
    SDL_Init(SDL_INIT_VIDEO);
    srand(time(NULL));
    
    SDL_Event event;
    bool running = true;
    
    SDL_DisplayMode displayMode;
    
    if (SDL_GetDesktopDisplayMode(0, &displayMode) != 0){
        perror("Getting displayMode failed");
        return 1;
    } else {
        printf("Screen width=%d, height=%d\n", displayMode.w, displayMode.h);
    }
    SDL_Window** windowArray = calloc(NBOFWINDOWS, sizeof(SDL_Window*));
    SDL_Renderer** rendererArray = calloc(NBOFWINDOWS, sizeof(SDL_Renderer*));
    for (size_t i = 0; i < NBOFWINDOWS; ++i){
        char str[20];
        sprintf(str, "Window N.%zu", i);
        windowArray[i] = Create_Window(displayMode.w, displayMode.h, str);
        rendererArray[i] = SDL_CreateRenderer(windowArray[i], -1, SDL_RENDERER_ACCELERATED);
    }

    int global_rect_x = displayMode.w/2;
    int global_rect_y = displayMode.h/2;
    
    pixelPos windowposArray[NBOFWINDOWS] = {0};

    while(running){
        while (SDL_PollEvent(&event)){
            switch (event.type){
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_WINDOWEVENT:
                    if (event.window.event == SDL_WINDOWEVENT_MOVED) {
                        Uint32 movedWindowID = event.window.windowID;
                        
                        for (size_t i = 0; i < NBOFWINDOWS; ++i) {
                            if (SDL_GetWindowID(windowArray[i]) == movedWindowID) {
                                windowposArray[i].x = event.window.data1;
                                windowposArray[i].y = event.window.data2;
                                break;
                            }
                        }
                    }
                    break;
            }
        }
       
        for (size_t i = 0; i < NBOFWINDOWS; ++i){
            SDL_Rect render_rect = {global_rect_x, global_rect_y, 500, 500};

            Global_to_Local(&render_rect.x, &render_rect.y, &windowposArray[i]);

            SDL_SetRenderDrawColor(rendererArray[i], 0, 0, 0, 200);
            SDL_RenderClear(rendererArray[i]);

            SDL_SetRenderDrawColor(rendererArray[i], 255, 255, 255, 255);
            SDL_RenderFillRect(rendererArray[i], &render_rect);
            SDL_RenderPresent(rendererArray[i]);
        }
    }

    Destroy_Windows_And_Renderers(windowArray, rendererArray, NBOFWINDOWS);
    SDL_Quit();
    return 0;
}
