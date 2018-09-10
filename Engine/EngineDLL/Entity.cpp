#include "Entity.h"

Entity::Entity(Renderer* renderer, Material* material)
{
	this->renderer = renderer;
	this->material = material;
}
Entity::~Entity()
{
}
