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

	if (game->Start())
	{
		game->Loop();
	}

	game->Stop();

	delete game;

	cin.get();

	return 0;
}