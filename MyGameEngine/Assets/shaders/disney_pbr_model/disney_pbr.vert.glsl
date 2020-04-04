#version 420 core

// Input
layout (location = 0) in vec3 model_position;
layout (location = 1) in vec3 model_normal;
layout (location = 2) in vec2 model_texcoord;
layout (location = 3) in vec3 model_tangent_vec;
layout (location = 4) in vec3 model_bitangent_vec;

// Const data
const int MAX_POINT_LIGHT_NUM = 5;


// Structure define
//////////////////////////////////////////////////////////////////////////////
struct PointLight{
	vec4 point_intensity;
	vec4 point_position;
};
//////////////////////////////////////////////////////////////////////////////

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

layout (std140, binding = 5) uniform const_shadow
{
	mat4 point_view_perspective_matrix[MAX_POINT_LIGHT_NUM];
	mat4 directional_view_perspective_matrix;
};

out VS_OUT{
	// Object world position
	vec4 world_object_position;
	// Normal vector of the object at model coordinate
	vec3 model_normal;
	// Point light direction vector at world coordinate
	vec3 world_pointlight_direction[MAX_POINT_LIGHT_NUM];
	// view direction vector at world coordinate
	vec3 world_view_direction;
	// Texture coordinate
	vec2 texcoord;
	// The depth value at light space
	vec3 light_space_position_depth[MAX_POINT_LIGHT_NUM];
	// tangent bitangent normal matrix
	mat3 tbn;
} vs_out;

/////////////////////////////////////////////////////////////////////////////
void main()
{
	vs_out.world_object_position    = model_view_perspective_matrix * vec4(model_position, 1.0);
	// Send position data at perspective coordinate
	gl_Position                     = vs_out.world_object_position;
	// Get normal vector at world coordinate
	vs_out.model_normal             = model_normal;

	for(int i = 0; i <= point_num; i++){
		vs_out.world_pointlight_direction[i] = normalize(vec3(pointlights[i].point_position) - vec3(model_position_matrix * vec4(model_position, 1)));
		vec4 position_depth                  = point_view_perspective_matrix[i] * model_position_matrix * vec4(model_position, 1.0);
		vec3 projcoord                       = position_depth.xyz / position_depth.w;
		vs_out.light_space_position_depth[i] = projcoord;
	}

	vs_out.world_view_direction     = normalize(camera_position_vector -  vec3(model_position_matrix * vec4(model_position, 1)));

	vs_out.texcoord                 = model_texcoord;

	vec3 t = normalize(vec3(model_position_matrix * vec4(model_tangent_vec, 0.0)));
	vec3 b = normalize(vec3(model_position_matrix * vec4(model_bitangent_vec, 0.0)));
	vec3 n = normalize(vec3(model_position_matrix * vec4(model_normal, 0.0)));
	vs_out.tbn = mat3(t, b, n);
}