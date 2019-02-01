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

	matTexture = new Material();
	matTexture->LoadShader("Shaders\\TextureVertexShader.vertexshader"		// Vertex Shader
						, "Shaders\\TextureFragmentShader.fragmentshader"	// Fragment Shader
	);

	tilemap = new Tilemap(GetRenderer(), matTexture, Default, "Tileset.bmp", 2, 3, "Level.csv", 2400, 800);
	
	tilemap->Translate(-10.0f, -10.0f, 0.0f);

	for (int i = 0; i < 3; i++)
		tilemap->SetTileProperty(i, Obstacle);
	tilemap->SetTileProperty(3, Background);
	for (int i = 4; i < 6; i++)
		tilemap->SetTileProperty(i, Obstacle);

	sprite = new Sprite(GetRenderer(), matTexture, Player, "Player-Spritesheet.bmp", true, 5, 8, 1.3f, 2.0f, true, tilemap);
	unsigned int frames[5] = { 5, 6, 7, 8, 9 };
	sprite->GetAnimation()->SetNewAnimation(frames);

	sprite2 = new Sprite(GetRenderer(), matTexture, Enemy, "Player-Spritesheet.bmp", false, 5, 8, 1.3f, 2.0f, true, tilemap);
	//sprite2->SetIsStatic(true);
	sprite2->SetMass(5.0f);

	cmgr->AddEntity(sprite->GetEntity());
	cmgr->AddEntity(sprite2->GetEntity());
	
	sprite->Translate(-5.0f, 4.0f, 0.0f);
	sprite2->Translate(5.0f, 3.5f, 0.0f);

	return true;
}

bool Game::OnStop()
{
	delete material;
	delete matTexture;
	delete sprite;
	delete sprite2;
	delete tilemap;

	return true;
}

bool Game::OnUpdate()
{
	speed = 2.0f;
	translating += speed * Defs::getInstance()->deltaTime;
	
	//GetRenderer()->MoveCamera(glm::vec3(speed * Defs::getInstance()->deltaTime * 2/3, 0.0f, 0.0f));	// This is to move the camera every frame
	
	sprite->Translate(speed * Defs::getInstance()->deltaTime, 0.0f,  0.0f);
	//sprite2->Translate(-speed * Definitions::getInstance()->deltaTime, 0.0f,  0.0f);
	
	tilemap->UpdateUV();

	sprite->Update();
	sprite2->Update();

	CollisionManager::getInstance()->DetectCollisions();

	return true;
}

bool Game::OnDraw()
{
	sprite->Draw();
	sprite2->Draw();

	tilemap->Draw();

	return true;
}