#include "ColorShape.h"

ColorShape::ColorShape(Renderer* renderer, Material* material) : Entity(renderer, material)
{
	verticesColorData = new float[12]{
		1.0f, 0.5f, 1.0f,
		0.0f, 1.0f, 0.43f,
		0.7f, 0.5f, 0.8f,
		0.0f, 0.5f, 0.5f,
	};

	count = 3;

	SetVertices(verticesColorData, count);
}
ColorShape::~ColorShape()
{
}

void ColorShape::Draw()
{
	renderer->loadIdentityMatrix();
	renderer->SetModelMatrix(model);

	if (material != NULL)
	{
		material->Bind();
		material->SetMatrixProperty("MVP", renderer->GetMVP());
	}
	renderer->EnableAttributes(1);
	renderer->BindBuffer(bufferId, 1);
	renderer->DrawBuffer(1, count);
	renderer->DisableAttributes(1);
}

void ColorShape::ShouldDispose()
{
	if (shouldDispose)
	{
		renderer->DestroyBuffer(bufferId);
		delete[] verticesColorData;
		shouldDispose = false;
	}
}

void ColorShape::SetVertices(float* vertices, int count)
{
	verticesColorData = vertices;
	this->count = count;
	variables = 3;

	bufferId = renderer->GenBuffer(verticesColorData, sizeof(float) * count * variables);
	shouldDispose = true;
}