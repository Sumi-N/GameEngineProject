#version 420 core

layout (triangles) in;
layout (triangle_strip, max_vertices=18) out;

out vec4 fragpos;

// Const data
const int CUBE_FACE_NUM = 6;

layout (std140, binding = 5) uniform const_shadow
{
	mat4 point_view_perspective_matrix[CUBE_FACE_NUM];
	vec4 point_position;
};

void main()
{
    for(int face = 0;  face < CUBE_FACE_NUM; face++){
		gl_Layer = face;
		for(int i = 0; i < 3; ++i){
			fragpos = gl_in[i].gl_Position;
			gl_Position = point_view_perspective_matrix[face] * fragpos;
			EmitVertex();
		}
		EndPrimitive();
	}
}