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

	void UpdateModel() override;
	void Translate(glm::vec3 vector3) override;
	void Translate(float newX, float newY, float newZ) override;
	void Scale(glm::vec3 vector3) override;
	void Scale(float newX, float newY, float newZ) override;
	void RotateX(float angle) override;
	void RotateY(float angle) override;
	void RotateZ(float angle) override;

	void SetVertices(float* vertices, int count) override;

	Triangle(Renderer* renderer, Material* material);
	~Triangle();
};

