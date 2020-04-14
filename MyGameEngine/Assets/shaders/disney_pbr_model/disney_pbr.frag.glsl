#version 420 core

// Consta data
const int   MAX_POINT_LIGHT_NUM = 5;
const float POINT_LIGHT_BIAS = 3;
const float FAR_PLANE_DISTANCE = 100;
const float PI = 3.14159265359;
const float ROUGHNESS_BIAS = 0.005;
const float MAX_REFLECTION_LOD = 4.0;

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
	// view direction vector at world coordinate
	vec3 world_view_direction;
	// Point light direction vector at world coordinate
	vec3 world_pointlight_direction[MAX_POINT_LIGHT_NUM];
	// tangent bitangent normal matrix
	mat3 tangent_bitangent_matrix;
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
layout(binding = 1) uniform samplerCube irradiancemap;
layout(binding = 2) uniform samplerCube shadowmap0;
layout(binding = 3) uniform samplerCube shadowmap1;
layout(binding = 4) uniform samplerCube shadowmap2;
layout(binding = 5) uniform samplerCube shadowmap3;
layout(binding = 6) uniform samplerCube shadowmap4;
layout(binding = 7) uniform samplerCube specularmap;
layout(binding = 8) uniform sampler2D texturebrdf; 
layout(binding = 10) uniform sampler2D texturealbedo;
layout(binding = 11) uniform sampler2D texturenormal;
layout(binding = 12) uniform sampler2D textureroughness;
layout(binding = 13) uniform sampler2D texturemetallic;

//////////////////////////////////////////////////////////////////////////////

