#version 430 core

out vec4 color;

in vec4 fragpos;

layout(binding = 2) uniform sampler2D equirectangularmap;

const vec2 invAtan = vec2(0.1591, 0.3183);
vec2 SampleSphericalMap(vec3 v)
{
    vec2 uv = vec2(atan(v.z, v.x), asin(v.y));
    uv *= invAtan;
    uv += 0.5;
    return uv;
}

void main(){
    vec2 uv = SampleSphericalMap(normalize(vec3(fragpos)));
    vec3 pointcolor = texture(equirectangularmap, uv).rgb;
    
    color = vec4(pointcolor, 1.0);
}