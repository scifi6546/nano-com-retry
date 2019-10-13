#ifndef CAMERA_OUT
#define CAMERA_OUT
#include <glm/glm.hpp>
#include "render_manager.h"
//camera class interfaces with render_manager.h instead of opengl directly
class Camera{
    public:
        Camera(glm::vec3 pos,float thetax, float thetay);
        void setPos(glm::vec3 pos_in);
        glm::vec3 getPos();
        void moveCam(float deltax,float deltay);
        void sendToRender();//sends data to render_manager.h
    private:
        float thetax;
        float thetay;
        glm::vec3 position;
};
#endif