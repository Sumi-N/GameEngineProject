#version 420 core

layout(triangles, equal_spacing, cw) in;

// Const data
const int MAX_POINT_LIGHT_NUM = 5;
const float DISP_FACTOR = 3.0;

//////////////////////////////////////////////////////////////////////////////

layout(binding = 6) uniform sampler2D texture3; // Normal map

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

in CS_OUT{
    // object's position and rotation matrix in world coordinate 
    vec3 world_object_position;
	// Normal vector of the object at world coordinate
	vec3 world_normal;
	// Point light direction vector at world coordinate
	vec3 world_pointlight_direction[MAX_POINT_LIGHT_NUM];
	// Object direction vector at world coordinate
	vec3 world_object_direction;
	// Texture coordinate
	vec2 texcoord;
	// The depth value at light space
	vec3 light_space_position_depth[MAX_POINT_LIGHT_NUM];
} es_in[];

out vec3 WorldPos_FS_in;
out vec2 TexCoord_FS_in;
out vec3 Normal_FS_in;

out ES_OUT{
    // object's position and rotation matrix in world coordinate 
    vec3 world_object_position;
	// Normal vector of the object at world coordinate
	vec3 world_normal;
	// Point light direction vector at world coordinate
	vec3 world_pointlight_direction[MAX_POINT_LIGHT_NUM];
	// Object direction vector at world coordinate
	vec3 world_object_direction;
	// Texture coordinate
	vec2 texcoord;
	// The depth value at light space
	vec3 light_space_position_depth[MAX_POINT_LIGHT_NUM];
} es_out;

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
    es_out.texcoord              = interpolate2D(es_in[0].texcoord, es_in[1].texcoord, es_in[2].texcoord);
    es_out.world_normal          = interpolate3D(es_in[0].world_normal, es_in[1].world_normal, es_in[2].world_normal);
    es_out.world_normal          = normalize(es_out.world_normal);
    es_out.world_object_position = interpolate3D(es_in[0].world_object_position, es_in[1].world_object_position, es_in[2].world_object_position);
    es_out.world_object_direction= interpolate3D(es_in[0].world_object_direction, es_in[1].world_object_direction, es_in[2].world_object_direction);

    for(int i = 0; i < MAX_POINT_LIGHT_NUM; i++){
        es_out.world_pointlight_direction[i] = interpolate3D(es_in[0].world_pointlight_direction[i], es_in[1].world_pointlight_direction[i], es_in[2].world_pointlight_direction[i]);
        es_out.light_space_position_depth[i] = interpolate3D(es_in[0].light_space_position_depth[i], es_in[1].light_space_position_depth[i], es_in[2].light_space_position_depth[i]);
    }

    // Displace the vertex along the normal
    float Displacement = texture(texture3, vec2(es_out.texcoord.s, 1.0 - es_out.texcoord.t)).x;
    es_out.world_object_position += es_out.world_normal  * Displacement * DISP_FACTOR;
    gl_Position = perspective_matrix * view_matrix * vec4(es_out.world_object_position, 1.0);
}