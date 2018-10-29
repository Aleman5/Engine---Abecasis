#pragma once



class ICollisionCallback
{
	unsigned int width;
	unsigned int height;
	bool isStatic;

public:
	virtual void SetDimensions() = 0;
};

