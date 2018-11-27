#pragma once

#include "Shape.h"
#include "Animation.h"
#include "TextureImporter.h"

class ENGINEDLL_API Sprite : public Shape
{
	Header header;
	Animation* anim;
	unsigned int textureId;
	unsigned int uvBufferId;
	unsigned int frameId;
	unsigned int actualFrame;
	unsigned int columns;
	unsigned int rows;
	unsigned int widthOfFrame;
	unsigned int heightOfFrame;

	float* verticesTextureData;
	float* uvBufferData;

	bool isAnimated;

public:
	void Draw() override;
	void Update(float deltaTime);

	unsigned int SetTextureUV(
		float* vertices,	// Data of the vertices
		int count,			// Total Vertices
		int variables		// Total variables
	);

	void SetNextFrame(unsigned int newFrame);

	float* SetUV(unsigned int x, unsigned int y);

	Sprite(Renderer* renderer,			// Renderer reference
		   Material* material,			// Material reference
		   Layers layer,				// Layer of the Entity
		   const char* imagePath,		// Path of the image
		   bool isAnimated,				// IsAnimated? Yes/No
		   const unsigned int sColumns, // Columns of the spritesheet
		   const unsigned int sRows,	// Rows of the spritesheet
		   const float colliderWidth,	// Width of the collider
		   const float colliderHeight);	// Height of the collider
	~Sprite();
};