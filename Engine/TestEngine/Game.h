#pragma once

#include "GameBase.h"
#include "Triangle.h"
#include "Rectangle.h"

class Game : public GameBase
{
	Material* material;
	Triangle* t;
	Rectangle* r;

protected:
	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate() override;

public:
	Game();
	~Game();
};

