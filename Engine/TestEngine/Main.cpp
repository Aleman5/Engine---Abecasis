/*
	Abecasis Alejandro 

	Engine
*/

#include <iostream>
#include "Game.h"

using namespace std;

int main()
{
	Game* game = new Game();

	if (game->Start(1024, 720, "Hi world!"))
	{
		game->Loop();
	}

	game->Stop();

	delete game;

	return 0;
}