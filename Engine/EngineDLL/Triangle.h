#pragma once

#include "Shape.h"

class ENGINEDLL_API Triangle : public Shape
{
	float* verticesColorData;
	unsigned int colorBufferId;

public:
	void Draw() override;

	Triangle(Renderer* renderer, Material* material);
	~Triangle();
};

