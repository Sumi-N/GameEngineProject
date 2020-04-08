#version 420 core

// Consta data
const int   MAX_POINT_LIGHT_NUM = 5;
const float POINT_LIGHT_BIAS = 0.5;
const float FAR_PLANE_DISTANCE = 100;

// Output
out vec4 color;

/////////////////////////////////////////////////////////////////////////////

in VS_OUT{
	// Object world position
	vec4 world_position;
	// Normal vector of the object at model coordinate
	vec3 model_normal;
	// Texture coordinate
	vec2 texcoord;
	// Object direction vector at world coordinate
	vec3 world_view_direction;
	// Point light direction vector at world coordinate
	vec3 world_pointlight_direction[MAX_POINT_LIGHT_NUM];
} fs_in;

//////////////////////////////////////////////////////////////////////////////
// Structure define
struct PointLight{
	vec4 intensity;
	vec4 position;
	vec3 attenuation;
	float padding;
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
layout(binding = 1) uniform samplerCube shadowmap;
layout(binding = 3) uniform sampler2D texture0; // Diffuse  texture
layout(binding = 4) uniform sampler2D texture1; // Specular texture
layout(binding = 5) uniform sampler2D texture2; // Normal map

//////////////////////////////////////////////////////////////////////////////

float ShadowCalculation(vec3 fragpos)
{
	vec3 fragtolight = fragpos - vec3(pointlights[0].position);
	float closestDepth = texture(shadowmap, fragtolight).r;

	closestDepth *= FAR_PLANE_DISTANCE;
	float currentDepth = length(fragtolight);

	float shadow  = 0.0;
	float samples = 4.0;
	float offset  = 0.1;

	for(float x = -offset; x < offset; x += offset / (samples * 0.5))
	{
		for(float y = -offset; y < offset; y += offset / (samples * 0.5))
		{
			for(float z = -offset; z < offset; z += offset / (samples * 0.5))
			{
				float closestDepth = texture(shadowmap, fragtolight + vec3(x, y, z)).r; 
				closestDepth *= FAR_PLANE_DISTANCE;   // Undo mapping [0;1]
				if(currentDepth - POINT_LIGHT_BIAS > closestDepth)
					shadow += 1.0;
			}
		}
	}
	shadow /= (samples * samples * samples);
	return shadow;
}

/////////////////////////////////////////////////////////////////////////////


vec4 CalcPointLightShading(PointLight pointlight, vec3 world_normal, vec3 pointlight_direction){
//vec4 CalcPointLightShading(vec3 world_pointlight_direction, vec4 intensity, vec3 world_normal, vec3 attenuation, vec4 position){

	float dist = distance(vec3(pointlight.position), vec3(fs_in.world_position));
	float attenuation = 1.0 / (pointlight.attenuation.x + pointlight.attenuation.y * dist + pointlight.attenuation.z * dist * dist);
	vec4  radiance = pointlight.intensity * attenuation;

	vec4 color = vec4(0, 0, 0, 1.0);

	float cos_theta = dot(world_normal, pointlight_direction);
	
	if (cos_theta > 0)
	{
		color += texture2D(texture1,  vec2(fs_in.texcoord.s, 1.0 - fs_in.texcoord.t))  * abs(cos_theta) * diffuse * radiance;
	
		vec3 half_vec = normalize(fs_in.world_view_direction + pointlight_direction);

		if (dot(half_vec, world_normal) > 0)
		{
			vec3 reflection = -1 * fs_in.world_view_direction + 2 * dot(fs_in.world_view_direction, world_normal) * world_normal;

			color +=  (texture2D(texture1,  vec2(fs_in.texcoord.s, 1.0 - fs_in.texcoord.t)) + texture(skybox, reflection)) * vec4(vec3(radiance) * vec3(specular) * pow(dot(half_vec, world_normal), specular.w), 1.0);
		}
	}

	return color;
}


/////////////////////////////////////////////////////////////////////////////
void main()
{
	// Calculate world normal of the object
	vec3 world_normal =  normalize(mat3(model_inverse_transpose_matrix) * fs_in.model_normal);
	// Ambient light
	color =texture2D(texture0,  vec2(fs_in.texcoord.s, 1.0 - fs_in.texcoord.t)) * diffuse * ambient_intensity;

	float shadow = 0;

	for(int i = 0; i < 1; i++){
		shadow += ShadowCalculation(vec3(fs_in.world_position));
	}
	
	shadow = min(shadow, 1.0);


	for(int i = 0; i < point_num; i++){
		color += CalcPointLightShading(pointlights[i], world_normal, fs_in.world_pointlight_direction[i]) * (1.0 - shadow);
	}
}