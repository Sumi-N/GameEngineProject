#version 420 core

layout(triangles, equal_spacing, cw) in;

const float DISP_FACTOR = 3.0;

//uniform mat4 gVP;
//uniform sampler2D gDisplacementMap;
layout(binding = 6) uniform sampler2D texture3; // Normal map
//uniform float gDispFactor;

layout (std140, binding = 0) uniform const_camera
{
	mat4 view_matrix;
	mat4 perspective_matrix;
	vec3 camera_position_vector;
	float camera_padding;
};

in vec3 WorldPos_ES_in[];
in vec2 TexCoord_ES_in[];
in vec3 Normal_ES_in[];

out vec3 WorldPos_FS_in;
out vec2 TexCoord_FS_in;
out vec3 Normal_FS_in;

vec2 interpolate2D(vec2 v0, vec2 v1, vec2 v2)
{
    return vec2(gl_TessCoord.x) * v0 + vec2(gl_TessCoord.y) * v1 + vec2(gl_TessCoord.z) * v2;
}

vec3 interpolate3D(vec3 v0, vec3 v1, vec3 v2)
{
    return vec3(gl_TessCoord.x) * v0 + vec3(gl_TessCoord.y) * v1 + vec3(gl_TessCoord.z) * v2;
}

void main()
{
    // Interpolate the attributes of the output vertex using the barycentric coordinates
    TexCoord_FS_in = interpolate2D(TexCoord_ES_in[0], TexCoord_ES_in[1], TexCoord_ES_in[2]);
    Normal_FS_in = interpolate3D(Normal_ES_in[0], Normal_ES_in[1], Normal_ES_in[2]);
    Normal_FS_in = normalize(Normal_FS_in);
    WorldPos_FS_in = interpolate3D(WorldPos_ES_in[0], WorldPos_ES_in[1], WorldPos_ES_in[2]);

    // Displace the vertex along the normal
    float Displacement = texture(texture3, vec2(TexCoord_FS_in.s, 1.0 - TexCoord_FS_in.t)).x;
    WorldPos_FS_in += Normal_FS_in * Displacement * DISP_FACTOR;
    gl_Position = perspective_matrix * view_matrix * vec4(WorldPos_FS_in, 1.0);
}