#version 420 core

layout(binding = 2) uniform sampler2D tex_sampler;

// Input
layout (location = 0) in vec2 frag_tex_coord;
// Output
layout (location = 0) out vec4 color;

void main()
{
    vec2 flipped_coord = vec2(frag_tex_coord.s, 1.0f - frag_tex_coord.t);
    color = texture(tex_sampler, flipped_coord);
}