float ShadowCalculation(vec3 fragpos, samplerCube shadowmap, int nth)
{
	vec3 fragtolight = fragpos - vec3(pointlights[nth].position);
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

//////////////////////////////////////////////////////////////////////////////

vec3 FresnelSchlick(float cos, vec3 f0){
	return f0 + (1.0 - f0) * pow(1.0 - cos, 5.0);
}

vec3 FresnelSchlickRoughness(float cos, vec3 f0, float roughness)
{
    return f0 + (max(vec3(1.0 - roughness), f0) - f0) * pow(1.0 - cos, 5.0);
} 

/////////////////////////////////////////////////////////////////////////////

float DistributionGGX(vec3 normal, vec3 half_vector, float roughness){
	float a_2 = roughness * roughness + ROUGHNESS_BIAS;
	float n_dot_h = max(dot(normal, half_vector), 0.0);
	float n_dot_h2 = n_dot_h * n_dot_h;

	float num = a_2;
	float denom = (n_dot_h2 * (a_2 - 1.0) + 1.0);
	denom = PI * denom * denom;

	return num /denom;
}

/////////////////////////////////////////////////////////////////////////////

float GeometrySchlickGGX(float n_dot_v, float roughness)
{
	float r = roughness + 1.0;
	float k = (r * r) / 8.0;
    float nom   = n_dot_v;
    float denom = n_dot_v * (1.0 - k) + k;
	
    return nom / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx1 = GeometrySchlickGGX(NdotV, roughness);
    float ggx2 = GeometrySchlickGGX(NdotL, roughness);
	
    return ggx1 * ggx2;
}

/////////////////////////////////////////////////////////////////////////////

vec4 CalcPointLightShading(PointLight pointlight, vec3 world_normal, vec3 pointlight_direction){

	float dist = distance(vec3(pointlight.position), vec3(fs_in.world_position));
	float attenuation = 1.0 / (pointlight.attenuation.x + pointlight.attenuation.y * dist + pointlight.attenuation.z * dist * dist);
	vec4  radiance = pointlight.intensity * attenuation;

	vec4 color = vec4(0, 0, 0, 1.0);

	//Calculate albedo based on texture
	vec4 albedotexel = texture2D(texturealbedo, vec2(fs_in.texcoord.s, 1.0 - fs_in.texcoord.t));
	// Calculate roughness based on texture
	float roughnesstexel = texture2D(textureroughness, vec2(fs_in.texcoord.s, 1.0 - fs_in.texcoord.t)).x;
	// Calculate metali based on texture
	float metallictexel  = texture2D(texturemetallic, vec2(fs_in.texcoord.s, 1.0 - fs_in.texcoord.t)).x;


	// Cos theta term
	float cos_theta_1 = max(dot(world_normal, pointlight_direction), 0.0); // n dot l
	float cos_theta_2 = max(dot(world_normal, fs_in.world_view_direction), 0.0); // n dot v

	// Half vector
	vec3 h = normalize(fs_in.world_view_direction + pointlight_direction);


	vec3 f0 = vec3(0.04);
	f0      = mix(f0, vec3(albedotexel), metallictexel);

	// Normal distribution function
	float ndf = DistributionGGX(world_normal, h, roughnesstexel);
	// Geometry function
	float g   = GeometrySmith(world_normal, fs_in.world_view_direction, pointlight_direction, roughnesstexel);
	// Fresnel equation
	vec3  f = FresnelSchlick(max(dot(h, pointlight_direction), 0.0), f0);

	vec3 numerator = ndf * g * f;
	float denominator = 4.0 * cos_theta_1 * cos_theta_2;
	vec3 specular     = numerator / max(denominator, 0.0001);

	vec3 ks = f;
	vec3 kd = vec3(1.0 - ks);
	kd *= 1.0 - metallictexel;

	color = (vec4(kd, 1.0) * albedotexel / PI + vec4(specular,1.0)) * radiance * cos_theta_1;

	 return color;
}


/////////////////////////////////////////////////////////////////////////////
void main()
{
	// Calculate world normal
	vec3 world_normal = texture(texturenormal, vec2(fs_in.texcoord.s, 1.0 - fs_in.texcoord.t)).rgb;
	world_normal = normalize(world_normal * 2.0 - 1.0);
	world_normal = normalize( fs_in.tangent_bitangent_matrix * world_normal);

	// Calculate roughness based on texture
	float roughnesstexel = texture2D(textureroughness, vec2(fs_in.texcoord.s, 1.0 - fs_in.texcoord.t)).x;
	// Calculate metali based on texture
	float metallictexel  = texture2D(texturemetallic, vec2(fs_in.texcoord.s, 1.0 - fs_in.texcoord.t)).x;

	// Image based reindering part
	vec4 albedotexel = texture2D(texturealbedo, vec2(fs_in.texcoord.s, 1.0 - fs_in.texcoord.t));
	vec3 ks          = FresnelSchlickRoughness(max(dot(world_normal, fs_in.world_view_direction), 0.0), vec3(0.04), roughnesstexel); 
	vec3 kd          = 1.0 - ks;
	kd *= 1.0 - metallictexel;
	vec4 irradiance  = vec4(texture(irradiancemap, world_normal).rgb, 1.0);
	vec4 diffuse     = irradiance * albedotexel;

	vec3 reflect          = reflect(-1 * fs_in.world_view_direction, world_normal);
	vec3 prefilteredcolor = textureLod(specularmap, reflect, roughnesstexel * MAX_REFLECTION_LOD).rgb;
	vec3 f                = FresnelSchlickRoughness(max(dot(world_normal, fs_in.world_view_direction), 0.0), vec3(0.04), roughnesstexel); 
	vec2 environment_brdf = texture2D(texturebrdf, vec2(max(dot(world_normal, fs_in.world_view_direction), 0.0), roughnesstexel)).rg;
	vec3 specular         = prefilteredcolor * (f * environment_brdf.x + environment_brdf.y);

	color   = vec4(kd, 1.0) * diffuse + vec4(specular, 1.0); 
	//color   = (kd * diffuse + specular) * ao; 

	// Calculate shadow
	float shadow = 0;

	for(int i = 0; i < point_num; i++){
		if(i == 0)
			shadow += ShadowCalculation(vec3(fs_in.world_position), shadowmap0, 0);
		if(i == 1)
			shadow += ShadowCalculation(vec3(fs_in.world_position), shadowmap1, 1);
		if(i == 2)
			shadow += ShadowCalculation(vec3(fs_in.world_position), shadowmap2, 2);
		if(i == 3)
			shadow += ShadowCalculation(vec3(fs_in.world_position), shadowmap3, 3);
		if(i == 4)
			shadow += ShadowCalculation(vec3(fs_in.world_position), shadowmap4, 4);
	}
	
	shadow = min(shadow / point_num, 1.0);

	// Calculate light points shading
	for(int i = 0; i < point_num; i++){
		color += CalcPointLightShading(pointlights[i], world_normal,fs_in.world_pointlight_direction[i]) * (1.0 - shadow);
	}

	//Ganmma correction
	// color = color / (color + vec4(1.0));
	// color = pow(color, vec4(1.0/2.2)); 
	// color = vec4(vec3(color), 1.0);
}