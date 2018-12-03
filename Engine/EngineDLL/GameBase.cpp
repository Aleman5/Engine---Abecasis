#include "GameBase.h"

GameBase::GameBase()
{
}

GameBase::~GameBase()
{
}

bool GameBase::Start(int width, int height, const char* windowMe)
{
	time = 0.0f;
	currentFrame = 0.0f;
	lastFrame = 0.0f;

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
	
	if (!OnStart())
	{
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
	renderer->SetClearColor(0.3f, 0.3f, 0.3f, 0.0); // Dark Gray

	bool state = true;
	while (!window->ShouldClose() && state)
	{
		renderer->ClearScreen();

		Time();

		state = OnUpdate();
		state = OnDraw();

		renderer->SwapBuffers();

		window->PollEvents();
	}
}

void GameBase::Time()
{
	currentFrame = glfwGetTime();		// Save the actual time
	time = currentFrame - lastFrame;	// Make a difference btw the actualFrame and the lastFrame
	lastFrame = currentFrame;			// Save the lastFrame with the actual time
}

Renderer* GameBase::GetRenderer()
{
	return renderer;
}