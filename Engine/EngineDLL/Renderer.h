#pragma once

#include "Exports.h"
#include "Window.h"

class ENGINEDLL_API Renderer
{
	Window* window;

public:
	bool Start(Window* window);
	bool Stop();

	void SetClearColor(float r, float g, float b, float a);
	void ClearScreen();
	void SwapBuffers();

	Renderer();
	~Renderer();
};

