#version 440

///////////////////////////Varying inputs.////////////////////////////////////////////////
in vec2 uv;
//////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////Varying outputs.///////////////////////////////////////////////
out vec3 Colour;
//////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////Uniforms from LightShaderBase class.///////////////////////////
uniform sampler2D DiffuseTexture;
uniform sampler2D NormalTexture;
uniform sampler2D PositionTexture;
uniform sampler2D ShadowMap;

uniform mat4 ViewMatrix;
uniform mat4 LightMatrix;
uniform vec3 LightColour;
//////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////Uniforms from DirectionalLightShader class.////////////////////
uniform vec3 LightVector;
//////////////////////////////////////////////////////////////////////////////////////////

vec3 LightColourBiased = LightColour*0.4;

const float PI = 3.141592653589793238462643;
const float PI2 = 6.28318530718;
const float PISq = 9.86960440108935861;

float m=0.8; //Rougness [0,1]
float n=0.2; //Refractive index [1,20]

float F0 =0.84;

float m2 = m*m;


float D(float nh)
{
float nh2 = nh*nh;
return 1/(m2*nh2*nh2) * exp ((nh*nh-1.0)/( m2*nh2));
}

float F(float vh)
{
return F0+(1-F0)*pow(1-vh,5);
}

float G(float nv, float nl, float nh, float vh)
{
float nh2 = nh*2;
return min(1, min((nh2*nv)/vh, (nh2*nl)/vh));
}



float CookTorrance(float nh, float vh, float nv, float nl)
{
return (D(nh)*F(vh)*G(nv,nl,nh,vh))/(4*nl*nv);
}

float OrenNayar(const in float nv, const in float nl, const in vec3 l, const in vec3 v, const in vec3 n)
{    

    float angleVN = acos(nv);
    float angleLN = acos(nl);
    
    float alpha = max(angleVN, angleLN);
    float beta = min(angleVN, angleLN);
    float gamma = dot(v - n * nv, v - n * nl);
    
    float roughnessSquared9 = (m2 / (m2 + 0.09));
    
    // calculate C1, C2 and C3
    float C1 = 1.0 - 0.5 * (m2 / (m2 + 0.33));
    float C2 = 0.45 * roughnessSquared9;
    
    if(gamma >= 0.0)
    {
        C2 *= sin(alpha);
    }
    else
    {
        C2 *= (sin(alpha) - pow((2.0 * beta) / PI, 3.0));
    }
 
    float powValue = (4.0 * alpha * beta) / (PI * PI);
    float C3  = 0.125 * roughnessSquared9 * powValue * powValue;
 
    // now calculate both main parts of the formula
    float A = gamma * C2 * tan(beta);
    float B = (1.0 - abs(gamma)) * C3 * tan((alpha + beta) / 2.0);
 
    // put it all together
    float L1 = max(0.0, nl) * (C1 + A + B);
	
	// also calculate interreflection
    float twoBetaPi = 2.0 * beta / PI;
	//TODO: p is squared in this case... how to separate this?
    float L2 = 0.17 * max(0.0, nl) * (m2 / (m2 + 0.13)) * (1.0 - gamma * twoBetaPi * twoBetaPi);
    
    // get the final color by summing both components
    return(L1 + L2);
}

float readShadowMap(vec4 cameraSpacePos)
{
mat4 cameraToWorld = inverse(ViewMatrix);
mat4 cameraToLight = LightMatrix * cameraToWorld;
	
vec4 projectedEyeDir =  cameraToLight*vec4(cameraSpacePos.xyz,1);
projectedEyeDir = projectedEyeDir/projectedEyeDir.w;

vec2 textureCoordinates = (projectedEyeDir.xy +vec2(1,1)) * vec2(0.5,0.5);

const float bias = 0.0001;
float depthValue = texture2D( ShadowMap, textureCoordinates).r - bias;
return (projectedEyeDir.z*0.5+0.5) < depthValue ? 1:0;

}


void main ()
{
vec4 cameraSpacePos = texture2D(PositionTexture, uv);

vec3 n = normalize(texture2D(NormalTexture, uv).xyz);
vec3 v = normalize(-cameraSpacePos.xyz);
vec3 l = normalize(LightVector);
vec3 h = normalize(v+l);
vec3 shadowPos = (LightMatrix*vec4(-v,1)).xyz;

float nh = dot(n,h); float vh = dot(v,h);
float nv = dot(n,v); float nl = dot(n,l);

vec3 pixelColour =  texture2D(DiffuseTexture,uv).xyz;

float diffuseCoefficient = max(0,OrenNayar(nv, nl, l, v, n));
float ambientCoefficient = 0.004;
float specularCoefficient = 0;
if (diffuseCoefficient>0)
	specularCoefficient = CookTorrance(nh,vh,nv,nl);


	
vec3 diffuse = diffuseCoefficient*pixelColour*LightColourBiased;
vec3 ambient = ambientCoefficient*pixelColour*LightColourBiased;
vec3 specular = specularCoefficient*pixelColour*LightColourBiased;
float shadow = readShadowMap(cameraSpacePos);

Colour = diffuse*specular*shadow+ambient;




//Colour = ((Colour*(0.15*Colour+0.05)+0.004)/(Colour*(0.15*Colour+0.5)+0.06))-0.06666666666;
}
