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

void Triangle::UpdateModel()
{
	model = translationMatrix * rotateX * rotateY * rotateZ * scallingMatrix;
}

void Triangle::Translate(glm::vec3 vector3)
{
	// Changes the actual position multiplying Matrix4x4 * position
	translationMatrix = glm::translate(glm::mat4(), vector3);

	UpdateModel();
}

void Triangle::Translate(float newX, float newY, float newZ)
{
	// Changes the actual position multiplying Matrix4x4 * position
	glm::vec3 vector3(newX, newY, newZ);

	translationMatrix = glm::translate(glm::mat4(), vector3);

	UpdateModel();
}

void Triangle::Scale(glm::vec3 vector3)
{
	scallingMatrix = glm::scale(vector3);

	UpdateModel();
}

void Triangle::Scale(float newX, float newY, float newZ)
{
	glm::vec3 vector3(newX, newY, newZ);

	scallingMatrix = glm::scale(vector3);

	UpdateModel();
}

void Triangle::RotateX(float angle)
{
	glm::vec3 vecAxis;

	vecAxis[1] = vecAxis[2] = 0.0f;
	vecAxis[0] = 1.0f;

	rotateX = glm::rotate(glm::mat4(), glm::radians(angle), vecAxis);

	UpdateModel();
}

void Triangle::RotateY(float angle)
{
	glm::vec3 vecAxis;

	vecAxis[0] = vecAxis[2] = 0.0f;
	vecAxis[1] = 1.0f;

	rotateY = glm::rotate(glm::mat4(), glm::radians(angle), vecAxis);

	UpdateModel();
}

void Triangle::RotateZ(float angle)
{
	glm::vec3 vecAxis;

	vecAxis[0] = vecAxis[1] = 0.0f;
	vecAxis[2] = 1.0f;

	rotateZ = glm::rotate(glm::mat4(), glm::radians(angle), vecAxis);

	UpdateModel();
}

void Triangle::SetVertices(float* vertices, int count)
{
	verticesData = vertices;
	this->count = count;
	variables = 3;

	bufferId = renderer->GenBuffer(verticesData, sizeof(float) * count * variables);
	shouldDispose = true;
}