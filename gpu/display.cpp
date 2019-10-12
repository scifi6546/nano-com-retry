#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "display.h"
#include "error.h"
SDL_Window *win;
SDL_GLContext context;

int initDisplay(int width, int height,std::string title){
    printf("displayed\n");
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE,8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
 //getError();

    win = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_OPENGL);
    context=SDL_GL_CreateContext(win);
     getError();
    GLenum status = glewInit();
    if(status != GLEW_OK){
        printf("glew did not init");
    }
    getError();
    glEnable(GL_DEPTH_TEST);  

    return 0;
}
void updateDisplay(){
    
    SDL_GL_SwapWindow(win); 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void delDisplay(){
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
void clearDisplay(float r, float g, float b, float a){
    glClearColor(r,g,b,1.0f);
    glClear(GL_COLOR_BUFFER_BIT); 
}
/*
SDL_Event getEvent(){
    SDL_Event out;
    SDL_PollEvent(&out);
    return out;
}
*/
