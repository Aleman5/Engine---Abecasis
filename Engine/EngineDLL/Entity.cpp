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

}
Entity::~Entity()
{
}
