#version 420 core

layout(location = 0) out vec4 color;

uniform sampler2D texture0;
uniform samplerCube skybox;

in vec4 clipcoord;
in vec2 texcoord;

layout (std140, binding = 2) uniform const_material
{
	vec4 diffuse;
	vec4 specular;
};

void main()
{
	//vec2 normalizedDeviceCoordinate = (clipcoord.xy/clipcoord.w)*0.5 + 0.5;
	//color = texture(texture0, normalizedDeviceCoordinate);

	float depthvalue = texture(texture0, texcoord).x;
	color = diffuse;
}