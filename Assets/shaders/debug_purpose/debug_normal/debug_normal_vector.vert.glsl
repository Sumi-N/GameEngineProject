#version 420 core

layout (location = 0) in vec3 model_position;
layout (location = 1) in vec3 model_normal;
layout (location = 2) in vec2 model_texcoord;

layout (std140, binding = 1) uniform const_model
{
	mat4 model_position_matrix;
	mat4 model_view_perspective_matrix;
	mat4 model_inverse_transpose_matrix;
};

layout (std140, binding = 0) uniform const_camera
{
	mat4 view_matrix;
	mat4 perspective_matrix;
	vec3 camera_position_vector;
	float camera_padding;
};

out VS_OUT{
	// Normal vector of the object at world coordinate
	vec3 normal;
} vs_out;

void main()
{
	gl_Position         = model_view_perspective_matrix * vec4(model_position, 1.0);
	vs_out.normal       = normalize(mat3(perspective_matrix) * mat3(view_matrix) * mat3(model_inverse_transpose_matrix) * model_normal);
}