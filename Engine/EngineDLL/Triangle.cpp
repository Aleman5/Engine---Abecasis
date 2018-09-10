#include "Triangle.h"

Triangle::Triangle(Renderer* renderer) : Entity(renderer)
{
	verticesData = new float[9]{
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
	};

	count = 3;
	variables = 3;

	GenBuffer();
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
		renderer->DestroyBuffer(&bufferId);
		delete[] verticesData;
		shouldDispose = false;
	}
}

void Triangle::SetVertices(unsigned int bufferId, int count)
{
	this->bufferId = bufferId;

	this->count = count;
}

void Triangle::GenBuffer()
{
	bufferId = renderer->GenBuffer(verticesData, sizeof(float) * count * variables);
	shouldDispose = true;
}