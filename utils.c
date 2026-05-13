#include "utils.h"
void Local_to_Global(int* objX, int* objY, const pixelPos* windowPos){
    *objX += windowPos->x;
    *objY += windowPos->y;
}
void Global_to_Local(int* objX, int* objY, const pixelPos* windowPos){
    *objX -= windowPos->x;
    *objY -= windowPos->y;
}
