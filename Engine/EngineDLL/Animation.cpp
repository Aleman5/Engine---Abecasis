#include "Animation.h"
#include "Sprite.h"

Animation::Animation(Sprite* sprite, unsigned int frames[], bool isLooping, float frameRate)
	: sprite(sprite), isLooping(isLooping), isFinished(true), frameRate(1.0f / frameRate)
{
	unsigned int size = sizeof(frames) / sizeof(unsigned int);

	this->frames = new queue<unsigned int>;

	for (int i = 0; i < size; i++)
		this->frames->push(frames[i]);

	actualFrame = 0;
	lastFrame = this->frames->back();

	Play();
}
Animation::~Animation()
{
}

void Animation::Play()
{
	time = 0.0f;
	isFinished = false;
}

void Animation::Update(float deltaTime)
{
	time += deltaTime;
	if (time > frameRate)
	{
		time = 0.0f;
		if (!isFinished)
		{
			actualFrame = frames->front();
			frames->pop();
			frames->push(actualFrame);
			sprite->SetNextFrame(actualFrame);

			if (actualFrame == lastFrame && !isLooping)
				isFinished = true;
		}
	}
}