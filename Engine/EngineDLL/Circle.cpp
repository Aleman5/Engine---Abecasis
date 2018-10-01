#include "Circle.h"

Circle::Circle(Renderer* renderer, Material* material) : Shape(renderer, material)
{
	verticesData = new float[3]{
		-1.0f, -1.0f, 0.0f,
	};

	verticesColorData = new float[3]{
		0.583f, 0.771f, 0.014f,
	};

	drawMode = GL_TRIANGLE_FAN;

	count = 4;
	variables = 3;
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