#version 440

out vec4 Colour;
uniform sampler2D Texture;
in vec2 uv;

void main ()
{
Colour =texture2D(Texture,uv).rgba;
}