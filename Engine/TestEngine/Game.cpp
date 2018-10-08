#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

bool Game::OnStart()
{
	speed = 0.0f;
	translating = 0.0f;
	rotating = 0.0f;
	scalling = 0.0f;

	material = new Material();
	material->LoadShader("Shaders\\SimpleVertexShader.vertexshader"		// Vertex Shader
					   , "Shaders\\SimpleFragmentShader.fragmentshader"	// Fragment Shader
	);

	t = new Triangle(GetRenderer(), material);
	r = new Rectangle(GetRenderer(), material);
	c = new Circle(GetRenderer(), material, 4.0f, 20);

	r->Translate(1.5f, 1.5f, 0.0f);
	c->Translate(-1.0f, 2.0f, 0.0f);

	return true;
}

bool Game::OnStop()
{
	delete t;
	delete r;
	delete c;

	return true;
}

bool Game::OnUpdate()
{
	speed = 1.0f;
	translating += speed * time;

	t->Translate(1.0f + translating, 0.0f, 0.0f);
	r->RotateX(135.0f * translating);
	r->RotateY(90.0f * translating);
	r->RotateZ(180.0f * translating);

	return true;
}

bool Game::OnDraw()
{
	t->Draw();
	r->Draw();
	c->Draw();

	return true;
}