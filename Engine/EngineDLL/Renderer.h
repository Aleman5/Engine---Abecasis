#pragma once

#include "Exports.h"
#include "Window.h"

#include "GL\glew.h"
#include "glm\glm.hpp"
using namespace glm;

class ENGINEDLL_API Renderer
{
	Window* window;

	GLuint VertexArrayID;

public:
	bool Start(Window* window);
	bool Stop();

	void SetClearColor(float r, float g, float b, float a);
	void ClearScreen();
	void SwapBuffers();

	Renderer();
	~Renderer();
};

