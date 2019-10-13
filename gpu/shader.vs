#version 130
/*
in vec3 position;
in vec2 texcoord;
in vec3 aNormal;
out vec2 texcoord0;
out vec3 Normal;
out vec3 Pos;
out float z_depth;
uniform mat4 translate;
uniform mat4 camera;
uniform mat4 move;
uniform mat4 look;
uniform vec3 pos_global;
//uniform vec3 pos_translate

void main(){
    vec3 temp = pos_global+position;
    gl_Position=camera*look*translate*vec4(temp,1.0);
    z_depth=gl_Position.z;
    //gl_Position= camera * vec4(position,1.0);
    //gl_Position=vec4(position,1.0);
    Pos = position;
    texcoord0=texcoord;
    Normal=aNormal;
    //gl_Position=camera*translate*vec4(position,1.0f)

}
*/


in vec3 position;
in vec2 texcoord;
in vec3 aNormal;
out vec2 texcoord0;
out vec3 Normal;
out vec3 Pos;
out float z_depth;
void main(){
    gl_Position=vec4(position,1.0);
    texcoord0=texcoord;
    Normal=aNormal;
	z_depth = 0.5;

}
