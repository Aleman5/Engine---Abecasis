#pragma once

#include<fstream>

class TextureImporter
{
public:
	static unsigned int loadBMP_custom(const char* imagePath);

	TextureImporter();
	~TextureImporter();
};

