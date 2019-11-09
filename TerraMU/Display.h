#pragma once
#include <GLFW/glfw3.h>

class Display {
private:
	static int const width = 1280;
	static int const height = 720;
	GLFWwindow *window;

public:
	static constexpr int getWidth() { return width; };
	static constexpr int getHeight() { return height; };

	Display();
	void update();
	bool isCloseRequested();
	GLFWwindow *getWindow() { return window; };
};