#include "stdafx.h"
#include <GL/glew.h>

#include "textureDDS.h" 

#include <iostream>
#include <fstream>



TextureDDS::TextureDDS ()
{
loaded = false;
}

TextureDDS::~TextureDDS ()
{
if (loaded)
{
glDeleteTextures (1, &id);
}
}

bool TextureDDS::load (char location [])
{
using namespace std;

cout << "Loading image \"" << location << "\"\n";


ifstream file (location, ios::binary | ios::ate);
if (!file)
{
cout << "Could not open \"" << location << "\"\n";
return false;
}

//Get file size
unsigned long fileSize = (unsigned long)file.tellg();

if (fileSize <5)
{
cout << "Invalid file: Too small.\n";
return false;
}
//Done getting size

//Verify type of file
unsigned long pos = 0;
file.seekg (pos);


char filecode [4];
file.read (filecode, 4);
pos += 4;

if (!strcmp (filecode, "DDS "))
{
cout << "Invalid file: Not DDS.\n";
return false;
}


char header [124];
file.seekg (pos);
file.read (header, 124);
pos += 124;

unsigned int height      = *(unsigned int*)&(header[8 ]);
unsigned int width       = *(unsigned int*)&(header[12]);
unsigned int linearSize  = *(unsigned int*)&(header[16]);
unsigned int mipMapCount = *(unsigned int*)&(header[24]);
unsigned int fourCC      = *(unsigned int*)&(header[80]);

//Check whether image is to the power of 2:
if (((height!=0) && (height & (height-1))!= 0) || height != width)
{
cout << "Error: Texture not to the power of 2.\n";
return false;
}
//


//data

//It's size, including mipmaps:
size = (mipMapCount > 1) ? linearSize*2:linearSize;

//Fill up the data:

char* data = new char [size * sizeof(char)];

file.seekg (pos);
file.read (data, fileSize - pos); //Maybe -1 too? Unsure.

file.close();

unsigned int format;

const unsigned int FOURCC_DXT1 = 0x31545844;
const unsigned int FOURCC_DXT3 = 0x33545844;
const unsigned int FOURCC_DXT5 = 0x35545844;

unsigned int components = (fourCC == FOURCC_DXT1) ? 3:4;

switch (fourCC)
{
case FOURCC_DXT1:
format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
break;

case FOURCC_DXT3:
format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
break;

case FOURCC_DXT5:
format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
break;

default:
cout << "Error: Could not detect DXT format.\n";
return 0;
}


if (loaded)
{
glDeleteTextures (1, &id);
}

glGenTextures (1, &id);

glBindTexture (GL_TEXTURE_2D, id);


unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
unsigned int offset = 0;

//Load the mipmaps:
for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
{
unsigned int size = ((width+3)/4)*((height+3)/4)*blockSize;

glCompressedTexImage2D (GL_TEXTURE_2D, level, format, width, height, 0, size, data + offset);

offset += size;
width /= 2;
height /= 2;
}

//glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

//glBindTexture (GL_TEXTURE_2D, 0);
delete[] data;



loaded = true;

return true;
}

void TextureDDS::clear ()
{
if (loaded)
{
glDeleteTextures (1, &id);
}
}