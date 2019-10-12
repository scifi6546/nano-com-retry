#ifndef shader_H
#define shader_H
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <string>

#include "render_target.h"

//int shaderInit(); 
int checkShaderError(GLuint shader, GLuint flag, bool isProgram, std::string errorMessage);

/*
NOT TESTED
creates shader specified by text and then applies changes to render target
element 0 of text is vertex shader string
element 1 of text is fragment shader string
*/
void createShaderT(std::vector<std::string> text,render_target &target);

/*
NOT TESTED
Sends mat4 to uniform specified by name. Uses program in render_target
*/
void sendMat4(const std::string name, glm::mat4 mat_in,
    render_target program);
/*
NOT TESTED
sends vec3 to uniform specified by name. Uses program in render_target
*/
void sendVec3(const std::string name,const glm::vec3 vec3_in,
    const render_target in);

/*
NOT TESTED
sends GLfloat to uniform specified by name. uses program in render_target
*/
void sendGLfloat(const std::string name,const GLfloat float_in,
    const render_target in);
void bind();
//void sendCamera(glm::mat4 cam);
//void sendTranslate(glm::mat4 trans);
//void sendLook(glm::mat4 look);
//void setTexture(int unit);
//void sendAmbient(glm::vec3 color,GLfloat intensity,
//    glm::vec3 sun_pos,GLfloat sun_intensity,glm::vec3 sun_color);
//void sendCamMatBuffer(glm::mat4 in);

//void useGameShader();//uses the game world shaders
void useBufferShader();//activates the frame buffer shaders

//NOT TESTED!!!!!
void useShader(render_target target);//uses shader specified in render_target
//void bindGameShader();
//void bindBufferShader();
#endif