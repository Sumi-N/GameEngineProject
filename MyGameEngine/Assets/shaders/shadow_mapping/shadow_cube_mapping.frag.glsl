#version 420 core

in vec4 fragpos;

const int   MAX_POINT_LIGHT_NUM = 5;
const float FAR_PLANE_DISTANCE = 100;

//////////////////////////////////////////////////////////////////////////////
// Structure define
struct PointLight{
	vec4 point_intensity;
	vec4 point_position;
	vec3 point_attenuation;
	float padding;
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

void main()
{
    float lightdistance = length(fragpos.xyz - vec3(pointlights[0].point_position));

    lightdistance = lightdistance / FAR_PLANE_DISTANCE; 

    gl_FragDepth = lightdistance;
}