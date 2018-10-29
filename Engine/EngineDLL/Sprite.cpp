#include "Sprite.h"

Sprite::Sprite(Renderer* renderer, Material* material, const char* imagePath) : Shape(renderer, material)
{
	header = TextureImporter::loadBMP_custom(imagePath);

	textureId = renderer->GenTexture(header.width, header.height, header.data);

	count = 4;
	variables = 3;

	verticesData = new float[count * 3]{
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
	};

	verticesTextureData = new float[count * 2]{
		1.0f, 1.0f - 1.0f,
		0.0f, 1.0f - 0.0f,
		1.0f, 1.0f - 1.0f,
		1.0f, 1.0f - 0.0f,
	};

	drawMode = GL_TRIANGLE_STRIP;

	bufferId = SetVertices(verticesData, count);
}

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
	renderer->BindTextureBuffer(textureId, 1);
	renderer->DrawBuffer(0, count, drawMode);
	renderer->DisableAttributes(0);
	renderer->DisableAttributes(1);
}