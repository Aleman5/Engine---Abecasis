#pragma once

#include "Shape.h"

class ENGINEDLL_API Circle : public Shape
{
	float* verticesColorData;

public:
	void Draw() override;

	Circle(Renderer* renderer, Material* material);
	~Circle();
};

