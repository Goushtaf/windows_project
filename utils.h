#ifndef UTILS_H
#define UTILS_H
#define WIDTH 800
#define HEIGHT 600
#include "SDL2/SDL.h"

typedef struct{
    int x,y;
}pixelPos;
  
void Local_to_Global(int* objX, int* objY, const pixelPos* windowPos);
void Global_to_Local(int* objX, int* objY, const pixelPos* windowPos);

SDL_Window* Create_Window(int screenWidth, int screenHeight, char* title);
void Destroy_Windows_And_Renderers(SDL_Window** windowArray, SDL_Renderer** rendererArray, size_t length);
#endif
