#version 440 core

layout (location=0) out vec3 colour;

uniform sampler2D DiffuseTexture;



in vec2 UVCoord;
in vec3 NormalCameraspace;
in vec3 CameraRay;
in vec3 LightVectorCameraspace;

uniform vec3 LightColour;
uniform vec3 AmbientColour;
uniform float SpecularExponent;
uniform float SpecularPower;

void main ()
{
vec3 cameraRay = normalize(CameraRay);
vec3 SurfaceToLightRay = normalize(LightVectorCameraspace);

float LightNormalAngle =  clamp(dot(SurfaceToLightRay, NormalCameraspace), 0, 1);


vec3 HalfAngleSpecular =  normalize (SurfaceToLightRay+cameraRay);
float AngleNormalHalf = acos(dot(HalfAngleSpecular, NormalCameraspace));
float Exponent = AngleNormalHalf/SpecularExponent;
Exponent = -(Exponent*Exponent);
float GaussianTerm = LightNormalAngle == 0 ? 0 : exp(Exponent);

vec3 TexColour = texture2D(DiffuseTexture, UVCoord).xyz;

colour =TexColour*LightColour*LightNormalAngle+GaussianTerm*SpecularPower*LightColour+TexColour*AmbientColour;
//colour=vec3(1,0,0);
}