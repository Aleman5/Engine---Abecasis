#pragma once

#include "Shape.h"
#include "Animation.h"
#include "TextureImporter.h"

class ENGINEDLL_API Sprite : public Shape
{
	Header header;				// Information of the Texture
	Animation* anim;			// Animation reference
	unsigned int textureId;		// Id of the Texture
	unsigned int uvBufferId;	// Id of the UvBuffer
	unsigned int actualFrame;	// Actual Frame
	unsigned int columns;		// Columns of the Spritesheet
	unsigned int rows;			// Rows of the Spritesheet
	unsigned int widthOfFrame;	// Widht of each frame
	unsigned int heightOfFrame;	// Height of each frame

	float* verticesTextureData;	// Data of each vertice of the Texture (vec2)
	float* uvBufferData;		// Data of each UV of the Buffer (vec2)

	bool isAnimated;			// Is animated? Yes/No

public:
	void Draw() override;
	void Update(float deltaTime);

	unsigned int SetTextureUV(
		float* vertices,	// Data of the vertices
		int count,			// Total Vertices
		int variables		// Total variables
	);

	void SetNextFrame(
		unsigned int newFrame // The next frame to render
	);

	float* SetUV(
		unsigned int x, // Equivalent to U
		unsigned int y  // Equivalent to V
	);

	Sprite(Renderer* renderer,			// Renderer reference
		   Material* material,			// Material reference
		   Layers layer,				// Layer of the Entity
		   const char* imagePath,		// Path of the image
		   bool isAnimated,				// Is animated? Yes/No
		   const unsigned int sColumns, // Columns of the spritesheet
		   const unsigned int sRows,	// Rows of the spritesheet
		   const float colliderWidth,	// Width of the collider
		   const float colliderHeight);	// Height of the collider
	~Sprite();
};