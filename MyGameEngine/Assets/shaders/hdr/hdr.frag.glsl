#version 430 core

out vec4 color;

in vec2 texcoords;

layout(binding = 2) uniform sampler2d hdrbuffer;

void main(){
    vec3 hdrcolor = texture(hdrbuffer, texcoords).rgb;
    color = vec4(hdrcolor, 1.0);
}