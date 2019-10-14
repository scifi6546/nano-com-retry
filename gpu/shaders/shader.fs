#version 130
uniform sampler2D diffuse;
in vec2 texcoord0;
uniform float wiggle;
out vec4 color;
void main(){
   float x_of=0.3f*sin(texcoord0.y*132)+0.1*sin(texcoord0.y*192+121.0f);
   float col = sin(texcoord0.x*150.0f-wiggle/50.0f+x_of)*0.05+0.05;
   vec4 col_out = vec4(col,col,col,1.0f);
   //vec4 col_out = vec4(texcoord0.y,texcoord0.y,texcoord0.y,texcoord0.y);
   color=texture(diffuse,texcoord0)+col_out;
}
