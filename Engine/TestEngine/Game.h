#pragma once

#include "GameBase.h"

class Game : public GameBase
{
protected:
	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate() override;

public:
	Game();
	~Game();
};

