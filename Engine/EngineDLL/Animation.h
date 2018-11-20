#pragma once

#include <queue>
#include "Exports.h"

using namespace std;

class Sprite;

class ENGINEDLL_API Animation
{
	Sprite* sprite;

	unsigned int actualFrame;
	unsigned int lastFrame;

	float time;
	float frameRate;
	float frameTime;

	bool isLooping;
	bool isStopped;
	bool isFinished;

	queue<unsigned int>* frames;

public:
	void Play(); // Starts playing.
	void Stop(); // Stops playing.
	void Update(float deltaTime); // Updates the actual frame.

	Animation(Sprite* sprite, unsigned int frames[], bool isLooping, float frameRate);
	~Animation();
};