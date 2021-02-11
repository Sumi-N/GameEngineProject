#version 430 core

out vec4 color;

in vec3 texcoord;

layout(binding = 0) uniform samplerCube skybox;

void main(){
    vec3 envcolor = texture(skybox, texcoord).rgb;
    
    envcolor = envcolor / (envcolor + vec3(1.0));
    envcolor = pow(envcolor, vec3(1.0/2.2)); 

    color = vec4(envcolor, 1.0);
}