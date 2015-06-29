#version 440 core

layout (location = 0) in vec3 vertexPosition_modelspace;
layout (location = 1) in vec2 VertexUV;
layout (location = 2) in vec3 Normals;

out vec2 UVCoord;
out vec3 NormalWorldspace;
out vec3 VertexPosWorld;

uniform mat4 MVP;
uniform mat4 ModelMatrix;

void main ()
{
gl_Position = MVP * (vec4(vertexPosition_modelspace,1));
NormalWorldspace = normalize((ModelMatrix*vec4(Normals,0)).xyz);
VertexPosWorld = (ModelMatrix*vec4(vertexPosition_modelspace, 1)).xyz;
UVCoord = VertexUV;
}