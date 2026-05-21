#include "utils.h"
#include <GLFW/glfw3.h>
void Local_to_Global(int* objX, int* objY, const pixelPos* windowPos){
    *objX += windowPos->x;
    *objY += windowPos->y;
}
void Global_to_Local(int* objX, int* objY, const pixelPos* windowPos){
    *objX -= windowPos->x;
    *objY -= windowPos->y;
}

GLFWwindow* Create_Window(GLFWmonitor* monitor, int screenWidth, int screenHeight, char* title){
    int x = rand() % (screenWidth + 1);
    int y = rand() % (screenHeight + 1);
    printf("Window created with pos x=%d,y=%d\n",x, y);
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, title, NULL, NULL);
    glfwSetWindowMonitor(window, monitor, x, y, WIDTH, HEIGHT, REFRESHRATE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    return window;
}
void Destroy_Windows(GLFWwindow** windowArray, size_t length){
    for(size_t i = 0; i < length; ++i){
        glfwDestroyWindow(windowArray[i]);
    }
}
void window_pos_callback(GLFWwindow* window, int xpos, int ypos) {
    WindowData* data = (WindowData*) glfwGetWindowUserPointer(window);
    if (data) {
        data->pos.x = xpos;
        data->pos.y = ypos;
        printf("Fenêtre %d déplacée en x:%d, y:%d\n", data->id, xpos, ypos);
    }
}
