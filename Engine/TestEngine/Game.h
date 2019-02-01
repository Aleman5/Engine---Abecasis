#pragma once

#include "GameBase.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Sprite.h"
#include "Tilemap.h"
#include "CollisionManager.h"

class Game : public GameBase
{
	Material* material;
	Material* matTexture;
	Sprite* sprite;
	Sprite* sprite2;
	Tilemap* tilemap;

	float speed;		// Speed.
	float translating;	// How much has to translate
	float rotating;		// How much has to rotate
	float scalling;		// How much has to be scaled

protected:
	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate() override;
	bool OnDraw() override;

public:
	Game();
	~Game();
};

