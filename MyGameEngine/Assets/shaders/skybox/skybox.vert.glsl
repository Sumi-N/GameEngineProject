#version 420 core
layout (location = 0) in vec3 model_position;

out vec3 TexCoords;

layout (std140, binding = 4) uniform const_skybox
{
    mat4 view_perspective_matrix;
};

void main()
{
    TexCoords = model_position;
    gl_Position = view_perspective_matrix * vec4(model_position, 1.0);
}