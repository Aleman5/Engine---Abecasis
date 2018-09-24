#pragma once

#include "Entity.h"

class ENGINEDLL_API Rectangle : public Entity
{
	float* verticesData;
	int count; // total vertices
	int variables; // total data for each vertice
public:

	void Draw() override;
	void ShouldDispose() override;

	void SetVertices(float* vertices, int count) override;
	
	Rectangle(Renderer* renderer, Material* material);
	~Rectangle();
};

