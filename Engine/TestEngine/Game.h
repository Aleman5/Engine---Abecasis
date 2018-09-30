#pragma once

#include "GameBase.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "ColorShape.h"

class Game : public GameBase
{
	Material* material;
	Triangle* t;
	Rectangle* r;

	float speed;
	float translating;
	float rotating;
	float scalling;

protected:
	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate() override;
	bool OnDraw() override;

public:
	Game();
	~Game();
};

