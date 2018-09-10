#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

bool Game::OnStart()
{
	t = new Triangle(GetRenderer());

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