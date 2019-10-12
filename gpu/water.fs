#version 130
uniform sampler2D diffuse;
uniform vec3 ambient_color;
uniform float ambient_intensity;
uniform vec3 sun_pos;
uniform float sun_intensity;
uniform vec3 sun_color;
in vec2 texcoord0;
in vec3 Normal;
in vec3 Pos;
in float z_depth;
out vec4 color;
uniform mat4 camera;
//out vec4 color;
void main(){
    vec3 lightDir = normalize(sun_pos-Pos);
    float diff = dot(Normal,lightDir);
    vec3 diffuse_light=diff*sun_color*sun_intensity;
    
    vec3 color_light = ambient_color*ambient_intensity + diffuse_light;

    //color=vec4(Pos,1.0);
    //color=texture(diffuse,texcoord0);
    color=texture(diffuse,texcoord0)*vec4(color_light,1.0)*min(1/z_depth,1);
   // color=texture(diffuse,texcoord0);
}
