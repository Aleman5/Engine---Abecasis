#pragma once

#include "Shape.h"
#include "TextureImporter.h"

class ENGINEDLL_API Sprite : public Shape
{
	Header header;
	unsigned int textureId;
	unsigned int columns;
	unsigned int rows;

	float* verticesTextureData;

public:
	void Draw() override;

	unsigned int SetTextureUV(
		float* vertices,	// Data of the vertices
		int count,			// Total Vertices
		int variables		// Total variables
	);

	Sprite(Renderer* renderer,			// Renderer reference
		   Material* material,			// Material reference
		   Layers tag,					// Tag of the Entity
		   const char* imagePath,		// Path of the image
		   const unsigned int sColumns, // Columns of the spritesheet
		   const unsigned int sRows,	// Rows of the spritesheet
		   const float colliderWidth,	// Width of the collider
		   const float colliderHeight);	// Height of the collider
	~Sprite();
};