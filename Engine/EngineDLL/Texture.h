#pragma once

class Texture
{
	unsigned int textureId;
	unsigned int width;
	unsigned int height;

public:
	

	Texture(unsigned int id, unsigned int width, unsigned int height);
	~Texture();
};

