#include "Sprite.h"

Sprite::Sprite(Renderer* renderer, Material* material, const char* imagePath, const unsigned int sColumns, const unsigned int sRows)
	: Shape(renderer, material), columns(sColumns), rows(sRows)
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
		0.0f, 1.0f - 1.0f,
		1.0f, 1.0f - 1.0f,
		0.0f, 1.0f - 0.0f,
		1.0f, 1.0f - 0.0f,
	};

	drawMode = GL_TRIANGLE_STRIP;

	bufferId = SetVertices(verticesData, count);
	textureId = SetTextureUV(verticesTextureData, count, 2);
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

unsigned int Sprite::SetTextureUV(float* vertices, int count, int variables)
{
	verticesData = vertices;

	unsigned int id = renderer->GenBuffer(verticesData, sizeof(float) * count * variables);
	shouldDispose = true;

	return id;
}