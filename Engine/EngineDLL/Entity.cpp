#include "Entity.h"

Entity::Entity(Renderer* renderer, Material* material)
{
	this->renderer = renderer;
	this->material = material;

	vectorPosition = vectorRotation = vectorScale = glm::vec3(0.0f);

	model = glm::mat4(1.0f);
	translationMatrix = glm::mat4(1.0f);
	rotateX = glm::mat4(1.0f);
	rotateY = glm::mat4(1.0f);
	rotateZ = glm::mat4(1.0f);
	scallingMatrix = glm::mat4(1.0f);

	UpdateModel();
}
Entity::~Entity()
{
}

void Entity::UpdateModel()
{
	model = translationMatrix * rotateX * rotateY * rotateZ * scallingMatrix;
}

void Entity::Translate(glm::vec3 vector3)
{
	// Changes the actual position multiplying Matrix4x4 * position
	translationMatrix = glm::translate(glm::mat4(), vector3);

	UpdateModel();
}

void Entity::Translate(float newX, float newY, float newZ)
{
	// Changes the actual position multiplying Matrix4x4 * position
	glm::vec3 vector3(newX, newY, newZ);

	translationMatrix = glm::translate(glm::mat4(), vector3);

	UpdateModel();
}

void Entity::Scale(glm::vec3 vector3)
{
	scallingMatrix = glm::scale(vector3);

	UpdateModel();
}

void Entity::Scale(float newX, float newY, float newZ)
{
	glm::vec3 vector3(newX, newY, newZ);

	scallingMatrix = glm::scale(vector3);

	UpdateModel();
}

void Entity::RotateX(float angle)
{
	glm::vec3 vecAxis;

	vecAxis[1] = vecAxis[2] = 0.0f;
	vecAxis[0] = 1.0f;

	rotateX = glm::rotate(glm::mat4(), glm::radians(angle), vecAxis);

	UpdateModel();
}

void Entity::RotateY(float angle)
{
	glm::vec3 vecAxis;

	vecAxis[0] = vecAxis[2] = 0.0f;
	vecAxis[1] = 1.0f;

	rotateY = glm::rotate(glm::mat4(), glm::radians(angle), vecAxis);

	UpdateModel();
}

void Entity::RotateZ(float angle)
{
	glm::vec3 vecAxis;

	vecAxis[0] = vecAxis[1] = 0.0f;
	vecAxis[2] = 1.0f;

	rotateZ = glm::rotate(glm::mat4(), glm::radians(angle), vecAxis);

	UpdateModel();
}