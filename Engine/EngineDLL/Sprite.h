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

	unsigned int SetTextureUV(
		float* vertices,	// Data of the vertices
		int count,			// Total Vertices
		int variables		// Total variables
	);

	Sprite(Renderer* renderer, Material* material, const char* imagePath);
	~Sprite();
};