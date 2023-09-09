#version 420 core
out vec4 color;

// Consta data
const int MAX_POINT_LIGHT_NUM = 5;

in VS_OUT{
	// Normal vector of the object at world coordinate
	vec3 world_normal;
	// Object direction vector at world coordinate
	vec3 world_view_direction;
	// Point light direction vector at world coordinate
	vec3 world_pointlight_direction[MAX_POINT_LIGHT_NUM];
} fs_in;

void main()
{
    color = vec4( abs(fs_in.world_pointlight_direction[0]), 1.0);
} 