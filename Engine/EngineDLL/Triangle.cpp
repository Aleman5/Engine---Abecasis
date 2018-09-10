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
}
Triangle::~Triangle()
{
}

void Triangle::Draw()
{
	renderer->DrawBuffer(bufferId, count);
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