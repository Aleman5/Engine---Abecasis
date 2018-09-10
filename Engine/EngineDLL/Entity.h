#pragma once

#include "Renderer.h"

class ENGINEDLL_API Entity
{
protected:
	Renderer* renderer;
	Material* material;
	unsigned int bufferId;
	unsigned int programId;
	bool shouldDispose;

public:
	virtual void Draw() = 0;
	virtual void ShouldDispose() = 0;

	Entity(Renderer* renderer, Material* material);
	~Entity();
};

