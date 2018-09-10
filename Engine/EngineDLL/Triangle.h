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

	void SetVertices(unsigned int bufferId, int count);
	void GenBuffer();

	Triangle(Renderer* renderer);
	~Triangle();
};

