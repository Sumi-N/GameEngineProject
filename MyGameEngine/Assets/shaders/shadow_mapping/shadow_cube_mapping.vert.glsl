#version 420 core

layout (location = 0) in vec3 model_position;

// Const data
const int MAX_POINT_LIGHT_NUM = 5;
const int CUBE_FACE_NUM = 6;

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

layout (std140, binding = 5) uniform const_shadow
{
	mat4 point_view_perspective_matrix[MAX_POINT_LIGHT_NUM * CUBE_FACE_NUM];
	mat4 directional_view_perspective_matrix;
};

void main()
{
    gl_Position = model_position_matrix * vec4(model_position, 1.0);

}