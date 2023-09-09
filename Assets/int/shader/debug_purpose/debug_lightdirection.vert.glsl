#version 420 core

// Consta data
const int MAX_POINT_LIGHT_NUM = 5;

layout (location = 0) in vec3 model_position;
layout (location = 1) in vec3 model_normal;
layout (location = 2) in vec2 model_texcoord;

struct PointLight{
	vec4 point_intensity;
	vec4 point_position;
};

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
	vec4 ambient_intensity;
	vec4 directional_intensity;
	vec4 directional_direction;
	PointLight pointlights[MAX_POINT_LIGHT_NUM];
	int  point_num;
};

out VS_OUT{
	// Normal vector of the object at world coordinate
	vec3 world_normal;
	// Object direction vector at world coordinate
	vec3 world_view_direction;
	// Point light direction vector at world coordinate
	vec3 world_pointlight_direction[MAX_POINT_LIGHT_NUM];
} vs_out;

void main()
{
	gl_Position = model_view_perspective_matrix * vec4(model_position, 1);
	vs_out.world_normal               = normalize(mat3(model_inverse_transpose_matrix) * model_normal);
	vs_out.world_view_direction     = normalize(camera_position_vector -  vec3(model_position_matrix * vec4(model_position, 1)));

	for(int i = 0; i <= point_num; i++){
		vs_out.world_pointlight_direction[i] = normalize(vec3(pointlights[i].point_position) - vec3(model_position_matrix * vec4(model_position, 1)));
	}
}