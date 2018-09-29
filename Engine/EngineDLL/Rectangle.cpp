#include "Rectangle.h"

Rectangle::Rectangle(Renderer* renderer, Material* material) : Entity(renderer, material)
{
	verticesData = new float[12]{
		-1.0f, -1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
	};

	count = 4;

	SetVertices(verticesData, count);
}

Rectangle::~Rectangle()
{
}

void Rectangle::Draw()
{
	renderer->loadIdentityMatrix();
	renderer->SetModelMatrix(model);

	if (material != NULL)
	{
		material->Bind();
		material->SetMatrixProperty("MVP", renderer->GetMVP());
	}
	renderer->EnableAttributes(0);
	renderer->BindBuffer(bufferId, 0);
	renderer->DrawBuffer(0, count);
	renderer->DisableAttributes(0);
}

void Rectangle::ShouldDispose()
{
	if (shouldDispose)
	{
		renderer->DestroyBuffer(bufferId);
		delete[] verticesData;
		shouldDispose = false;
	}
}

void Rectangle::SetVertices(float* vertices, int count)
{
	verticesData = vertices;
	this->count = count;
	variables = 3;

	bufferId = renderer->GenBuffer(verticesData, sizeof(float) * count * variables);
	shouldDispose = true;
}