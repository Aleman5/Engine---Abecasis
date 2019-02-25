#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

bool Game::OnStart()
{
	CollisionManager* cmgr = CollisionManager::getInstance();
	
	cmgr->SetRelation(Player, Enemy);
	cmgr->SetRelation(Player, Wall);
	cmgr->SetRelation(Enemy, Wall);

	speed = 100.0f;
	translating = 0.0f;
	rotating = 0.0f;
	scalling = 0.0f;

	playerSpeed = 100.0f;

	gameState = 0;

	material = new Material();
	material->LoadShader("Shaders\\SimpleVertexShader.vertexshader"		// Vertex Shader
					   , "Shaders\\SimpleFragmentShader.fragmentshader"	// Fragment Shader
	);

	matTexture = new Material();
	matTexture->LoadShader("Shaders\\TextureVertexShader.vertexshader"		// Vertex Shader
						, "Shaders\\TextureFragmentShader.fragmentshader"	// Fragment Shader
	);
	//																									 4800  960
	tilemap = new Tilemap(GetRenderer(), matTexture, Default, "SpaceTiles.bmp", 3, 4, "SpaceLevel3.csv", 4800, 960);
	tilemap->Translate(glm::vec3(0.0f, 64.0f, 0.0f));
	GetRenderer()->MoveCamera(glm::vec3(0.0f, 64.0f, 0.0f));

	tilemap->SetTileProperty(0, Obstacle);
	tilemap->SetTileProperty(1, Obstacle);
	tilemap->SetTileProperty(2, Obstacle);
	tilemap->SetTileProperty(3, Obstacle);
	tilemap->SetTileProperty(4, Background);
	tilemap->SetTileProperty(5, Background);
	tilemap->SetTileProperty(6, Death_Trigger);
	tilemap->SetTileProperty(7, Death_Trigger);
	tilemap->SetTileProperty(8, Death_Trigger);
	tilemap->SetTileProperty(9, Death_Trigger);
	tilemap->SetTileProperty(10,Win_Trigger);

	player = new Sprite(GetRenderer(), matTexture, Player, "Ship3.bmp", true, 2, 6, 40.0f, 20.0f, true, tilemap);
	unsigned int frames[6] = { 0, 1, 2, 3, 4, 5 };
	player->GetAnimation()->SetNewAnimation(frames);

	asteroids = new list<Sprite*>;
	for (int i = 0; i < totalAsteroids; i++)
		asteroids->push_back(new Sprite(GetRenderer(), matTexture, Enemy, "Asteroid.bmp", false, 1, 1, 32.0f, 32.0f, false, tilemap));

	cmgr->AddEntity(player->GetEntity());
	for (list<Sprite*>::iterator ast = asteroids->begin(); ast != asteroids->end(); ast++)
		cmgr->AddEntity((*ast)->GetEntity());

	player->SetOriginalPosition(100.0f, 400.0f);

	FillAsteroidsData();

	return true;
}

void Game::FillAsteroidsData()
{
	list<Sprite*>::iterator ast = asteroids->begin();
	(*ast)->SetOriginalPosition(500.0f, 400.0f);
	ast++;
	(*ast)->SetOriginalPosition(830.0f, 400.0f);
	ast++;
	(*ast)->SetOriginalPosition(1050.0f, 400.0f);
	ast++;
	(*ast)->SetOriginalPosition(1050.0f, 300.0f);
	ast++;
	(*ast)->SetOriginalPosition(1050.0f, 500.0f);
	ast++;
	(*ast)->SetOriginalPosition(1500.0f, 350.0f);
	ast++;
	(*ast)->SetOriginalPosition(1750.0f, 600.0f);
	ast++;
	(*ast)->SetOriginalPosition(1900.0f, 400.0f);
	ast++;
	(*ast)->SetOriginalPosition(2300.0f, 600.0f);
	ast++;
	(*ast)->SetOriginalPosition(2500.0f, 500.0f);
	ast++;
	(*ast)->SetOriginalPosition(2700.0f, 550.0f);
	ast++;
	(*ast)->SetOriginalPosition(3000.0f, 550.0f);
	ast++;
	(*ast)->SetOriginalPosition(3050.0f, 518.0f);
	ast++;
	(*ast)->SetOriginalPosition(3100.0f, 486.0f);
	ast++;
	(*ast)->SetOriginalPosition(3200.0f, 454.0f);
	ast++;
	(*ast)->SetOriginalPosition(3700.0f, 605.0f);
	ast++;
	(*ast)->SetOriginalPosition(3900.0f, 410.0f);
	ast++;
	(*ast)->SetOriginalPosition(4200.0f, 450.0f);
	ast++;
	(*ast)->SetOriginalPosition(4500.0f, 470.0f);
	ast++;
	(*ast)->SetOriginalPosition(4600.0f, 502.0f);
	ast++;
	(*ast)->SetOriginalPosition(4700.0f, 534.0f);
	ast++;
	(*ast)->SetOriginalPosition(4750.0f, 566.0f);
	ast++;
	(*ast)->SetOriginalPosition(5000.0f, 600.0f);
	ast++;
	(*ast)->SetOriginalPosition(5200.0f, 450.0f);
	ast++;
	(*ast)->SetOriginalPosition(5500.0f, 500.0f);
}

