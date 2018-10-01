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
	bool Start(int width,		// Width of the Window.
		int height,				// Height of the Window.
		const char* windowMe	// Name of the Window.
	);
	bool Stop();
	bool ShouldClose();
	void PollEvents();

	void* GetContext(); // Returns a pointer to void.
	int GetWidth();
	int GetHeight();

	Window();
	~Window();
};

