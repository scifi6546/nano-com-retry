#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "render_target.h"
#include "mesh.h"


const int display_height = 800;
const int display_width = 1000;

int getHeight(){return display_height;}
int getWidth(){return display_width;}
//public functions
//initilizes render manager
void initRender();
//quits rendering
void quitRender_INT();
//draws frame called every frame draw
//reset_mouse tells whether to move mouse to center
void drawFrame(bool reset_mouse);
/*
Buffer Draw Calls
*/
void bufferDrawCalls(RunTimeModel Model,glm::vec3 pos,Texture texture);
/*
Buffer Draw Calls for Gui Layer
*/
void bufferDrawCallsGui(RunTimeModel Model,glm::vec3 pos,Texture texture);
/*
NOT TESTED
sends the camera position (world coordinates) and rotation to the rendering engine 
*/
void sendCamera(glm::vec3 position,float thetax,float thetay);

/*
NOT IMPLEMENTED OR TESTED
Sends world color data to the gpu
*/
void sendAmbientInfo(glm::vec3 color,GLfloat intensity,
    glm::vec3 sun_pos,GLfloat sun_intensity,glm::vec3 sun_color);
/*
Not Tested
Sends position data to the gpu
*/
void sendPos(glm::vec3 pos);
/*
TO ONLY BE USED BY RENDERING CODE
gets pointer to currently bound shader
*/
render_target *getBoundShader();

//private functions
namespace rManager{
    const unsigned int shadow_width = 1024, shadow_height=1024;
    //initilizes frame buffer object and modifies in
    void makeFBO(render_target &in);
    //binds a frame buffer object struct
    void bindFBO(render_target in);
    void RuseShader(render_target &in);
}
#endif
