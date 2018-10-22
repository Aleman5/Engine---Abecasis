#include "Sprite.h"

Sprite::Sprite(Renderer* renderer, Material* material, const char* imagePath) : Shape(renderer, material)
{
	texture = TextureImporter::loadBMP_custom(imagePath);

	count = 4;
	variables = 3;

	verticesData = new float[count * 3]{
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
	};

	verticesTextureData = new float[count * 2]{
		0.0f, 1.0f - 0.0f,
		1.0f, 1.0f - 0.0f,
		0.0f, 1.0f - 1.0f,
		1.0f, 1.0f - 1.0f,
	};

	drawMode = GL_TRIANGLE_STRIP;

	bufferId = SetVertices(verticesData, count);
}

/*Texture::Texture(unsigned int id, unsigned int width, unsigned int height) :
textureId(id),
width(width),
height(height)
{

}*/
Sprite::~Sprite()
{
}

void Sprite::Draw()
{
	renderer->loadIdentityMatrix();
	renderer->SetModelMatrix(model);

	if (material != NULL)
	{
		material->Bind();
		material->SetMatrixProperty("MVP", renderer->GetMVP());
	}

	renderer->EnableAttributes(0);
	renderer->EnableAttributes(1);
	renderer->BindBuffer(bufferId, 0);
	renderer->BindTextureBuffer(texture->GetTextureId(), 1);
	renderer->DrawBuffer(0, count, drawMode);
	renderer->DisableAttributes(0);
	renderer->DisableAttributes(1);
}