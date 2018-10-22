#pragma once

#include <fstream>
#include "Renderer.h"

class TextureImporter
{
public:
	static unsigned int loadBMP_custom(const char* imagePath);

	TextureImporter();
	~TextureImporter();
};

