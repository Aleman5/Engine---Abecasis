#pragma once

#include "Shape.h"

class ENGINEDLL_API Rectangle : public Shape
{
	float* verticesColorData;

public:

	void Draw() override;

	Rectangle(Renderer* renderer, Material* material);
	~Rectangle();
};