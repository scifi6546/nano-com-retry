#ifndef Texture_h
#define Texture_h
#include <string>
#include <GL/glew.h>
#include <vector>
#include "render_target.h"
void genTexture(std::vector<std::string> filename);//decripitated
void bindTexture(unsigned int unit);//decrepitated do not use!
/*
Not tested
binds the texture to the sampler specified
*/
void bindTexture(const Texture to_bind,const render_target buffer,const std::string sampler_name);
void delTexture();
/*
Generates a texture from given Filename
*/
Texture genTexture(std::string filename);
/*
Not Tested
Generates a empty texture
*/
Texture genTextureEmp();

#endif