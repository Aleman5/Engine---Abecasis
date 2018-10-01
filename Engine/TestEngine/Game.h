#pragma once

#include "GameBase.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "ColorShape.h"

class Game : public GameBase
{
	Material* material;
	Triangle* t;
	Rectangle* r;

	float speed;		// Speed of the entity
	float translating;	// How much the entity has to translate
	float rotating;		// How much the entity has to rotate
	float scalling;		// How much the entity has to be scaled

protected:
	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate() override;
	bool OnDraw() override;

public:
	Game();
	~Game();
};

