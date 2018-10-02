#include "Shape.h"

Shape::Shape(Renderer* renderer, Material* material) : Entity(renderer, material)
{
	srand(time(0));
}
Shape::~Shape()
{
}

void Shape::ShouldDispose()
{
	if (shouldDispose)
	{
		renderer->DestroyBuffer(bufferId);
		delete[] verticesData;
		shouldDispose = false;
	}
}

unsigned int Shape::SetVertices(float* vertices, int count)
{
	verticesData = vertices;
	this->count = count;

	unsigned int id = renderer->GenBuffer(verticesData, sizeof(float) * count * variables);
	shouldDispose = true;

	return id;
}