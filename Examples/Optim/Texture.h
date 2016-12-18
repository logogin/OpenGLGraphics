// Texture.h: interface for the Texture class.
//
//////////////////////////////////////////////////////////////////////
#include "includes.h"

class Texture  
{
public:

	// GLubyte will work for images up to 32-bits.
	GLubyte *imageData;

	// Stores the color depth of the image in bits
	// per pixel.
	GLuint   bpp;

	GLuint   width;
	GLuint   height;

	GLuint   texID;     // For texture objects;

public:
	bool LoadTGA(char * filename, bool wrap);
	Texture();
	virtual ~Texture();

};
