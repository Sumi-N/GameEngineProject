#version 420 core

layout (location = 0) in vec3 model_position;

// Const data
const int CUBE_FACE_NUM = 6;

layout (std140, binding = 1) uniform const_object
{
	mat4 model_position_matrix;
	mat4 model_view_perspective_matrix;
	mat4 model_inverse_transpose_matrix;
};

layout (std140, binding = 5) uniform const_shadow
{
	mat4 point_view_perspective_matrix[CUBE_FACE_NUM];
	vec4 point_position;
};

void main()
{
    gl_Position = model_position_matrix * vec4(model_position, 1.0);

}