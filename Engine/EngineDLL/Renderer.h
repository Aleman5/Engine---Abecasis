#pragma once

#include "Exports.h"
#include "Window.h"
#include "Material.h"
#include "GL\glew.h"
#include "GLFW\glfw3.h"

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
	void DestroyBuffer(unsigned int bufferId);

	unsigned int GenBuffer(float* buffer, int size);
	void DrawBuffer(unsigned int vertexbuffer, int size);

	Renderer();
	~Renderer();
};

