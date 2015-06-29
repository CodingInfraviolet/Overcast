#version 440

out vec3 Colour;

uniform sampler2D Diffuse;
uniform sampler2D Normal;
uniform sampler2D Position;

uniform vec3 LightColour;
uniform vec3 AmbientColour;
uniform float SpecularExponent;
uniform float SpecularPower;
uniform mat4 ViewMatrix;
uniform vec3 LightVector;
uniform float Exposure;

in vec2 uv;


void main ()
{
vec3 CameraRay = normalize(vec3(0,0,0)-(ViewMatrix*(vec4(texture2D(Position, uv).xyz, 1))).xyz);

vec3 NormalCameraspace = (ViewMatrix*vec4(texture2D(Normal, uv).xyz, 0)).xyz;

vec3 SurfaceToLightRay = normalize((ViewMatrix*vec4(LightVector,0)).xyz);
float LightNormalAngle =  clamp(dot(SurfaceToLightRay, NormalCameraspace), 0, 1);


vec3 HalfAngleSpecular =  normalize (SurfaceToLightRay+CameraRay);
float AngleNormalHalf = acos(dot(HalfAngleSpecular, NormalCameraspace));
float Exponent = AngleNormalHalf/SpecularExponent;
Exponent = -(Exponent*Exponent);
float GaussianTerm = LightNormalAngle == 0 ? 0 : exp(Exponent);

vec3 TexColour = texture2D(Diffuse, uv).xyz;

Colour =(TexColour*LightColour*LightNormalAngle+GaussianTerm*SpecularPower*LightColour+TexColour*AmbientColour)*Exposure;
Colour = ((Colour*(0.15*Colour+0.05)+0.004)/(Colour*(0.15*Colour+0.5)+0.06))-0.06666666666;
}