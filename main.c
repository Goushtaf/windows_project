#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include "utils.h"

#define WIDTH 800
#define HEIGHT 600

int main(void){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow(
            "boids (SDL2)",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            WIDTH, HEIGHT, 0
            );
    SDL_DisplayMode displayMode;
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Event event;
    bool running = true;
    
    pixelPos windowpos = {0, 0}; 
    
    if (SDL_GetDesktopDisplayMode(0, &displayMode) != 0){
        perror("Getting displayMode failed");
        return 1;
    } else {
        printf("Screen width=%d, height=%d\n", displayMode.w, displayMode.h);
    }

    int global_rect_x = displayMode.w/2;
    int global_rect_y = displayMode.h/2;

    while(running){
        while (SDL_PollEvent(&event)){
            switch (event.type){
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_WINDOWEVENT:
                    switch (event.window.event){
                        case SDL_WINDOWEVENT_MOVED:
                            windowpos.x = event.window.data1;
                            windowpos.y = event.window.data2;
                            printf("Window moved to x=%d;y=%d\n", windowpos.x, windowpos.y);
                            break;
                    }
                    break;
            }
        }
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_Rect render_rect = {global_rect_x, global_rect_y, 100, 100};

        Global_to_Local(&render_rect.x, &render_rect.y, &windowpos);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &render_rect);
        SDL_RenderPresent(renderer);
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
