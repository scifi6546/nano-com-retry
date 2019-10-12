#version 130
uniform sampler2D diffuse;
in vec2 texcoord0;
in vec3 Normal;
out vec4 color;
uniform mat4 camera;
//out vec4 color;
void main(){
    float n_temp = dot(Normal,vec3(1.0f,1.0f,1.0f));
    color=texture(diffuse,texcoord0)*n_temp;
   // color=texture(diffuse,texcoord0);
}