bool Game::OnStop()
{
	delete material;
	delete matTexture;
	delete player;
	delete asteroids;
	delete tilemap;

	return true;
}

bool Game::OnUpdate()
{
	translating += speed * Defs::getInstance()->deltaTime;
	
	switch (gameState)
	{
	case 0:
	{
		vec2 move = vec2(speed * Defs::getInstance()->deltaTime, 0.0f);

		tilemap->Translate(glm::vec3(move.x, 0.0f, 0.0f));
		GetRenderer()->MoveCamera(glm::vec3(move.x, 0.0f, 0.0f));

		if (input(GLFW_KEY_W))
			move.y += playerSpeed * Defs::getInstance()->deltaTime;

		if (input(GLFW_KEY_S))
			move.y -= playerSpeed * Defs::getInstance()->deltaTime;

		if (input(GLFW_KEY_D))
			move.x += playerSpeed * Defs::getInstance()->deltaTime;

		if (input(GLFW_KEY_A))
			move.x -= playerSpeed * Defs::getInstance()->deltaTime;

		TileType hit = player->Move(move.x, move.y, 0.0f);

		switch (hit)
		{
		case Win_Trigger:
		{
			gameState = 1;
		}
			break;
		case Death_Trigger:
		{
			gameState = -1;

			unsigned int frames[6] = { 6, 7, 8, 9, 10, 11 };
			player->GetAnimation()->SetNewAnimation(frames);
			player->GetAnimation()->SetIsLoop(false);
		}
			break;
		}

		Entity* col = player->OnCollisionEnter();
		if (col)
		{
			if (col->GetTag() == Enemy)
			{
				gameState = -1;
				unsigned int frames[6] = { 6, 7, 8, 9, 10, 11 };
				player->GetAnimation()->SetNewAnimation(frames);
				player->GetAnimation()->SetIsLoop(false);
			}
		}
	}
		break;
	case 1:  // Win
	{

	}
		break;
	case -1: // Lose
	{
		if (player->GetAnimation()->IsFinished())
			Restart();
	}
		break;
	}

	for (list<Sprite*>::iterator ast = asteroids->begin(); ast != asteroids->end(); ast++)
		(*ast)->Translate(-speed * Defs::getInstance()->deltaTime / 2, 0.0f,  0.0f);
	
	tilemap->UpdateUV();

	player->Update();

	for (list<Sprite*>::iterator ast = asteroids->begin(); ast != asteroids->end(); ast++)
		(*ast)->Update();

	if (gameState == 0)
		CollisionManager::getInstance()->DetectCollisions();

	return true;
}

bool Game::OnDraw()
{
	player->Draw();
	for (list<Sprite*>::iterator ast = asteroids->begin(); ast != asteroids->end(); ast++)
		(*ast)->Draw();

	tilemap->Draw();

	return true;
}

void Game::Restart()
{
	// Positions
	tilemap->Teleport(0.0f, 64.0f, 0.0f);
	GetRenderer()->ResetCamera(0.0f, 64.0f);
	player->Teleport(
		player->GetOriginalPosition().x,
		player->GetOriginalPosition().y,
		0.0f);
	for (list<Sprite*>::iterator ast = asteroids->begin(); ast != asteroids->end(); ast++)
		(*ast)->Teleport(
			(*ast)->GetOriginalPosition().x,
			(*ast)->GetOriginalPosition().y,
			0.0f);

	// Animations
	unsigned int frames[6] = { 0, 1, 2, 3, 4, 5 };
	player->GetAnimation()->SetNewAnimation(frames);
	player->GetAnimation()->SetIsLoop(true);

	gameState = 0;
}