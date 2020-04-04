#version 420 core

// Output
out vec4 color;

// Consta data
const int MAX_POINT_LIGHT_NUM = 5;
const float POINT_LIGHT_BIAS = 0.00005;
const float PI = 3.14159265359;
const float ROUGHTNESS_BIAS = 0.00005;


/////////////////////////////////////////////////////////////////////////////

in VS_OUT{
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
} fs_in;

//////////////////////////////////////////////////////////////////////////////
// Structure define
struct PointLight{
	vec4 point_intensity;
	vec4 point_position;
};
//////////////////////////////////////////////////////////////////////////////

layout (std140, binding = 1) uniform const_object
{
	mat4 model_position_matrix;
	mat4 model_view_perspective_matrix;
	mat4 model_inverse_transpose_matrix;
};

layout (std140, binding = 2) uniform const_material
{
	vec4 diffuse;
	vec4 specular;
	
	vec4 albedo;
	float metalic;
	float roughness;
	float ambient_occlusion;
	float padding;
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
layout(binding = 3) uniform sampler2D texturealbedo;
layout(binding = 4) uniform sampler2D texturenormal;
layout(binding = 5) uniform sampler2D textureroughness;
layout(binding = 6) uniform sampler2D texturemetalic;

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

//////////////////////////////////////////////////////////////////////////////

vec3 FresnelSchlick(float cos, vec3 f0){
	return f0 + (1.0 - f0) * pow(1.0 - cos, 5.0);
}

/////////////////////////////////////////////////////////////////////////////

float DistributionGGX(vec3 normal, vec3 half_vector){
	float a_2 = roughness * roughness + ROUGHTNESS_BIAS;
	float n_dot_h = max(dot(normal, half_vector), 0.0);
	float n_dot_h2 = n_dot_h * n_dot_h;

	float num = a_2;
	float denom = (n_dot_h2 * (a_2 - 1.0) + 1.0);
	denom = PI * denom * denom;

	return num /denom;
}

/////////////////////////////////////////////////////////////////////////////

float GeometrySchlickGGX(float n_dot_v)
{
	float r = roughness + 1.0;
	float k = (r * r) / 8.0;
    float nom   = n_dot_v;
    float denom = n_dot_v * (1.0 - k) + k;
	
    return nom / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx1 = GeometrySchlickGGX(NdotV);
    float ggx2 = GeometrySchlickGGX(NdotL);
	
    return ggx1 * ggx2;
}

/////////////////////////////////////////////////////////////////////////////

vec4 CalcPointLightShading(vec3 world_pointlight_direction, vec4 point_intensity, vec4 point_position, vec3 world_normal){
	vec4 color;

	// Cos theta term
	float cos_theta_1 = max(dot(world_normal, world_pointlight_direction), 0.0); // n dot l
	float cos_theta_2 = max(dot(world_normal, fs_in.world_view_direction), 0.0); // n dot v

	// Half vector
	vec3 h = normalize(fs_in.world_view_direction + world_pointlight_direction);


	vec3 f0 = vec3(0.04);
	f0      = mix(f0, vec3(albedo), metalic);

	// Normal distribution function
	float ndf = DistributionGGX(world_normal, h);
	// Geometry function
	float g   = GeometrySmith(world_normal, fs_in.world_view_direction, world_pointlight_direction);
	// Fresnel equation
	vec3  f = FresnelSchlick(max(dot(h, world_pointlight_direction), 0.0), f0);

	vec3 numerator = ndf * g * f;
	float denominator = 4.0 * cos_theta_1 * cos_theta_2;
	vec3 specular     = numerator / max(denominator, 0.0001);

	vec3 ks = f;
	vec3 kd = vec3(1.0 - ks);
	kd *= 1.0 - metalic;

	float dist = distance(vec3(point_position), vec3(fs_in.world_object_position));
	float attenuation = 1.0 / dist * dist;
	vec4  radiance = point_intensity * attenuation;

	color = (vec4(kd, 1.0) * albedo / PI + vec4(specular,1.0)) * radiance * cos_theta_1;

	 return color;
}


/////////////////////////////////////////////////////////////////////////////
void main()
{
	// Ambient light
	//color =texture2D(texture0,  vec2(fs_in.texcoord.s, 1.0 - fs_in.texcoord.t)) * diffuse * ambient_intensity;
	color = ambient_intensity * albedo;

	// Calculate world normal
	vec3 world_normal = normalize(mat3(model_inverse_transpose_matrix) * fs_in.model_normal);

	float shadow = 0;
	for(int i = 0; i < 1; i++){
		//shadow += ShadowCalculation(fs_in.light_space_position_depth[i]);
	}

	shadow = min(shadow, 1.0);

	for(int i = 0; i < point_num; i++){
		color += CalcPointLightShading(fs_in.world_pointlight_direction[i], pointlights[i].point_intensity, pointlights[i].point_position, world_normal);
	}

	// Ganmma correction
	color = color / (color + vec4(1.0));
	color = pow(color, vec4(1.0/2.2)); 
	color = vec4(vec3(color), 1.0);
}