#pragma once

#include "GameBase.h"

class Game : public GameBase
{
	int frame;
protected:
	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate() override;

public:
	Game();
	~Game();
};

