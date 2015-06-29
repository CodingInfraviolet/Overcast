#version 440 core

layout (location = 0) out vec3 DiffuseOut;
layout (location = 1) out vec3 PosCameraOut;  
layout (location = 2) out vec3 NormalCameraOut; 

in vec2 UVCoord;
in vec3 VertexPosCamera;
in vec3 NormalCameraspace;

uniform sampler2D DiffuseTexture;

void main ()
{
DiffuseOut=texture(DiffuseTexture,UVCoord).xyz;
PosCameraOut=VertexPosCamera;
NormalCameraOut=NormalCameraspace;
}