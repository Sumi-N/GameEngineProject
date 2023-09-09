#version 430 core

layout(location = 0) in vec3 texcoord;

layout(location = 0) out vec4 color;

layout(binding = 0) uniform samplerCube skybox;

void main(){
    vec3 envcolor = texture(skybox, texcoord).rgb;
    
    envcolor = envcolor / (envcolor + vec3(1.0));
    envcolor = pow(envcolor, vec3(1.0/2.2)); 

    color = vec4(envcolor, 1.0);
}