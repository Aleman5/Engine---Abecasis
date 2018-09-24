#include "Renderer.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

bool Renderer::Start(Window* win)
{
	window = win;

	glfwMakeContextCurrent((GLFWwindow*)window->GetContext());

	
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		glfwTerminate();
		return false;
	}

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	projectionMatrix = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.0f, 100.0f);

	viewMatrix = glm::lookAt(
		glm::vec3(0, 0, 3), // Camera is at (0, 0, 3), is World Space
		glm::vec3(0, 0, 0), // Looks at the origin
		glm::vec3(0, 1, 0)  // Head is up to (0, -1, 0)
	);

	return true;
}

bool Renderer::Stop()
{
	return true;
}

void Renderer::SetClearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}

void Renderer::SwapBuffers()
{
	glfwSwapBuffers((GLFWwindow*)window->GetContext());
}

void Renderer::ClearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::DestroyBuffer(unsigned int bufferId)
{
	glDeleteBuffers(1, &bufferId);
}

unsigned int Renderer::GenBuffer(float* buffer, int size)
{
	// Identificar el vertex buffer
	unsigned int vertexbuffer;
	// Generar un buffer, poner el resultado en el vertexbuffer que acabamos de crear
	glGenBuffers(1, &vertexbuffer);
	// Los siguientes comandos le darán características especiales al 'vertexbuffer' 
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Darle nuestros vértices a  OpenGL.
	glBufferData(GL_ARRAY_BUFFER, size, buffer, GL_STATIC_DRAW);

	return vertexbuffer;
}

/*void Renderer::DrawBuffer(unsigned int vertexbuffer, int size)
{
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // atributo 0. No hay razón particular para el 0, pero debe corresponder en el shader.
		3,                  // tamaño
		GL_FLOAT,           // tipo
		GL_FALSE,           // normalizado?
		0,                    // Paso
		(void*)0            // desfase del buffer
	);
	// Dibujar el triángulo !
	glDrawArrays(GL_TRIANGLES, 0, size); // Empezar desde el vértice 0S; 3 vértices en total -> 1 triángulo
	glDisableVertexAttribArray(0);
}*/

void Renderer::EnableAttributes(unsigned int attributebId)
{
	glEnableVertexAttribArray(attributebId);
}

void Renderer::BindBuffer(unsigned int bufferId, unsigned int attributebId)
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferId);
	glVertexAttribPointer(
		attributebId,                  // atributo 0. No hay razón particular para el 0, pero debe corresponder en el shader.
		3,                  // tamaño
		GL_FLOAT,           // tipo
		GL_FALSE,           // normalizado?
		0,                    // Paso
		(void*)0            // desfase del buffer
	);
}

void Renderer::DrawBuffer(unsigned int attributeId, int size)
{
	glDrawArrays(GL_TRIANGLES, 0, size); // Empezar desde el vértice 0S; 3 vértices en total -> 1 triángulo
}

void Renderer::DisableAttributes(unsigned int attributeId)
{
	glDisableVertexAttribArray(attributeId);
}

void Renderer::loadIdentityMatrix()
{
	modelMatrix = glm::mat4(1.0f);

	SetMVP();
}

void Renderer::SetModelMatrix(glm::mat4 model)
{
	modelMatrix = model;

	SetMVP();
}


void Renderer::MultiplyModelMatrix(glm::mat4 model)
{
	modelMatrix *= model;

	SetMVP();
}

void Renderer::SetMVP()
{
	MVP = projectionMatrix * viewMatrix * modelMatrix;
}

glm::mat4& Renderer::GetMVP()
{
	return MVP;
}