#pragma once

#include "Renderer.h"

class ENGINEDLL_API Entity
{
protected:
	Renderer* renderer;
	Material* material;
	unsigned int bufferId;
	unsigned int programId;
	bool shouldDispose;

	glm::vec4 originalVector;
	glm::mat4 translationMatrix;
	glm::mat4 scallingMatrix;
	glm::mat4 rotationMatrix;

public:
	virtual void Draw() = 0;
	virtual void ShouldDispose() = 0;

	virtual void World(glm::vec3 vector3) = 0;
	virtual void Translate(glm::vec3 vector3) = 0;
	virtual void Translate(float newX, float newY, float newZ) = 0;
	virtual void Scale(glm::vec3 vector3) = 0;
	virtual void Scale(float newX, float newY, float newZ) = 0;
	virtual void Rotate(float angle) = 0;

	virtual void SetVertices(float* vertices, int count) = 0;

	Entity(Renderer* renderer, Material* material);
	~Entity();
};

