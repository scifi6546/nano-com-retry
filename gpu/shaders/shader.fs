#version 130
uniform sampler2D diffuse;
in vec2 texcoord0;
uniform float wiggle;
out vec4 color;
void main(){
   float x = texcoord0.x+texcoord0.y+wiggle*0.001f;
   float x_of=5.0f*sin(x*(10*sin(wiggle/30.0f)+132))+0.1*sin(x*192.0f+20.0f*sin(wiggle/8.0f))-4.0f;
   x_of=max(x_of,0.0f);
   float col = sin(texcoord0.x*150.0f-wiggle/50.0f+x_of)*0.05+0.05;
   vec4 col_out = vec4(col,col,col,1.0f);
   //vec4 col_out = vec4(texcoord0.y,texcoord0.y,texcoord0.y,texcoord0.y);
   color=texture(diffuse,texcoord0)+col_out;
}
