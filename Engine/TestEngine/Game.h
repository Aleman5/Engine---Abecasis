#pragma once

#include "GameBase.h"
#include "Triangle.h"

class Game : public GameBase
{
	Triangle* t;

protected:
	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate() override;

public:
	Game();
	~Game();
};

