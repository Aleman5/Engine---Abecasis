#pragma once

#include "Shape.h"
#include "TextureImporter.h"

class ENGINEDLL_API Texture : public Shape
{
	/*unsigned int textureId;
	unsigned int width;
	unsigned int height;*/

	unsigned int textureId;
	float* verticesTextureData;

public:
	void Draw() override;

	Texture(Renderer* renderer, Material* material, const char* imagePath);
	//Texture(unsigned int id, unsigned int width, unsigned int height);
	~Texture();
};

