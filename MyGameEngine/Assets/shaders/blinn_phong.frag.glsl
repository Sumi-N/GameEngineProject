#version 420 core

// Output
out vec4 color;

// Consta data
const int MAX_POINT_LIGHT_NUM = 5;

/////////////////////////////////////////////////////////////////////////////

// Normal vector of the object at world coordinate
in vec3 world_normal;
// Point light direction vector at world coordinate
in vec3 world_pointlight_direction[MAX_POINT_LIGHT_NUM];
// Object direction vector at world coordinate
in vec3 world_object_direction;
// Texture coordinate
in vec2 texcoord;
// The depth value at light space
in vec4 light_space_position_depth;

//////////////////////////////////////////////////////////////////////////////
// Structure define
struct PointLight{
	vec4 point_intensity;
	vec4 point_position;
};
//////////////////////////////////////////////////////////////////////////////

layout (std140, binding = 2) uniform const_material
{
	vec4 diffuse;
	vec4 specular;
};

layout (std140, binding = 3) uniform const_light
{
	vec4 ambient_intensity;
	vec4 directional_intensity;
	vec4 directional_direction;
	PointLight pointlights[MAX_POINT_LIGHT_NUM];
	int  point_num;
};

layout(binding = 0)uniform samplerCube skybox;
layout(binding = 1) uniform sampler2D texture0;
layout(binding = 2) uniform sampler2D texture1;
uniform sampler2D shadowmap;

//////////////////////////////////////////////////////////////////////////////
bool ShadowCalculation(vec4 fragPosLightSpace)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowmap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // check whether current frag pos is in shadow
    return  currentDepth - 0.005 > closestDepth  ? true : false;
} 

/////////////////////////////////////////////////////////////////////////////
vec4 calcPointLightShading(vec3 world_normal, vec3 world_pointlight_direction, vec4 diffuse, vec4 specular, vec4 point_intensity, vec3 world_object_direction, sampler2D texture0, vec2 texcoord, sampler2D texture1){
	vec4 color;

	float cos_theta_1 = dot(world_normal, world_pointlight_direction);
	
	if (cos_theta_1 > 0)
	{
		color += texture2D(texture0, texcoord.st)  * cos_theta_1 * diffuse * point_intensity;
	
		vec3 h = normalize(world_object_direction + world_pointlight_direction);

		if (dot(h, world_normal) > 0)
		{
			vec3 reflection = -1 * world_object_direction + 2 * dot(world_object_direction, world_normal) * world_normal;

			color +=  texture2D(texture1, texcoord.st) * vec4(vec3(point_intensity) * vec3(specular) * pow(dot(h, world_normal), specular.w), 1.0);
		}
	}

	return color;
}


/////////////////////////////////////////////////////////////////////////////
void main()
{
	// Ambient light
	color = texture2D(texture0, texcoord.st) * diffuse * ambient_intensity;

	for(int i = 0; i < point_num; i++){
		color += calcPointLightShading(world_normal, world_pointlight_direction[i], diffuse, specular, pointlights[i].point_intensity, world_object_direction, texture0, texcoord, texture1);
	}
}