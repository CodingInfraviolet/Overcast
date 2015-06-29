#version 440

layout (location=0) in vec4 ScreenCorners;

out vec2 uv;


void main ()
{
gl_Position = vec4(ScreenCorners.x,ScreenCorners.y,0,1);
uv.x=ScreenCorners.z;
uv.y=ScreenCorners.w;
}