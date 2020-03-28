#version 420 core

layout (location = 0) in vec3 model_position;
layout (location = 1) in vec3 model_normal;
layout (location = 2) in vec2 model_texcoord;

layout (std140, binding = 1) uniform const_object
{
	mat4 model_position_matrix;
	mat4 model_view_perspective_matrix;
	mat4 model_inverse_transpose_matrix;
};

out vec3 WorldPos_CS_in;
out vec2 TexCoord_CS_in;
out vec3 Normal_CS_in;

void main()
{
    WorldPos_CS_in = (model_position_matrix * vec4(model_position, 1.0)).xyz;
    TexCoord_CS_in = model_texcoord;
    Normal_CS_in = normalize(mat3(model_inverse_transpose_matrix) * model_normal);
}