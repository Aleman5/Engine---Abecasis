#include "Circle.h"

Circle::Circle(Renderer* renderer, Material* material, float radius, int totalTriangles) : Shape(renderer, material)
{
	drawMode = GL_TRIANGLE_FAN;

	this->radius = radius;
	totTriangles = totalTriangles;

	variables = 3;
	
	count = totTriangles * 3;
	degrees = 360.0f / totTriangles;
	angle = 0.0f;

	verticesData =		new float[count] {};
	verticesColorData = new float[count] {};
	glm::vec3 vec;

	for (int i = 0; i < count; i += 3)
	{
		vec = glm::vec3(cos(angle), sin(angle), 0) * radius;
		verticesData[i]	    = vec.x;
		verticesData[i + 1] = vec.y;
		verticesData[i + 2] = vec.z;
		angle += degrees * PI / 180.0f;

		verticesColorData[i]     = 1 / (rand() % 100 + 1);
		verticesColorData[i + 1] = 1 / (rand() % 100 + 1);
		verticesColorData[i + 2] = 1 / (rand() % 100 + 1);
	}

	bufferId = SetVertices(verticesData, count);
	colorBufferId = SetVertices(verticesColorData, count);
}
Circle::~Circle()
{
}

void Circle::Draw()
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
	renderer->BindBuffer(colorBufferId, 1);
	renderer->DrawBuffer(0, count, drawMode);
	renderer->DisableAttributes(0);
	renderer->DisableAttributes(1);
}