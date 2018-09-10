#include "GameBase.h"

GameBase::GameBase()
{
}

GameBase::~GameBase()
{
}

bool GameBase::Start(int width, int height, const char* windowMe)
{
	if (!OnStart())
	{
		return false;
	}

	window = new Window();
	if (!window->Start(width, height, windowMe))
	{
		delete window;
		return false;
	}

	renderer = new Renderer();
	if (!renderer->Start(window))
	{
		delete renderer;
		return false;
	}
	
	return true;
}

bool GameBase::Stop()
{
	OnStop();

	renderer->Stop();
	delete renderer;

	window->Stop();
	delete window;

	return true;
}

void GameBase::Loop()
{
	renderer->SetClearColor(0.0, 0.0, 1, 0.0);

	bool state = true;
	while (!window->ShouldClose() && state)
	{
		renderer->ClearScreen();

		state = OnUpdate();
		
		renderer->SwapBuffers();

		window->PollEvents();
	}
}

Renderer* GameBase::GetRenderer()
{
	return renderer;
}