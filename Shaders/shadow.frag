#version 440 core

layout (location = 0) out vec4 DistanceOut;

void main ()
{
DistanceOut = vec4(gl_FragCoord.z);
}