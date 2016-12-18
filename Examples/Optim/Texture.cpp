// Texture.cpp: implementation of the Texture class.
//
//////////////////////////////////////////////////////////////////////
#include "Texture.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Texture::Texture()
{
    imageData	= NULL;
    bpp			= 0;
    width		= 0;
    height		= 0;
    texID		=-1;
}

Texture::~Texture()
{

}

bool Texture::LoadTGA(char * filename, bool wrap)
{

	GLubyte    targaMagic[12] = { 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	GLubyte    fileMagic[12];

	// Header data.
	GLubyte    header[6];
	GLuint     bytesPerPixel;

	GLuint     imageSize;
	GLuint     tmp;
	GLuint     i;

    FILE *file = fopen(filename, "rb");

    // Start reading in the header, make sure we
    // have the right Targa data type.  

    if(file == NULL                                                           ||
       fread(fileMagic, 1, sizeof(fileMagic), file)      != sizeof(fileMagic) ||
       memcmp(targaMagic, fileMagic, sizeof(targaMagic)) != 0                 ||
       fread(header, 1, sizeof(header), file)            != sizeof(header))
    {
         fclose(file);
         return false;
    }

    // Determine width and height from header data.

    width  = header[1] * 256 + header[0];
    height = header[3] * 256 + header[2];

    // Determine color bit depth of the image (24 or 32).

    if(width <= 0 || height <= 0 || (header[4] != 24 && header[4] != 32))
    {
         fclose(file);
         return false;
    }

    bpp  = header[4];
    bytesPerPixel = bpp / 8;
    imageSize     = width * height * bytesPerPixel;

    imageData = (GLubyte *)malloc(imageSize);

    if(imageData == NULL ||
       (int)fread(imageData, 1, imageSize, file) != imageSize)
    {
          if(imageData != NULL)
               free(imageData);

          fclose(file);
		  return false;
    } 

    for(i = 0; i < imageSize; i += bytesPerPixel)
    {
          tmp = imageData[i];
          imageData[i] = imageData[i + 2];
          imageData[i + 2] = tmp;
    }

    fclose (file);

	glGenTextures( 1, &texID );

	glBindTexture( GL_TEXTURE_2D, texID );

	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
				   GL_LINEAR_MIPMAP_NEAREST );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
				   wrap ? GL_REPEAT : GL_CLAMP );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
				   wrap ? GL_REPEAT : GL_CLAMP );

	gluBuild2DMipmaps( GL_TEXTURE_2D, 4, width, height,
					   (header[4]==24)?GL_RGB : GL_RGBA,
					   GL_UNSIGNED_BYTE, imageData );

	free( imageData );

	return true;
}
