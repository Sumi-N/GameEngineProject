#version 420 core

const float Z_BUFFER_BIAS = 0.05f;

layout (location = 0) in vec3 model_position;

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
    mat4 scale = mat4(1.07, 0.0, 0.0, 0.0,  // 1. column
                      0.0, 1.07, 0.0, 0.0,  // 2. column
                      0.0, 0.0, 1.07, 0.0,  // 3. column
                      0.0, 0.0, 0.0, 1.0); 

    mat4 scaled_matrix = model_position_matrix * scale;

	vec4 unscaled_coord = perspective_matrix * view_matrix * model_position_matrix * vec4(model_position, 1.0);
	vec4 scaled_coord = perspective_matrix * view_matrix * scaled_matrix * vec4(model_position, 1.0);

    //gl_Position = vec4(scaled_coord.x, scaled_coord.y, unscaled_coord.z + Z_BUFFER_BIAS, unscaled_coord.w);
	gl_Position = unscaled_coord;
}