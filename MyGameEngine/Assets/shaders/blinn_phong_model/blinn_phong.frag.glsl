#version 420 core

// Output
out vec4 color;

// Consta data
const int MAX_POINT_LIGHT_NUM = 5;
const float POINT_LIGHT_BIAS = 0.00005;

/////////////////////////////////////////////////////////////////////////////

in VS_OUT{
	// Normal vector of the object at model coordinate
	vec3 model_normal;
	// Object direction vector at world coordinate
	vec3 world_view_direction;
	// Texture coordinate
	vec2 texcoord;
	// Point light direction vector at world coordinate
	vec3 world_pointlight_direction[MAX_POINT_LIGHT_NUM];
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

layout (std140, binding = 2) uniform const_material
{
	vec4 diffuse;
	vec4 specular;
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

layout(binding = 0) uniform samplerCube skybox;
layout(binding = 1) uniform sampler2D shadowmap;
layout(binding = 3) uniform sampler2D texture0; // Diffuse  texture
layout(binding = 4) uniform sampler2D texture1; // Specular texture
layout(binding = 5) uniform sampler2D texture2; // Normal map

//////////////////////////////////////////////////////////////////////////////

float ShadowCalculation(vec3 fragPosLightSpace)
{
    // transform to [0,1] range
    vec3 projCoords = fragPosLightSpace * 0.5 + 0.5;
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

vec4 CalcPointLightShading(vec3 world_pointlight_direction, vec4 point_intensity, vec3 world_normal){
	vec4 color;

	float cos_theta_1 = dot(world_normal, world_pointlight_direction);
	
	if (cos_theta_1 > 0)
	{
		color += texture2D(texture1,  vec2(fs_in.texcoord.s, 1.0 - fs_in.texcoord.t))  * cos_theta_1 * diffuse * point_intensity;
	
		vec3 h = normalize(fs_in.world_view_direction + world_pointlight_direction);

		if (dot(h, world_normal) > 0)
		{
			vec3 reflection = -1 * fs_in.world_view_direction + 2 * dot(fs_in.world_view_direction, world_normal) * world_normal;

			color +=  (texture2D(texture1,  vec2(fs_in.texcoord.s, 1.0 - fs_in.texcoord.t)) + texture(skybox, reflection)) * vec4(vec3(point_intensity) * vec3(specular) * pow(dot(h, world_normal), specular.w), 1.0);
		}
	}

	return color;
}


/////////////////////////////////////////////////////////////////////////////
void main()
{
	vec3 world_normal =  normalize(mat3(model_inverse_transpose_matrix) * fs_in.model_normal);
	// Ambient light
	color =texture2D(texture0,  vec2(fs_in.texcoord.s, 1.0 - fs_in.texcoord.t)) * diffuse * ambient_intensity;

	float shadow = 0;
	for(int i = 0; i < 1; i++){
		shadow += ShadowCalculation(fs_in.light_space_position_depth[i]);
	}

	if(shadow > 1){
		shadow = 1;
	}

	for(int i = 0; i < point_num; i++){
		color += CalcPointLightShading(fs_in.world_pointlight_direction[i], pointlights[i].point_intensity, world_normal) * (1.0 - shadow);
	}
}