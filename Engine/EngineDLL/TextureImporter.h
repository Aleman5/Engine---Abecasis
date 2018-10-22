#pragma once

#include <fstream>
#include "Renderer.h"
#include "Texture.h"

class TextureImporter
{
public:
	static Texture* loadBMP_custom(const char* imagePath);
	//static bool CheckBMP(FILE*& file, unsigned char& header);

	TextureImporter();
	~TextureImporter();
};

