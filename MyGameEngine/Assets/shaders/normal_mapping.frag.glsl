#version 420 core

// Output
out vec4 color;

// Consta data
const int MAX_POINT_LIGHT_NUM = 5;
const float POINT_LIGHT_BIAS = 0.00005;

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
in vec4 light_space_position_depth[MAX_POINT_LIGHT_NUM];

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

layout(binding = 0) uniform samplerCube skybox;
layout(binding = 1) uniform sampler2D texture0; // Diffuse  texture
layout(binding = 2) uniform sampler2D texture1; // Specular texture
layout(binding = 3) uniform sampler2D texture2; // Normal map
layout(binding = 4) uniform sampler2D shadowmap;

//////////////////////////////////////////////////////////////////////////////

float ShadowCalculation(vec4 fragPosLightSpace)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // check whether current frag pos is in shadow
	float shadow = 0.0;
	vec2 texelSize = 1.0 / textureSize(shadowmap, 0);
	for(int x = -2; x <= 2; ++x)
	{
		for(int y = -2; y <= 2; ++y)
		{
			float pcfDepth = texture(shadowmap, projCoords.xy + vec2(x, y) * texelSize).r; 
			shadow += currentDepth - POINT_LIGHT_BIAS > pcfDepth ? 1.0 : 0.0;        
		}    
	}
	shadow /= 16.0;
	return shadow;
}

/////////////////////////////////////////////////////////////////////////////

vec3 NormalMapping(){

    // obtain normal from normal map in range [0,1]
    vec3 normal = texture(texture2, 1- texcoord).rgb;
    // transform normal vector to range [-1,1]
    normal = normalize(normal * 2.0 - 1.0); 

	vec3 normal2 = normalize(mat3(model_inverse_transpose_matrix) * normal);

	return normal2;
}

/////////////////////////////////////////////////////////////////////////////

vec4 CalcPointLightShading(vec3 world_pointlight_direction, vec4 point_intensity){

	float cos_theta_1 = dot(NormalMapping(), world_pointlight_direction);
	
	if (cos_theta_1 > 0)
	{
		color += texture2D(texture0, 1.0 - texcoord.st)  * cos_theta_1 * diffuse * point_intensity;
	
		vec3 h = normalize(world_object_direction + world_pointlight_direction);

		if (dot(h, NormalMapping()) > 0)
		{
			//vec3 reflection = -1 * world_object_direction + 2 * dot(world_object_direction, world_normal) * world_normal;

			//color +=  (texture2D(texture1, 1.0 - texcoord.st) + texture(skybox, reflection)) * vec4(vec3(point_intensity) * vec3(specular) * pow(dot(h, world_normal), specular.w), 1.0);
			color +=  texture2D(texture1, 1.0 - texcoord.st) * vec4(vec3(point_intensity) * vec3(specular) * pow(dot(h, NormalMapping()), specular.w), 1.0);
		}
	}

	return color;
}

/////////////////////////////////////////////////////////////////////////////
void main()
{
	// Ambient light
	color = vec4(0, 0, 0, 0);
	//color = texture2D(texture0, 1.0 - texcoord.st) * diffuse * ambient_intensity;

	float shadow = 0;
	for(int i = 0; i < 1; i++){
		shadow += ShadowCalculation(light_space_position_depth[i]);
	}

	if(shadow > 1){
		shadow = 1;
	}

	for(int i = 0; i < point_num; i++){
		color += CalcPointLightShading(world_pointlight_direction[i], pointlights[i].point_intensity) * (1.0 - shadow);
	}
}