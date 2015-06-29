#version 440 core

layout (location = 0) in vec3 vertexPosition_modelspace;
layout (location = 1) in vec2 VertexUV;
layout (location = 2) in vec3 Normals;

out vec2 UVCoord;
out vec3 NormalCameraspace;
out vec3 CameraRay;
out vec3 LightVectorCameraspace;

uniform mat4 MVP;
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform vec3 LightVector;

void main ()
{
gl_Position = MVP * (vec4(vertexPosition_modelspace,1));


CameraRay = vec3(0,0,0)-(ViewMatrix*ModelMatrix*(vec4(vertexPosition_modelspace,1))).xyz;
NormalCameraspace = normalize((ViewMatrix*ModelMatrix*vec4(Normals,0)).xyz);

LightVectorCameraspace=(ViewMatrix*vec4(LightVector,0)).xyz;


UVCoord = VertexUV;
}