#pragma once

#include "Shape.h"
#include "TextureImporter.h"

class ENGINEDLL_API Sprite : public Shape
{
	Header header;
	unsigned int textureId;

	float* verticesTextureData;

public:
	void Draw() override;

	Sprite(Renderer* renderer, Material* material, const char* imagePath);
	~Sprite();
};