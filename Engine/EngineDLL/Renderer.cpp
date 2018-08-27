#include "Renderer.h"

#include "GLFW/glfw3.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

bool Renderer::Start(Window* window)
{
	this->window = window;

	glfwMakeContextCurrent((GLFWwindow*)this->window);
	
	return true;
}

bool Renderer::Stop()
{
	return true;
}

void Renderer::SetClearColor(float r, float g, float b, float a)
{
	// setea el color del fondo
}

void Renderer::SwapBuffers()
{
	glfwSwapBuffers((GLFWwindow*)window);
}

void Renderer::ClearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT);
}