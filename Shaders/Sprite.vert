#version 440

layout (location=0) in vec4 Vertex;
uniform vec4 PosScale;
uniform float Aspect;
out vec2 uv;

void main ()
{
vec2 pos  = (vec2(Vertex.x*Aspect, Vertex.y)*vec2(PosScale.z, PosScale.w*1000.0/800.0)) + PosScale.xy;

gl_Position = vec4(pos,0,1);
uv = vec2(Vertex.z,-Vertex.w);
}