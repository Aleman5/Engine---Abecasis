#pragma once

#include "Exports.h"
#include "Renderer.h"
#include "Window.h"
#include "Typedef.h"

class ENGINEDLL_API GameBase
{
	Window * window;
	Renderer* renderer;

protected:
	virtual bool OnStart() = 0;
	virtual bool OnStop() = 0;
	virtual bool OnUpdate() = 0;

public:
	bool Start(int width, int height, const char* window);
	bool Stop();
	void Loop();
	Renderer* GetRenderer();

	GameBase();
	~GameBase();
};

