#version 420 core

const float Z_BUFFER_BIAS = 0.05f;

layout (location = 0) in vec3 model_position;
layout (location = 1) in vec3 model_normal;
layout (location = 2) in vec2 model_texcoord;

layout (location = 0) out vec2 frag_tex_coord;

layout (std140, binding = 0) uniform const_camera
{
	mat4 view_matrix;
	mat4 perspective_matrix;
	vec3 camera_position_vector;
	float camera_padding;
};

layout (std140, binding = 1) uniform const_model
{
	mat4 model_position_matrix;
	mat4 model_view_perspective_matrix;
	mat4 model_inverse_transpose_matrix;
};

void main()
{
	vec4 mvp_coord = perspective_matrix * view_matrix * model_position_matrix * vec4(model_position, 1.0);	    
	frag_tex_coord = model_texcoord;
	gl_Position = mvp_coord;
}