#version 420 core

// Output
out vec4 color;

// Consta data
const int MAX_POINT_LIGHT_NUM = 5;
const float POINT_LIGHT_BIAS = 0.00005;

/////////////////////////////////////////////////////////////////////////////

in VS_OUT{
	// Normal vector of the object at world coordinate
	vec3 model_normal;
	// Point light direction vector at world coordinate
	vec3 world_pointlight_direction[MAX_POINT_LIGHT_NUM];
	// Object direction vector at world coordinate
	vec3 world_view_direction;
	// Texture coordinate
	vec2 texcoord;
	// The depth value at light space
	vec3 light_space_position_depth[MAX_POINT_LIGHT_NUM];
} fs_in;

//////////////////////////////////////////////////////////////////////////////
// Structure define
struct PointLight{
	vec4 point_intensity;
	vec4 point_position;
};
//////////////////////////////////////////////////////////////////////////////

layout (std140, binding = 3) uniform const_light
{
	vec4 ambient_intensity;
	vec4 directional_intensity;
	vec4 directional_direction;
	PointLight pointlights[MAX_POINT_LIGHT_NUM];
	int  point_num;
};

layout (std140, binding = 1) uniform const_object
{
	mat4 model_position_matrix;
	mat4 model_view_perspective_matrix;
	mat4 model_inverse_transpose_matrix;
};


/////////////////////////////////////////////////////////////////////////////

vec4 CalcPointLightShading(vec3 world_pointlight_direction, vec4 point_intensity){
	vec4 color = vec4(0, 0, 0, 1.0);

	vec3 world_normal = normalize(mat3(model_inverse_transpose_matrix) * fs_in.model_normal);

	float cos_theta_1 = dot(world_normal, world_pointlight_direction);
	
	if (cos_theta_1 > 0)
	{
		color += cos_theta_1 * vec4(0.50980395f, 0.0, 0.0, 1.0) * point_intensity;
	
		vec3 h = normalize(fs_in.world_view_direction + world_pointlight_direction);

		if (dot(h, world_normal) > 0)
		{
			color +=  vec4(vec3(point_intensity) * vec3(0.80099994f, 0.80099994f, 0.80099994f) * pow(dot(h, world_normal), 20), 1.0);
		}
	}

	return color;
}


/////////////////////////////////////////////////////////////////////////////
void main()
{
	// Ambient light
	color = vec4(0.50980395f, 0.0, 0.0, 1.0) * ambient_intensity;

	for(int i = 0; i < point_num; i++){
		color += CalcPointLightShading(fs_in.world_pointlight_direction[i], pointlights[i].point_intensity);
	}
}