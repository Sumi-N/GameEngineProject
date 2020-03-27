#version 420 core

layout (location = 0) in vec3 model_position;

// Const data
const int MAX_POINT_LIGHT_NUM = 5;

// Structure define
//////////////////////////////////////////////////////////////////////////////
struct PointLight{
	vec4 point_intensity;
	vec4 point_position;
};
//////////////////////////////////////////////////////////////////////////////

layout (std140, binding = 1) uniform const_object
{
	mat4 model_position_matrix;
	mat4 model_view_perspective_matrix;
	mat4 model_inverse_transpose_matrix;
};

layout (std140, binding = 3) uniform const_light
{
	vec4 ambient_intensity;
	vec4 directional_intensity;
	vec4 directional_direction;
	PointLight pointlights[MAX_POINT_LIGHT_NUM];
	int  point_num;
};

layout (std140, binding = 4) uniform const_shadow
{
	mat4 point_view_perspective_matrix[MAX_POINT_LIGHT_NUM];
	mat4 directional_view_perspective_matrix;
};

void main()
{
    gl_Position = point_view_perspective_matrix[0] * model_position_matrix * vec4(model_position, 1.0);
    //gl_Position = light_view_perspective_matrix * vec4(model_position, 1.0);
}