#pragma once

class Texture
{
	unsigned int textureId;
	unsigned int width;
	unsigned int height;

public:
	unsigned int GetTextureId();

	Texture(unsigned int textureId, unsigned int width, unsigned int height);
	~Texture();
};