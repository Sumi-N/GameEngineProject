#version 420 core
layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

out VS_OUT{
	// Normal vector of the object at world coordinate
	vec4 world_normal;
} gs_in[];

const float MAGNITUDE = 10.0;

void GenerateLine(int index)
{
    gl_Position = gl_in[index].gl_Position;
    EmitVertex();
    gl_Position = gl_in[index].gl_Position + gs_in[index].world_normal;
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