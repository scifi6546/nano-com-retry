#version 130
uniform sampler2D diffuse;
in vec2 texcoord0;
out vec4 color;
void main(){
   float col = sin(texcoord0.x*150.0f)*0.05+0.05;
   vec4 col_out = vec4(col,col,col,1.0f);
   //vec4 col_out = vec4(texcoord0.y,texcoord0.y,texcoord0.y,texcoord0.y);
   color=texture(diffuse,texcoord0)+col_out;
}
