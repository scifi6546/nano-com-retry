#include "texture.h"
#include <string>
#include "shader.h"
#include <GL/glew.h>
#include "stb_image.h"
#include <assert.h>
#include "error.h"
#include <vector>
#include "render_target.h"
Texture genTextureVec(unsigned char* imagedata,int width,int height,int num_components){

    Texture out;
    getError();
    GLuint *texture;
    //printf("num_textures = %i\n", num_textures);
    // /printf("texture_new: %i \n",temp_texture);
    texture = (GLuint *)calloc(1, sizeof(GLuint));
    glGenTextures(1,&out.color_texture);
    /*
    for (int i = 0; i < num_textures; i++)
    {
        glGenTextures(1, &texture[i]);
        printf("texture[%i] = %i\n", i, texture[i]);
    }*/
    
    glBindTexture(GL_TEXTURE_2D, out.color_texture);
    getError();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, imagedata);
    getError();
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //stbi_image_free(imagedata);
    getError();
    glBindTexture(GL_TEXTURE_2D,1);
    out.width=width;
    out.height=height;
    return out;
    
}
Texture genTexture(std::string filename){
    Texture out;
    getError();
    GLuint *texture;
    //printf("num_textures = %i\n", num_textures);
    int width, height, numcomponents;
    // /printf("texture_new: %i \n",temp_texture);
    texture = (GLuint *)calloc(1, sizeof(GLuint));
    glGenTextures(1,&out.color_texture);
    /*
    for (int i = 0; i < num_textures; i++)
    {
        glGenTextures(1, &texture[i]);
        printf("texture[%i] = %i\n", i, texture[i]);
    }*/
    
    unsigned char *imagedata = stbi_load(filename.c_str(), &width,
                                         &height, &numcomponents, 4);
    if (imagedata == NULL)
    {
        printf("can not find texture %s", filename.c_str());
    }
    glBindTexture(GL_TEXTURE_2D, out.color_texture);
    getError();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, imagedata);
    getError();
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //stbi_image_free(imagedata);
    getError();
    stbi_image_free(imagedata);
    glBindTexture(GL_TEXTURE_2D,1);
    out.width=width;
    out.height=height;
    return out;
    
}
Texture genTextureEmp(){
    Texture out;

    glGenTextures(1,&out.color_texture);
    glBindTexture(GL_TEXTURE_2D,out.color_texture);
    getError();
    //Creating Color Map
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 

    //depth map
    glGenTextures(1,&out.depth_texture);
    glBindTexture(GL_TEXTURE_2D,out.depth_texture);

    glTexImage2D(GL_TEXTURE_2D,0,GL_DEPTH24_STENCIL8,800,600,0,GL_DEPTH_STENCIL,GL_UNSIGNED_INT_24_8,NULL);
    glBindTexture(GL_TEXTURE_2D,1);
    getError();
    return out;
}
//void delTexture()
//{
//    for (int i = 0; i < num_textures; i++)
//    {
//        glDeleteTextures(1, &texture[i]);
//    }
//}
/*
void bindTexture(unsigned int unit)
{
    //printf("unit = %i",unit);
    //assert(unit >= 0 && unit <= 31);
    glActiveTexture(GL_TEXTURE0);
    getError();
    glBindTexture(GL_TEXTURE_2D, unit);
    getError();
    setTexture(unit);
    getError();
}*/
void bindTexture(const Texture to_bind,
    const render_target buffer,
    const std::string sampler_name){
        //printf("to_bind texture %i\n",to_bind.color_texture);
        //GLuint location = glGetUniformLocation(buffer.program,
        //    sampler_name.c_str());
        //printf("location: %i\n",location);
        //printf("sampler_name: %s\n",sampler_name.c_str());
        //glActiveTexture(GL_TEXTURE0+location);
        glActiveTexture(GL_TEXTURE0);
        //binds texture
        
        glBindTexture(GL_TEXTURE_2D,to_bind.color_texture);
        getError();
}
