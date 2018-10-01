#pragma once

#include "Entity.h"
#include "ColorShape.h"

class ENGINEDLL_API Triangle : public Entity
{
	ColorShape* color;

	float* verticesData;	// Data of the Vertices
	int count;				// Total vertices
	int variables;			// Total data for each vertice
public:

	void Draw() override;
	void ShouldDispose() override;

	void SetVertices(
		float* vertices,	// Data of the vertices
		int count			// Total Vertices
	) override;

	Triangle(Renderer* renderer, Material* material);
	~Triangle();
};

