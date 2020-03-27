#version 420 core

// Input
layout (location = 0) in vec3 model_position;
layout (location = 1) in vec3 model_normal;
layout (location = 2) in vec2 model_texcoord;

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

// Normal vector of the object at world coordinate
out vec3 world_normal;
// Point light direction vector at world coordinate
out vec3 world_pointlight_direction[MAX_POINT_LIGHT_NUM];
// Object direction vector at world coordinate
out vec3 world_object_direction;
// Texture coordinate
out vec2 texcoord;
// The depth value at light space
out vec4 light_space_position_depth[MAX_POINT_LIGHT_NUM];

//////////////////////////////////////////////////////////////////////////////

vec3 calcPointLightDirection(vec4 point_position, mat4 model_position_matrix, vec3 model_position){
	return normalize(vec3(point_position) - vec3(model_position_matrix * vec4(model_position, 1)));
}

/////////////////////////////////////////////////////////////////////////////
void main()
{
	// Send position data at perspective coordinate
	gl_Position                = model_view_perspective_matrix * vec4(model_position, 1.0);
	// Get normal vector at world coordinate
	world_normal               = normalize(mat3(model_inverse_transpose_matrix) * model_normal);

	for(int i = 0; i <= point_num; i++){
		world_pointlight_direction[i] = calcPointLightDirection(pointlights[i].point_position, model_position_matrix, model_position);
		light_space_position_depth[i] = point_view_perspective_matrix[i] * model_position_matrix * vec4(model_position, 1.0);
	}

	world_object_direction     = normalize(camera_position_vector -  vec3(model_position_matrix * vec4(model_position, 1)));

	texcoord                   = model_texcoord;
}