#version 420 core
layout (location = 0) in vec3 model_position;

out vec4 position;


void main()
{
    gl_Position = vec4(model_position, 1.0);
}