#version 130

in vec3 position;
in vec2 texcoord;
in vec3 aNormal;
out vec2 texcoord0;
out vec3 Normal;
out vec3 Pos;
void main(){
    gl_Position=vec4(position,1.0);
    texcoord0=texcoord;
    Normal=aNormal;

}
