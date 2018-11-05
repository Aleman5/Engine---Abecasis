#pragma once

#include "Shape.h"
#define PI 3.14159265359f

class ENGINEDLL_API Circle : public Shape
{
	float* verticesColorData;
	float radius;
	float degrees;
	float angle;
	int totTriangles;

public:
	void Draw() override;

	Circle(Renderer* renderer, Material* material, Layers tag, float radius, int totalTriangles);
	~Circle();
};

