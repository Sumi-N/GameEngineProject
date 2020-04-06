#version 420 core
layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

out VS_OUT{
	// Normal vector of the object at world coordinate
	vec3 world_normal;
} gs_in[];

const float MAGNITUDE = 10.0;

layout (std140, binding = 1) uniform const_model
{
	mat4 model_position_matrix;
	mat4 model_view_perspective_matrix;
	mat4 model_inverse_transpose_matrix;
};

layout (std140, binding = 0) uniform const_camera
{
	mat4 view_matrix;
	mat4 perspective_matrix;
	vec3 camera_position_vector;
	float camera_padding;
};


void GenerateLine(int index)
{
    vec4 world_normal = normalize(perspective_matrix * view_matrix * vec4(mat3(model_inverse_transpose_matrix) * gs_in[index].world_normal, 0.0));

    gl_Position = gl_in[index].gl_Position;
    EmitVertex();
    gl_Position = gl_in[index].gl_Position + vec4(gs_in[index].world_normal, 1.0);
    //gl_Position = gl_in[index].gl_Position + vec4(10, 0, 0, 0);
    EmitVertex();
    EndPrimitive();
}

void main()
{
    GenerateLine(0); // first vertex normal
    GenerateLine(1); // second vertex normal
    GenerateLine(2); // third vertex normal
}  