#pragma once

#include "Exports.h"
#include "Window.h"
#include "Material.h"
#include "GL\glew.h"
#include "GLFW\glfw3.h"

#define GLM_ENABLE_EXPERIMENTAL

#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\glm.hpp>

class ENGINEDLL_API Renderer
{
	Window* window;

	GLuint VertexArrayID;

	glm::mat4 modelMatrix;
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	glm::mat4 MVP;

public:
	bool Start(Window* window);
	bool Stop();

	void SetClearColor(float r, float g, float b, float a);
	void ClearScreen();
	void SwapBuffers();
	void DestroyBuffer(unsigned int bufferId);

	unsigned int GenBuffer(float* buffer, int size);
	//void DrawBuffer(unsigned int vertexbuffer, int size);

	void EnableAttributes(unsigned int attributeId);
	void BindBuffer(unsigned int bufferId, unsigned int attributeId);
	void DrawBuffer(unsigned int attributeId, int size);
	void DisableAttributes(unsigned int attributeId);

	void loadIdentityMatrix();
	void SetModelMatrix(glm::mat4 model);
	void MultiplyModelMatrix(glm::mat4 model);
	void SetMVP();
	glm::mat4& GetMVP();

	Renderer();
	~Renderer();
};

