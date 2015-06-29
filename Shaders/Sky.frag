#version 440

layout (location=0) out vec3 Colour;
uniform sampler2D Diffuse;

in vec2 uv;

void main ()
{
Colour = texture2D(Diffuse,uv).xyz;
}