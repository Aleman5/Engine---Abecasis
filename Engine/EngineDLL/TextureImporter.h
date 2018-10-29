#pragma once

#include <fstream>
#include "Renderer.h"
#include "Texture.h"

#define COULDNT_OPEN -2
#define INCORRECT_FORMAT -1
#define BMP_FORMAT 0
#define PNG_FORMAT 1

struct Header {
	unsigned int dataPos;
	unsigned int width, height;
	unsigned int imageSize;
	unsigned char * data;
};
static class TextureImporter
{
public:
	static Header loadBMP_custom(const char* imagePath);
	static int CheckFormat(FILE*& file, unsigned char header[]);

	TextureImporter();
	~TextureImporter();
};

