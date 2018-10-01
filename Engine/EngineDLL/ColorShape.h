#pragma once

#include "Entity.h"

class ENGINEDLL_API ColorShape : public Entity
{
	float* verticesColorData;	// Data of the Vertices
	int count;					// Total vertices
	int variables;				// Total data for each vertice

public:
	void Draw() override;
	void ShouldDispose() override;

	void SetVertices(
		float* vertices,	// Data of the vertices
		int count			// Total Vertices
	) override;
	unsigned int GetBufferId() { return bufferId; }

	ColorShape(Renderer* renderer, Material* material);
	~ColorShape();
};

