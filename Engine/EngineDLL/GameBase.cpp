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

	if (!window) cout << "Holi";

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
	renderer->SetClearColor(0.3, 0.3, 0.3, 0.0);

	bool state = true;
	while (!window->ShouldClose() && state)
	{
		state = OnUpdate();

		renderer->ClearScreen();
		renderer->SwapBuffers();

		window->PollEvents();
	}
}