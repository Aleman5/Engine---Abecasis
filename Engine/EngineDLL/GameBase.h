#pragma once

#include "Exports.h"
#include "Renderer.h"

class ENGINEDLL_API GameBase
{
	Renderer* renderer;

protected:
	virtual bool OnStart() = 0;
	virtual bool OnStop() = 0;
	virtual bool OnUpdate() = 0;

public:
	bool Start();
	bool Stop();
	void Loop();

	GameBase();
	~GameBase();
};

