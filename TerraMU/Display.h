#pragma once
#include <GLFW/glfw3.h>

class Display {
private:
	int const width = 1280;
	int const height = 720;
	GLFWwindow *window;

public:
	Display();
	void update();
	bool isCloseRequested();
	GLFWwindow *getWindow() { return window; };
};