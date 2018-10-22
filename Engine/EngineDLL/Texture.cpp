#include "Texture.h"

Texture::Texture(unsigned int textureId, unsigned int width, unsigned int height)
	: width(width),
	  height(height),
	  textureId(textureId)
{
	/*verticesTextureData = new float[count * 2]{
		0.0f, 1.0f - 0.0f,
		1.0f, 1.0f - 0.0f,
		0.0f, 1.0f - 1.0f,
		1.0f, 1.0f - 1.0f,
	};*/
}

Texture::~Texture()
{
}

unsigned int Texture::GetTextureId()
{
	return textureId;
}