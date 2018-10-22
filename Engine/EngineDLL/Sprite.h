#pragma once

#include "Shape.h"
#include "Texture.h"
#include "TextureImporter.h"

class ENGINEDLL_API Sprite : public Shape
{
	Texture* texture;

	float* verticesTextureData;

public:
	void Draw() override;

	Sprite(Renderer* renderer, Material* material, const char* imagePath);
	//Texture(unsigned int id, unsigned int width, unsigned int height);
	~Sprite();
};