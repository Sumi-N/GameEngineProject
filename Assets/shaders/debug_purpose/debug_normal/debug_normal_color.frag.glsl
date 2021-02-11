#version 420 core
out vec4 color;

in VS_OUT{
	// Normal vector of the object at world coordinate
	vec3 world_normal;
} fs_in;

void main()
{
    color = vec4(abs(fs_in.world_normal), 1.0);
} 