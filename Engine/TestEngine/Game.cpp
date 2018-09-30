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
	r = new Rectangle(GetRenderer(), material);
	//c = new ColorShape(GetRenderer(), material);

	return true;
}

bool Game::OnStop()
{
	delete t;
	delete r;
	//delete c;

	return true;
}

bool Game::OnUpdate()
{
	r->Translate(1.5f, 1.5f, 0.0f);

	t->Draw();
	r->Draw();
	//c->Draw();

	return true;
}