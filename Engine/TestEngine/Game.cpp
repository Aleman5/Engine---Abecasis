#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

bool Game::OnStart()
{
	CollisionManager::getInstance();
	CollisionManager::SetRelation(Player, Enemy);
	CollisionManager::SetRelation(Player, EnemyWeapon);
	CollisionManager::SetRelation(Enemy, PlayerWeapon);
	CollisionManager::SetRelation(Player, Wall);
	CollisionManager::SetRelation(Enemy, Wall);

	speed = 0.0f;
	translating = 0.0f;
	rotating = 0.0f;
	scalling = 0.0f;

	material = new Material();
	material->LoadShader("Shaders\\SimpleVertexShader.vertexshader"		// Vertex Shader
					   , "Shaders\\SimpleFragmentShader.fragmentshader"	// Fragment Shader
	);

	materialForTexture = new Material();
	materialForTexture->LoadShader("Shaders\\TextureVertexShader.vertexshader"		// Vertex Shader
								 , "Shaders\\TextureFragmentShader.fragmentshader"	// Fragment Shader
	);

	sprite = new Sprite(GetRenderer(), materialForTexture, Default, "Skull.bmp", 1, 1, 0.6f, 1.0f);
	sprite->Scale(2.0f, 2.0f, 2.0f);
	
	t = new Triangle(GetRenderer(), material, Default);
	r = new Rectangle(GetRenderer(), material, Default);
	c = new Circle(GetRenderer(), material, Default, 4.0f, 20);

	r->Translate(1.5f, 1.5f, 0.0f);
	c->Translate(-3.0f, 4.0f, 0.0f);

	return true;
}

bool Game::OnStop()
{
	delete material;
	delete materialForTexture;
	delete sprite;
	delete t;
	delete r;
	delete c;

	return true;
}

bool Game::OnUpdate()
{
	speed = 1.0f;
	translating += speed * time;

	t->Translate(1.0f + translating, 0.0f, 0.0f);
	r->RotateX(135.0f * translating);
	r->RotateY(90.0f * translating);
	r->RotateZ(180.0f * translating);

	CollisionManager::DetectCollisions();

	return true;
}

bool Game::OnDraw()
{
	sprite->Draw();
	t->Draw();
	r->Draw();
	c->Draw();

	return true;
}