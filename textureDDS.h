#pragma once

#include <GL/glew.h>

//DDS file
class TextureDDS
{
public:
	
bool loaded;
unsigned size;

GLuint id;

TextureDDS ();
~TextureDDS ();

//create OpenGL texture.
//Returns 0 if failed. Overwrites all previous information.
bool load (char location []);

void clear ();
};