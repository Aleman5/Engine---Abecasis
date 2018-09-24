#pragma once

#include "Entity.h"

class ENGINEDLL_API Triangle : public Entity
{
	float* verticesData;
	int count; // total vertices
	int variables; // total data for each vertice
public:

	void Draw() override;
	void ShouldDispose() override;

	void World(glm::vec3 vector3) override;
	void Translate(glm::vec3 vector3) override;
	void Translate(float newX, float newY, float newZ) override;
	void Scale(glm::vec3 vector3) override;
	void Scale(float newX, float newY, float newZ) override;
	void Rotate(float angle) override;

	glm::mat4 GetModelMatrix();

	void SetVertices(float* vertices, int count) override;

	Triangle(Renderer* renderer, Material* material);
	~Triangle();
};

