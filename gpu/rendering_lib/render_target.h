#ifndef RENDER_TARGET
#define RENDER_TARGET
#include <GL/glew.h>
#include <string>
#include <vector>
struct Texture{
    GLuint color_texture=0;
    GLuint depth_texture=0;
    int width=0;
    int height=0;
};

/*
    Struct that stores frame buffer object info
*/
struct FBO{
    unsigned int FBO_OJECT=0;
    Texture attTexture;//attached texture
    //unsigned int DEPTH_MAP=0;
    //unsigned int COLOR_MAP=0;
};
struct uniform{
    std::string name="";//name of uniform
    GLuint location=0;//location of uniform
    GLenum type=0;//type of inuform (float vec3 etc)
};
struct attribute{
    std::string name="";//name of uniform
    GLuint location=0;//location of uniform
    GLenum type=0;//type of inuform (float vec3 etc)
};

//render target struct
struct render_target{
    FBO bufer_object;
    GLuint program=0;
    std::vector<uniform> Unis={};
    std::vector<attribute> Attributes={};


};


#endif