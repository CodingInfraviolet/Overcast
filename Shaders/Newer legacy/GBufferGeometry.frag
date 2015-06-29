#version 440 core

in vec2 UVCoord;
in vec3 NormalWorldspace;
in vec3 VertexPosWorld;

out vec3 Colour;

uniform vec3 LightColour;
uniform vec3 AmbientColour;
uniform float SpecularExponent;
uniform float SpecularPower;
uniform mat4 ViewMatrix;
uniform vec3 LightVector;

uniform sampler2D Diffuse;

void main ()
{
/*
vec3 CameraRay = normalize(vec3(0,0,0)-(ViewMatrix*(vec4(VertexPosWorld, 1))).xyz);

vec3 NormalCameraspace = (ViewMatrix*vec4(NormalWorldspace, 0)).xyz;

vec3 SurfaceToLightRay = normalize((ViewMatrix*vec4(LightVector,0)).xyz);
float LightNormalAngle =  clamp(dot(SurfaceToLightRay, NormalCameraspace), 0, 1);


vec3 HalfAngleSpecular =  normalize (SurfaceToLightRay+CameraRay);
float AngleNormalHalf = acos(dot(HalfAngleSpecular, NormalCameraspace));
float Exponent = AngleNormalHalf/SpecularExponent;
Exponent = -(Exponent*Exponent);
float GaussianTerm = LightNormalAngle == 0 ? 0 : exp(Exponent);

vec3 TexColour = texture(Diffuse,UVCoord).xyz;

Colour =TexColour*LightColour*LightNormalAngle+GaussianTerm*SpecularPower*LightColour+TexColour*AmbientColour;
Colour = ((Colour*(0.15*Colour+0.05)+0.004)/(Colour*(0.15*Colour+0.5)+0.06))-0.06666666666;
Colour=TexColour;
*/

vec3 CameraRay = normalize(vec3(0,0,0)-(ViewMatrix*(vec4(VertexPosWorld, 1))).xyz);

vec3 NormalCameraspace = (ViewMatrix*vec4(NormalWorldspace, 0)).xyz;

vec3 SurfaceToLightRay = normalize((ViewMatrix*vec4(LightVector,0)).xyz);
float LightNormalAngle =  clamp(dot(SurfaceToLightRay, NormalCameraspace), 0, 1);

Colour=gl_FragCoord.xyy/500;
}