#include "utils.h"
#include <SDL2/SDL_video.h>
void Local_to_Global(int* objX, int* objY, const pixelPos* windowPos){
    *objX += windowPos->x;
    *objY += windowPos->y;
}
void Global_to_Local(int* objX, int* objY, const pixelPos* windowPos){
    *objX -= windowPos->x;
    *objY -= windowPos->y;
}

SDL_Window* Create_Window(int screenWidth, int screenHeight, char* title){
    int x = rand() % (screenWidth + 1);
    int y = rand() % (screenHeight + 1);
    printf("Window created with pos x=%d,y=%d\n",x, y);
    SDL_Window* window = SDL_CreateWindow(title, x, y, WIDTH, HEIGHT, 0);
    SDL_SetWindowBordered(window, SDL_TRUE);
    return window;
}
void Destroy_Windows_And_Renderers(SDL_Window** windowArray, SDL_Renderer** rendererArray, size_t length){
    for(size_t i = 0; i < length; ++i){
        SDL_DestroyRenderer(rendererArray[i]);
        SDL_DestroyWindow(windowArray[i]);
    }
}
