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
	cmgr->SetRelation(Player, EnemyWeapon);
	cmgr->SetRelation(Enemy, PlayerWeapon);
	cmgr->SetRelation(Player, Wall);
	cmgr->SetRelation(Enemy, Wall);

	speed = 0.0f;
	translating = 0.0f;
	rotating = 0.0f;
	scalling = 0.0f;

	material = new Material();
	material->LoadShader("Shaders\\SimpleVertexShader.vertexshader"		// Vertex Shader
					   , "Shaders\\SimpleFragmentShader.fragmentshader"	// Fragment Shader
	);

	matPlayer = new Material();
	matPlayer->LoadShader("Shaders\\TextureVertexShader.vertexshader"		// Vertex Shader
						, "Shaders\\TextureFragmentShader.fragmentshader"	// Fragment Shader
	);

	matEnemy = new Material();
	matEnemy->LoadShader("Shaders\\TextureVertexShader.vertexshader"		// Vertex Shader
					   , "Shaders\\TextureFragmentShader.fragmentshader"	// Fragment Shader
	);

	sprite = new Sprite(GetRenderer(), matPlayer, Player, "Player-Spritesheet.bmp", true, 5, 8, 1.3f, 2.0f);

	sprite2 = new Sprite(GetRenderer(), matEnemy, Enemy, "Player-Spritesheet.bmp", true, 5, 8, 1.3f, 2.0f);
	//sprite2->SetIsStatic(true);
	sprite2->SetMass(5.0f);

	//sprite3 = new Sprite(GetRenderer(), materialForTexture, Enemy, "Player-Spritesheet.bmp", true, 5, 8, 1.3f, 2.0f);
	
	cmgr->AddEntity(sprite->GetEntity());
	cmgr->AddEntity(sprite2->GetEntity());
	//cmgr->AddEntity(sprite3->GetEntity());
	
	sprite->Translate(-5.0f, 4.0f, 0.0f);
	sprite2->Translate(5.0f, 3.5f, 0.0f);
	//sprite3->Translate(-0.5f, -2.5f, 0.0f);

	tilemap = new Tilemap(GetRenderer(), matPlayer, Default, "Tileset.bmp", 2, 3, 32, 32, "Level.csv", 2400, 800);

	for (int i = 0; i < 3; i++)
		tilemap->SetTileProperty(i, Obstacle);
	tilemap->SetTileProperty(3, Background);
	for (int i = 4; i < 6; i++)
		tilemap->SetTileProperty(i, Obstacle);

	tilemap->UpdateUV();

	return true;
}

bool Game::OnStop()
{
	delete material;
	delete matPlayer;
	delete matEnemy;
	delete sprite;
	delete sprite2;
	//delete sprite3;
	delete tilemap;

	return true;
}

bool Game::OnUpdate()
{
	speed = 2.0f;
	translating += speed * time;

	sprite->Translate(speed * time, 0.0f,  0.0f);
	//sprite2->Translate(-speed * time, 0.0f,  0.0f);
	//sprite3->Translate( 0.0f, speed * time, 0.0f);

	sprite->Update(time);
	sprite2->Update(time);
	//sprite3->Update(time);

	CollisionManager::getInstance()->DetectCollisions();

	return true;
}

bool Game::OnDraw()
{
	tilemap->Draw();

	sprite->Draw();
	sprite2->Draw();
	//sprite3->Draw();

	return true;
}