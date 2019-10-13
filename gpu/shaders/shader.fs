#version 130
uniform sampler2D diffuse;
in vec2 texcoord0;
out vec4 color;
void main(){
   color=texture(diffuse,texcoord0);
}
