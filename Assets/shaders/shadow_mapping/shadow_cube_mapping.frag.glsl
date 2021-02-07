#version 420 core

in vec4 fragpos;

const float FAR_PLANE_DISTANCE = 100;
const int   CUBE_FACE_NUM = 6;

layout (std140, binding = 5) uniform const_shadow
{
	mat4 point_view_perspective_matrix[CUBE_FACE_NUM];
	vec4 point_position;
};

void main()
{
    float lightdistance = length(fragpos.xyz - vec3(point_position));

    lightdistance = lightdistance / FAR_PLANE_DISTANCE; 

    gl_FragDepth = lightdistance;
}