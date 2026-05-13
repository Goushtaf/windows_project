#ifndef UTILS_H
#define UTILS_H 

#include <SDL2/SDL.h>
typedef struct{
    int x, y;
} pixelPos;


void Global_to_Local(int* objX, int* objY, const pixelPos* windowPos);

void Local_to_Global(int* objX, int* objY, const pixelPos* windowPos);
#endif
