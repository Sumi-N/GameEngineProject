#version 420 core

// Output
out vec4 color;

// Consta data
const int MAX_POINT_LIGHT_NUM = 5;
const float POINT_LIGHT_BIAS = 0.00005;

/////////////////////////////////////////////////////////////////////////////

in VS_OUT{
	// Normal vector of the object at world coordinate
	vec3 world_normal;
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


/////////////////////////////////////////////////////////////////////////////

vec4 CalcPointLightShading(vec3 world_pointlight_direction, vec4 point_intensity){
	vec4 color;

	float cos_theta_1 = dot(fs_in.world_normal, world_pointlight_direction);
	
	if (cos_theta_1 > 0)
	{
		color += cos_theta_1 * vec4(0.50980395f, 0.0, 0.0, 1.0) * point_intensity;
	
		vec3 h = normalize(fs_in.world_view_direction + world_pointlight_direction);

		if (dot(h, fs_in.world_normal) > 0)
		{
			vec3 reflection = -1 * fs_in.world_view_direction + 2 * dot(fs_in.world_view_direction, fs_in.world_normal) * fs_in.world_normal;

			color +=  vec4(vec3(point_intensity) * vec3(0.80099994f, 0.80099994f, 0.80099994f) * pow(dot(h, fs_in.world_normal), 10), 1.0);
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