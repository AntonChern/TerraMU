#pragma once
#include <GLFW/glfw3.h>
#include <SOIL.h>

class Cursor {
private:
	GLFWwindow* window;
	GLFWcursor* cursor;
	GLFWimage image;
	unsigned char* pixels;

public:
	Cursor(GLFWwindow* window, char const filePath[]);
	~Cursor();

	void reset();
	void makeRed();
	void makeBlue();
	void makeMagenta();
	void makeOrange();
	
};