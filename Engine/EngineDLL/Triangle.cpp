#include "Triangle.h"

Triangle::Triangle(Renderer* renderer) : Entity(renderer)
{
	verticesData = new float[9]{
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
	};

	vertexbuffer = this->renderer->GenBuffer(verticesData, sizeof(float) * count * variables);
}
Triangle::~Triangle()
{
}

void Triangle::Draw()
{
	renderer->DrawBuffer(vertexbuffer, count);
}