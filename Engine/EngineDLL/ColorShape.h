#pragma once

#include "Entity.h"

class ENGINEDLL_API ColorShape : public Entity
{
	float* verticesColorData;
	int count;
	int variables;

public:
	void Draw() override;
	void ShouldDispose() override;

	void SetVertices(float* vertices, int count) override;

	ColorShape(Renderer* renderer, Material* material);
	~ColorShape();
};

