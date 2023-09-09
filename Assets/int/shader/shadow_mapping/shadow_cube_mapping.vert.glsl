#version 420 core

layout (location = 0) in vec3 model_position;

layout (std140, binding = 1) uniform const_object
{
	mat4 model_position_matrix;
	mat4 model_view_perspective_matrix;
	mat4 model_inverse_transpose_matrix;
};

void main()
{
    gl_Position = model_position_matrix * vec4(model_position, 1.0);

}