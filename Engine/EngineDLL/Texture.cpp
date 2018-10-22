#include "Texture.h"

Texture::Texture(Renderer* renderer, Material* material, const char* imagePath) : Shape(renderer, material)
{
	textureId = TextureImporter::loadBMP_custom(imagePath);

	count = 4;
	variables = 3;

	verticesData = new float[count * 3]{
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
	};

	verticesTextureData = new float[count * 2]{
		0.000059f, 1.0f - 0.000004f,
		0.000103f, 1.0f - 0.336048f,
		1.000023f, 1.0f - 0.000013f,
		0.667979f, 1.0f - 0.335851f,
	};

	drawMode = GL_TRIANGLE_STRIP;
	
	bufferId = SetVertices(verticesData, count);
	textureId = SetVertices(verticesTextureData, count);
}

/*Texture::Texture(unsigned int id, unsigned int width, unsigned int height) :
	textureId(id), 
	width(width), 
	height(height)
{
	
}*/
Texture::~Texture()
{
}

void Texture::Draw()
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
	renderer->BindBuffer(textureId, 1);
	renderer->DrawBuffer(0, count, drawMode);
	renderer->DisableAttributes(0);
	renderer->DisableAttributes(1);
}

