#pragma once

#include <iostream>
#include <string>

using namespace std;

class Window
{
	void* window;

	int windowWidth;
	int windowHeight;
	string windowName;

public:
	bool Start(int width, int height, const char* windowMe);
	bool Stop();
	bool ShouldClose();
	void PollEvents();

	void* GetContext(); // Retorna un puntero de un void
	int GetWidth();
	int GetHeight();

	Window();
	~Window();
};
