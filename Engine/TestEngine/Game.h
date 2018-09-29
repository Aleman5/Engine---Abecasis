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
	ColorShape* c;

protected:
	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate() override;

public:
	Game();
	~Game();
};

