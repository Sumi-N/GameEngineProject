#version 420 core

layout (location = 0) in vec3 model_position;

layout (location = 0) out vec3 texcoord;

layout (std140, binding = 4) uniform const_skybox
{
    mat4 view_perspective_matrix;
};

void main()
{
    texcoord = model_position;
    vec4 world_pos = view_perspective_matrix * vec4(model_position, 1.0);
    gl_Position = world_pos.xyww;
}