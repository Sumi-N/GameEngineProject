#version 420 core

// define the number of CPs in the output patch
layout (vertices = 3) out;

// Const data
const int MAX_POINT_LIGHT_NUM = 5;

//////////////////////////////////////////////////////////////////////////////

layout (std140, binding = 0) uniform const_camera
{
	mat4 view_matrix;
	mat4 perspective_matrix;
	vec3 camera_position_vector;
	float camera_padding;
};

in VS_OUT{
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
} cs_in[];

out CS_OUT{
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
} cs_out[];

float GetTessLevel(float Distance0, float Distance1)
{
    float AvgDistance = (Distance0 + Distance1) / 2.0;

    if (AvgDistance <= 100.0) {
        return 100.0;
    }
    else if (AvgDistance <= 200.0) {
        return 70.0;
    }
    else {
        return 30.0;
    }
}

void main()
{
    // Set the control points of the output patch
    cs_out[gl_InvocationID].world_object_position  = cs_in[gl_InvocationID].world_object_position;
    cs_out[gl_InvocationID].world_normal           = cs_in[gl_InvocationID].world_normal;
    cs_out[gl_InvocationID].texcoord               = cs_in[gl_InvocationID].texcoord;
    cs_out[gl_InvocationID].world_object_direction = cs_in[gl_InvocationID].world_object_direction;

    for(int i = 0; i < MAX_POINT_LIGHT_NUM; i++){
        cs_out[gl_InvocationID].world_pointlight_direction[i] = cs_in[gl_InvocationID].world_pointlight_direction[i];
        cs_out[gl_InvocationID].light_space_position_depth[i] = cs_in[gl_InvocationID].light_space_position_depth[i];
    }

    // Calculate the distance from the camera to the three control points
    float EyeToVertexDistance0 = distance(camera_position_vector, cs_out[0].world_object_position);
    float EyeToVertexDistance1 = distance(camera_position_vector, cs_out[1].world_object_position);
    float EyeToVertexDistance2 = distance(camera_position_vector, cs_out[2].world_object_position);

    // Calculate the tessellation levels
    gl_TessLevelOuter[0] = GetTessLevel(EyeToVertexDistance1, EyeToVertexDistance2);
    gl_TessLevelOuter[1] = GetTessLevel(EyeToVertexDistance2, EyeToVertexDistance0);
    gl_TessLevelOuter[2] = GetTessLevel(EyeToVertexDistance0, EyeToVertexDistance1);
    gl_TessLevelInner[0] = gl_TessLevelOuter[2];
}