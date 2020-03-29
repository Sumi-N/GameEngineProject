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

layout (std140, binding = 3) uniform const_light
{
	vec4 light_ambient_intensity;
	vec4 light_point_intensity;
	vec4 light_point_position;
	vec4 light_padding;
	mat4 light_view_perspective_matrix;
};

void main()
{
    // Send position data at perspective coordinate
	gl_Position                = model_view_perspective_matrix * vec4(model_position, 1.0);
}