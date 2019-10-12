#ifndef camera_H
#define camera_H
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
void initCam(GLfloat fov,GLfloat width, GLfloat height, GLfloat near, GLfloat far);
/*
Sends all matricies to currently bound shader
*/
void sendShader();
void rotate_cam(float x_rot, float y_rot);
void translateCam(glm::vec3 trans);
float getThetaX();
float getThetaY();
/*
Not Tested
sets up matricies for transform
*/
void translateCam(glm::vec3 trans,float thetax, float thetay);

void useGameCam();//use game world camera

//Not Implelented:
void useFrameCam();//use frame buffer camera

#endif