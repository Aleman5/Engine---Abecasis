#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

bool Game::OnStart()
{
	material = new Material();
	material->LoadShader("Shaders\\SimpleVertexShader.vertexshader"		// Vertex Shader
					   , "Shaders\\SimpleFragmentShader.fragmentshader"	// Fragment Shader
	);

	t = new Triangle(GetRenderer(), material);

	return true;
}

bool Game::OnStop()
{
	delete t;

	return true;
}

bool Game::OnUpdate()
{
	t->Draw();

	return true;
}