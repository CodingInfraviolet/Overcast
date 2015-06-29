/**
Performs various temporary actions. It's code that's merely meant to take advantage of the existing code base without
being directly linked to the intend of the engine. Called before the main game loop after initialisation.
Strange bug: Seems to be saving invalid BMP files in Release mode.
*/
#include "util.h"

/**To be put into matrix. Returns vector that would happen if you reflect the vector off the surface corresponding to the normal.*/
math::vec3 reflect(math::vec3 vector, math::vec3 normal)
{
	return vector - normal*(math::dot(vector*2.0,normal)/math::dot(vector,vector));
}

bool miscDevUtilOperations()
{
	/*
	This precomputes a basic phong bdrf.
	struct Pixel
	{
		unsigned char r;
		unsigned char g;
		unsigned char b;
		unsigned char a;
	};
	using namespace math;

	unsigned dimension = 1024;
	Texture tx;
	tx.create(dimension, dimension, Enum::CPU, Enum::RGBA);

	//Shader inputs:
	vec3 n; //Normal vector
	vec3 l; //Light vector
	vec3 E; //Eye vector

	//Texture inputs:
	float cosTheta = clamp(dot(n,l),0.f,1.f); //Diffuse component
	vec3 R = reflect(l*(-1), n); //Direction in which the trnagle reflects the light
	float cosAlpha = clamp(dot(E, R), 0.0f, 1.0f);

	//Where:
	//Theta = angle between normal and light vector.
	//Alpha = angle between eye and reflection vector.

	Pixel px = { 255, 0, 0, 255 };

	//Calculate diffuse value
	//x = dot(n,l)
	//y = Constant

	for (unsigned x = 0; x < dimension; ++x)
	{
		px.r = unsigned char (x/float(dimension) * 255);
		px.g = unsigned char (x / float(dimension) * 255);
		px.b = unsigned char (x / float(dimension) * 255);
		for (unsigned y = 0; y < dimension; ++y)
		{
			tx.setPixel(x, y, (unsigned char*)&px);
		}
	}

	tx.save("Game/Textures/brdf.tga", Texture::ImageType::TGA);
	*/

	return true;
}