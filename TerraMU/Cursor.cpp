#include "Cursor.h"
#include <GLFW/glfw3.h>
#include <SOIL.h>

Cursor::Cursor(GLFWwindow* window, char const filePath[]) : window(window) {
	GLFWimage im;
	image = &im;
	pixels = SOIL_load_image(filePath, &(image->width), &(image->height), 0, SOIL_LOAD_RGBA);
	image->height = image->width;
	image->pixels = pixels;

	cursor = glfwCreateCursor(image, 0, 0);
	glfwSetCursor(window, cursor);
}

Cursor::~Cursor() {
	SOIL_free_image_data(pixels);
	glfwDestroyCursor(cursor);
}

void Cursor::reset() {
	image->pixels = pixels;

	cursor = glfwCreateCursor(image, 0, 0);
	glfwSetCursor(window, cursor);
}

void Cursor::makeRed() {
	image->pixels = &(pixels[4 * image->width * image->width]);

	cursor = glfwCreateCursor(image, 0, 0);
	glfwSetCursor(window, cursor);
}

void Cursor::makeBlue() {
	image->pixels = &(pixels[2 * 4 * image->width * image->width]);

	cursor = glfwCreateCursor(image, 0, 0);
	glfwSetCursor(window, cursor);
}

void Cursor::makeMagenta() {
	image->pixels = &(pixels[3 * 4 * image->width * image->width]);

	cursor = glfwCreateCursor(image, 0, 0);
	glfwSetCursor(window, cursor);
}

void Cursor::makeOrange() {
	image->pixels = &(pixels[4 * 4 * image->width * image->width]);

	cursor = glfwCreateCursor(image, 0, 0);
	glfwSetCursor(window, cursor);
}