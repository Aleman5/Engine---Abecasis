#include "Triangle.h"

Triangle::Triangle(Renderer* renderer, Material* material) : Entity(renderer, material)
{
	verticesData = new float[9]{
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
	};

	count = 3;
	
	SetVertices(verticesData, count);

	color = new ColorShape(renderer, material);
}
Triangle::~Triangle()
{
}

void Triangle::Draw()
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
	renderer->BindBuffer(color->GetBufferId(), 1);
	renderer->DrawBuffer(0, count);
	renderer->DisableAttributes(0);
	renderer->DisableAttributes(1);
}

void Triangle::ShouldDispose()
{
	if (shouldDispose)
	{
		renderer->DestroyBuffer(bufferId);
		delete[] verticesData;
		shouldDispose = false;
	}
}

void Triangle::SetVertices(float* vertices, int count)
{
	verticesData = vertices;
	this->count = count;
	variables = 3;

	bufferId = renderer->GenBuffer(verticesData, sizeof(float) * count * variables);
	shouldDispose = true;
}