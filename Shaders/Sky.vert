#version 440

layout (location = 0) in vec3 vertexPosition_modelspace;
layout (location = 1) in vec2 VertexUV;
layout (location = 2) in vec3 Normals;

uniform mat4 MP;

out vec2 uv;

void main ()
{
gl_Position = MP* vec4(vertexPosition_modelspace,1)*3;
uv = VertexUV;
}