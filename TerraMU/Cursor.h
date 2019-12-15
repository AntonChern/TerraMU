#pragma once
struct GLFWimage;
struct GLFWcursor;
struct GLFWwindow;

class Cursor {
private:
	GLFWwindow* window;
	GLFWcursor* cursor;
	GLFWimage* image;
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