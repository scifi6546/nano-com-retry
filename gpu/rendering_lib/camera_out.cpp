#include "camera_out.h"
#include <stdio.h>
#include <glm/glm.hpp>
float PIt=3.14159265358979323846264338327;
Camera::Camera(glm::vec3 pos,float thetax, float thetay){
    this->position=pos;
    this->thetax=thetax;
    this->thetay=thetay;
}
void Camera::setPos(glm::vec3 pos_in){
    this->position=pos_in;
}
glm::vec3 Camera::getPos(){
    return this->position;
}
void Camera::moveCam(float deltax,float deltay){
    this->thetax+=deltay;
    this->thetay+=deltax;

    if(thetay>=2.0*PIt){
        thetay-=2.0*PIt;
    }if(thetay<=-2.0*PIt){
        thetay+=2.0*PIt;
    }
    if(thetax>=PIt/2.0){
        thetax=PIt/2.0;
    }if(thetax<=-PIt/2.0){
        thetax=-PIt/2.0;
    }
	printf("thetax: %f thetay: %f\n",thetax,thetay);
}
void Camera::sendToRender(){
    //printf("positon.x: %f, position.y: %f, position.z: %f\n",
    //this->position.x,this->position.y,this->position.z);

    //printf("look_x: %f look_y %f\n",this->thetax,this->thetay);
    sendCamera(this->position,this->thetax,this->thetay);
}
