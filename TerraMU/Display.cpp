#include "Display.h"
#include <iostream>
using namespace std;

Display::Display() {
	this->window = glfwCreateWindow(this->width, this->height, "TerraMU", nullptr, nullptr);
	if (this->window == nullptr) {
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		exit(-1);
	}
	glfwMakeContextCurrent(this->window);

	int width = 0;
	int height = 0;
	glfwGetFramebufferSize(this->window, &width, &height);
	glViewport(0, 0, width, height);
}

void Display::update() {
	glfwSwapBuffers(this->window);
}

bool Display::isCloseRequested() {
	return glfwWindowShouldClose(this->window);
}