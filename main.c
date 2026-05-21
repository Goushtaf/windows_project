#include <stdlib.h>
#include <stdbool.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <time.h>
#include "utils.h"


#define WIDTH 800
#define HEIGHT 600
#define NBOFWINDOWS 5


int main(void){
    glfwInit();
    srand(time(NULL));
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    
    bool running = true;
     const GLFWvidmode* mode = glfwGetVideoMode(monitor);   

    
    printf("Screen width=%d, height=%d\n", mode->width, mode->height);
    GLFWwindow** windowArray = calloc(NBOFWINDOWS, sizeof(GLFWwindow*));
    WindowData* windowDataArray = calloc(NBOFWINDOWS, sizeof(WindowData));
    for (size_t i = 0; i < NBOFWINDOWS; ++i){
        char str[20];
        sprintf(str, "Window N.%zu", i);
        windowArray[i] = Create_Window(monitor, mode->width, mode->height, str);
        windowDataArray[i].id = i;
        windowDataArray[i].pos.x = mode->width; 
        windowDataArray[i].pos.y = mode->height; 
        glfwSetWindowUserPointer(windowArray[i], &windowDataArray[i]);
        glfwSetWindowPosCallback(windowArray[i], window_pos_callback);
    }
    int global_rect_x = mode->width/2;
    int global_rect_y = mode->height/2;
    
    pixelPos windowposArray[NBOFWINDOWS] = {0};

    while(running){
        glfwPollEvents();

        for (size_t i = 0; i < NBOFWINDOWS; ++i){
            if (glfwWindowShouldClose(windowArray[i])){
                running = false;
                break;
            }
            glfwMakeContextCurrent(windowArray[i]);
            
            glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            
            glfwSwapBuffers(windowArray[i]);
        }
    }

    Destroy_Windows(windowArray, NBOFWINDOWS);
    return 0;
}
