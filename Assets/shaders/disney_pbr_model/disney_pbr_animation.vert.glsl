#version 420 core

// Const data
const int MAX_POINT_LIGHT_NUM = 5;
const int MAX_BONE_NUM = 256;

// Input
layout (location = 0) in vec3 model_position;
layout (location = 1) in vec3 model_normal;
layout (location = 2) in vec2 model_texcoord;
layout (location = 3) in vec3 model_tangent_vec;
layout (location = 4) in vec3 model_bitangent_vec;
layout (location = 5) in vec2 padding;
layout (location = 6) in ivec4 skin_index;
layout (location = 7) in vec4  skin_weight;

// Structure define
//------------------------------------------------------------------------------
struct PointLight{
	vec4 intensity;
	vec4 position;
	vec3 attenuation;
	float padding;
};
//------------------------------------------------------------------------------

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

layout (std140, binding = 3) uniform const_light
{
	vec4 ambient_intensity;
	vec4 directional_intensity;
	vec4 directional_direction;
	PointLight pointlights[MAX_POINT_LIGHT_NUM];
	int  point_num;
};

layout (std140, binding = 6) uniform const_animation_bone
{
	mat4 global_inversed_matrix[MAX_BONE_NUM];
};

out VS_OUT{
	// Object world position
	vec4 world_position;
	// Normal vector of the object at model coordinate
	vec3 model_normal;
	// Texture coordinate
	vec2 texcoord;
	// view direction vector at world coordinate
	vec3 world_view_direction;
	// Point light direction vector at world coordinate
	vec3 world_pointlight_direction[MAX_POINT_LIGHT_NUM];
	// tangent bitangent normal matrix
	mat3 tangent_bitangent_matrix;
} vs_out;

//------------------------------------------------------------------------------

void main()
{
	vec4 animated_model_position    = skin_weight.x * global_inversed_matrix[skin_index.x] * vec4(model_position, 1.0)
									+ skin_weight.y * global_inversed_matrix[skin_index.y] * vec4(model_position, 1.0)
									+ skin_weight.z * global_inversed_matrix[skin_index.z] * vec4(model_position, 1.0)
									+ skin_weight.w * global_inversed_matrix[skin_index.w] * vec4(model_position, 1.0);

	vec3 animated_model_normal      = model_normal;

	vs_out.world_position           = model_position_matrix * animated_model_position;
	// Send position data at perspective coordinate
	gl_Position                     = model_view_perspective_matrix * animated_model_position;

	// Get normal vector at world coordinate
	vs_out.model_normal             = animated_model_normal;

	for(int i = 0; i <= point_num; i++){
		vs_out.world_pointlight_direction[i] = normalize(vec3(pointlights[i].position) - vec3(model_position_matrix * animated_model_position));
	}

	vs_out.world_view_direction     = normalize(camera_position_vector -  vec3(model_position_matrix * animated_model_position));

	vs_out.texcoord                 = model_texcoord;

	vec3 t = normalize(vec3(model_position_matrix * vec4(model_tangent_vec, 0.0)));
	vec3 b = normalize(vec3(model_position_matrix * vec4(model_bitangent_vec, 0.0)));
	vec3 n = normalize(vec3(model_position_matrix * vec4(animated_model_normal, 0.0)));
	vs_out.tangent_bitangent_matrix = mat3(t, b, n);
}