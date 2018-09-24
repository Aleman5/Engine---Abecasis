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

	glm::vec3 vectorPosition;
	glm::vec3 vectorRotation;
	glm::vec3 vectorScale;

	glm::mat4 model;

	glm::mat4 translationMatrix;
	glm::mat4 rotateX;
	glm::mat4 rotateY;
	glm::mat4 rotateZ;
	glm::mat4 scallingMatrix;

public:
	virtual void Draw() = 0;
	virtual void ShouldDispose() = 0;

	void UpdateModel();
	void Translate(glm::vec3 vector3);
	void Translate(float newX, float newY, float newZ);
	void Scale(glm::vec3 vector3);
	void Scale(float newX, float newY, float newZ);
	void RotateX(float angle);
	void RotateY(float angle);
	void RotateZ(float angle);
	virtual void SetVertices(float* vertices, int count) = 0;

	Entity(Renderer* renderer, Material* material);
	~Entity();
};

