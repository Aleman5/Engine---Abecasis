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

void Triangle::World(glm::vec3 vector3)
{
	originalVector = glm::vec4(vector3.x, vector3.y, vector3.z, 1); // It goes 1 at 'W' because it's a position at the space.
}

void Triangle::Translate(glm::vec3 vector3)
{
	// Changes the actual position multiplying Matrix4x4 * position
	translationMatrix = glm::translate(glm::mat4(), vector3);
}

void Triangle::Translate(float newX, float newY, float newZ)
{
	// Changes the actual position multiplying Matrix4x4 * position
	glm::vec3 vector3(newX, newY, newZ);

	translationMatrix = glm::translate(glm::mat4(), vector3);
}

void Triangle::Scale(glm::vec3 vector3)
{
	scallingMatrix = glm::scale(vector3);
}

void Triangle::Scale(float newX, float newY, float newZ)
{
	glm::vec3 vector3(newX, newY, newZ);

	scallingMatrix = glm::scale(vector3);
}

void Triangle::Rotate(float angle)
{
	rotationMatrix = glm::rotate(glm::mat4(), glm::radians(angle), glm::vec3(0, 0, 0));
}

glm::mat4 Triangle::GetModelMatrix()
{
	return (translationMatrix * rotationMatrix * scallingMatrix);
}

void Triangle::SetVertices(float* vertices, int count)
{
	verticesData = vertices;
	this->count = count;
	variables = 3;



	bufferId = renderer->GenBuffer(verticesData, sizeof(float) * count * variables);
	shouldDispose = true;
}