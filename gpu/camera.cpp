#include "camera.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "shader.h"
#include <string>
#include <math.h>
#include "error.h"
#include "render_manager.h"
#include "game_const.h"
GLint camera_loc;
glm::mat4 translate;
glm::mat4 projection;
glm::vec3 cam_pos;
glm::mat4 camera_mat;
glm::mat4 look_at;
//float thetax;
//float thetay;
float PI=3.14159265358979323846264338327;

//camera constants

GLfloat game_cam_fov;//game field of vision
GLfloat game_cam_width;//game screen width
GLfloat game_cam_height;//game screen height
GLfloat game_cam_near;//game neear clipping plane
GLfloat game_cam_far;//game far clipping plane

void INT_look();

//converts glm::mat4 to std::string inorder to make printing easier
std::string makeString(glm::mat4 in){
    float* mat = glm::value_ptr(in);
    float mat_arr[16];
    std::string out;
    for(int i =0; i<16; i+=4){
        //out+= std::to_string((double) mat[i]);
        out+="[" + std::to_string(mat[i]) + "," + std::to_string(mat[i+1]) +"," + std::to_string(mat[i+2]) + "," + std::to_string(mat[i+3]) +"]\n";
    }
    return out;
}
void sendShader(){
    sendMat4("camera",camera_mat,*getBoundShader());
    sendMat4("look",look_at,*getBoundShader());
    sendMat4("translate",translate,*getBoundShader());
	sendVec3("ambient_color", ambient_color, *getBoundShader());
	sendVec3("sun_color", sun_color, *getBoundShader());
	sendGLfloat("sun_intensity", sun_intensity, *getBoundShader());
}
void initCam(GLfloat fov,GLfloat width, GLfloat height, GLfloat near, GLfloat far){
    getError();
    game_cam_fov=fov;
    game_cam_width=width;
    game_cam_height=height;
    game_cam_near=near;
    game_cam_far=far;
    camera_mat=glm::mat4(1.0f);
    camera_mat = glm::perspective(glm::radians(fov),width/height,near,far);
    sendMat4("camera",camera_mat,*getBoundShader());

//not needed anymore
/*
    thetax=0.0f;
    thetay=PI/2.0;
    translate=glm::mat4(1.0f);
    look_at=glm::mat4(1.0f);
    cam_pos = glm::vec3(0.0f,0.0f,0.0f);
    printf("fov = %f , width = %f, height = %f, near = %f, far = %f\n",fov,width,height,near,far);
    getError();
    //useGameCam();
    getError();
    */
    /*
    projection=glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(fov),width/height,near,far);

    printf("projection \n%s",makeString(projection).c_str());
    sendCamera(projection);
    translate = glm::translate(translate,glm::vec3(0.0f,0.0f,0.0f));
    printf("translate \n%s",makeString(translate).c_str());
    sendTranslate(translate);

    INT_look();
    printf("look at = \n%s",makeString(look_at).c_str());
    */
}
/*
void rotate_cam(float x_rot, float y_rot){
    glm::vec3 direction;
    direction.x = -cos(y_rot);
    direction.y = -sin(x_rot);
    direction.z = -sin(y_rot);
    
    float x = -cos(thetay);
    float y = -sin(thetax);
    float z = -sin(thetay);
    
    
    //printf("pos.x = %f pos.y = %f pos.z = %f\n",cam_pos.x,cam_pos.y,cam_pos.z);
    //printf("thetax = %f thetay = %f \n x look = %f y look = %f z look = %f\n",thetax,thetay,x,y,z);
    look_at=glm::lookAt(cam_pos,cam_pos+direction,glm::vec3(0.0f,1.0f,0.0f));
    sendLook(look_at);
    return;
    /*thetax+=x_rot;
    thetay+=y_rot;
    if(thetay>=2*PI){
        thetay-=2*PI;
    }if(thetax>=PI/2){
        thetax=PI/2;
    }if(thetax<=-PI/2){
        thetax=-PI/2;
    }
    INT_look();
}
*/
void translateCam(glm::vec3 trans,float thetax, float thetay){

    glm::vec3 direction;
    direction.x = -cos(thetay);
    direction.y = -sin(thetax);
    direction.z = -sin(thetay);
    /*
    float x = -cos(thetay);
    float y = -sin(thetax);
    float z = -sin(thetay);
    */
    translate = glm::mat4(1.0f);
   translate = glm::translate(translate,glm::vec3(0.0f,0.0f,0.0f));
        look_at = glm::mat4(1.0f);
    //printf("pos.x = %f pos.y = %f pos.z = %f\n",cam_pos.x,cam_pos.y,cam_pos.z);
    //printf("thetax = %f thetay = %f \n x look = %f y look = %f z look = %f\n",thetax,thetay,x,y,z);
    look_at=glm::lookAt(trans,trans+direction,glm::vec3(0.0f,1.0f,0.0f));
    getError();
    
    sendMat4("look",look_at,*getBoundShader());
    sendMat4("translate",translate,*getBoundShader());
    //sendLook(look_at);
    getError();
}