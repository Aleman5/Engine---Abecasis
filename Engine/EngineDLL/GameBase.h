#pragma once

#include "Exports.h"
#include "Renderer.h"
#include "Window.h"
#include "Typedef.h"

#include "GLFW\glfw3.h"

class ENGINEDLL_API GameBase
{
	Window * window;
	Renderer* renderer;
	
	double currentFrame;
	double lastFrame;

protected:
	double time;

	virtual bool OnStart() = 0;
	virtual bool OnStop() = 0;
	virtual bool OnUpdate() = 0;
	virtual bool OnDraw() = 0;

public:
	bool Start(int width, int height, const char* window);
	bool Stop();
	void Loop();
	void Time();
	Renderer* GetRenderer();

	GameBase();
	~GameBase();
};

