#version 420 core

out vec4 color;

layout(binding = 0) uniform samplerCube skybox;
layout(binding = 3) uniform sampler2D shadowmap;

in vec4 clipcoord;
in vec2 texcoord;

float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // Back to NDC 
    return (2.0 * 0.1 * 100) / (100 + 0.1 - z * (100 - 0.1));
}

void main()
{
	//vec2 normalizedDeviceCoordinate = (clipcoord.xy/clipcoord.w)*0.5 + 0.5;
	//color = texture(texture0, normalizedDeviceCoordinate);

	float depthvalue = texture(shadowmap, texcoord).x;
	//color = vec4(vec3(depthvalue), 1.0);
	color = vec4(vec3(LinearizeDepth(depthvalue) / 100), 1.0); // perspective
}