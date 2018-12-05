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
	GetRenderer()->MoveCamera(glm::vec3(0.0f,/* speed * time * 3*/ 10.0f, 0.0f)); // This is temp
	for (int i = 0; i < 3; i++)
		tilemap->SetTileProperty(i, Obstacle);
	tilemap->SetTileProperty(3, Background);
	for (int i = 4; i < 6; i++)
		tilemap->SetTileProperty(i, Obstacle);

	//tilemap->UpdateUV();

	sprite = new Sprite(GetRenderer(), matTexture, Player, "Player-Spritesheet.bmp", true, 5, 8, 1.3f, 2.0f, true, tilemap);
	unsigned int frames[5] = { 5, 6, 7, 8, 9 };
	sprite->GetAnimation()->SetNewAnimation(frames);

	sprite2 = new Sprite(GetRenderer(), matTexture, Enemy, "Player-Spritesheet.bmp", false, 5, 8, 1.3f, 2.0f, true, tilemap);
	//sprite2->SetIsStatic(true);
	sprite2->SetMass(5.0f);
	

	//sprite3 = new Sprite(GetRenderer(), matTexture, Enemy, "Player-Spritesheet.bmp", true, 5, 8, 1.3f, 2.0f, true, tilemap);
	
	cmgr->AddEntity(sprite->GetEntity());
	cmgr->AddEntity(sprite2->GetEntity());
	//cmgr->AddEntity(sprite3->GetEntity());
	
	sprite->Translate(-5.0f, 4.0f, 0.0f);
	sprite2->Translate(5.0f, 3.5f, 0.0f);
	//sprite3->Translate(-0.5f, -2.5f, 0.0f);


	/*cout << sprite->GetPosition().x << " " << sprite->GetPosition().y << endl;
	cout << sprite2->GetPosition().x << " " << sprite2->GetPosition().y << endl;
	cout << tilemap->GetPosition().x << " " << tilemap->GetPosition().y << " " << tilemap->GetPosition().z << endl;*/

	return true;
}

bool Game::OnStop()
{
	delete material;
	delete matTexture;
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

	GetRenderer()->MoveCamera(glm::vec3(speed * time , speed * time * 3, 0.0f));

	sprite->Translate(speed * time, 0.0f,  0.0f);
	//sprite2->Translate(-speed * time, 0.0f,  0.0f);
	//sprite3->Translate( 0.0f, speed * time, 0.0f);
	
	tilemap->UpdateUV();

	sprite->Update(time);
	sprite2->Update(time);
	//sprite3->Update(time);

	CollisionManager::getInstance()->DetectCollisions();

	return true;
}

bool Game::OnDraw()
{
	sprite->Draw();
	sprite2->Draw();
	//sprite3->Draw();

	tilemap->Draw();

	return true;
}