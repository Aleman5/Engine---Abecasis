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

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		glfwTerminate();
		return false;
	}

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

unsigned int Renderer::GenBuffer(float* buffer, int size)
{
	// Identificar el vertex buffer
	unsigned int vertexbuffer;
	// Generar un buffer, poner el resultado en el vertexbuffer que acabamos de crear
	glGenBuffers(1, &vertexbuffer);
	// Los siguientes comandos le dar�n caracter�sticas especiales al 'vertexbuffer' 
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Darle nuestros v�rtices a  OpenGL.
	glBufferData(GL_ARRAY_BUFFER, size, buffer, GL_STATIC_DRAW);

	return vertexbuffer;
}

void Renderer::DrawBuffer(unsigned int vertexbuffer, int size)
{
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // atributo 0. No hay raz�n particular para el 0, pero debe corresponder en el shader.
		3,                  // tama�o
		GL_FLOAT,           // tipo
		GL_FALSE,           // normalizado?
		0,                    // Paso
		(void*)0            // desfase del buffer
	);
	// Dibujar el tri�ngulo !
	glDrawArrays(GL_TRIANGLES, 0, size); // Empezar desde el v�rtice 0S; 3 v�rtices en total -> 1 tri�ngulo
	glDisableVertexAttribArray(0);
}