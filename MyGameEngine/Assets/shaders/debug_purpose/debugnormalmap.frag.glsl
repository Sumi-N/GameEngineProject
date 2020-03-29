#version 420 core

out vec4 color;

in vec2 texcoord;
Displacement mapping
layout(binding = 1) uniform sampler2D texture0;

void main()
{
    color = texture( texture0, 1.0 - texcoord.xy);
}