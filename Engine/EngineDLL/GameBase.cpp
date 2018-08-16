#include "GameBase.h"

GameBase::GameBase()
{
}

GameBase::~GameBase()
{
}

bool GameBase::Start()
{
	if (!OnStart())
	{
		return false;
	}

	renderer = new Renderer();
	if (!renderer->Start())
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

	return true;
}

void GameBase::Loop()
{
	bool state = true;
	do
	{
		state = OnUpdate();
	} while (state);
}