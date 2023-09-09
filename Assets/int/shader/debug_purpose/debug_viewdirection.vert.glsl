#version 420 core

layout (location = 0) in vec3 model_position;
layout (location = 1) in vec3 model_normal;
layout (location = 2) in vec2 model_texcoord;

layout (std140, binding = 0) uniform const_camera
{
	mat4 view_matrix;
	mat4 perspective_matrix;
	vec3 camera_position_vector;
	float camera_padding;
};

layout (std140, binding = 1) uniform const_object
{
	mat4 model_position_matrix;
	mat4 model_view_perspective_matrix;
	mat4 model_inverse_transpose_matrix;
};

out VS_OUT{
	// Normal vector of the object at world coordinate
	vec3 world_normal;
	// Object direction vector at world coordinate
	vec3 world_view_direction;
} vs_out;

void main()
{
	gl_Position = model_view_perspective_matrix * vec4(model_position, 1);
	vs_out.world_normal               = normalize(mat3(model_inverse_transpose_matrix) * model_normal);
	vs_out.world_view_direction     = normalize(camera_position_vector -  vec3(model_position_matrix * vec4(model_position, 1)));
}