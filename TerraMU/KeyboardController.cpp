#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "KeyboardController.h"
using namespace std;

//KeyboardController::KeyboardController(Camera *receivedCamera, Display *receivedDisplay) {
//	camera = receivedCamera;
//	display = receivedDisplay;
//}
//
//void KeyboardController::process() {
//	if (glfwGetKey(display->getWindow(), GLFW_KEY_UP) == GLFW_PRESS) {
//		camera->increasePosition(0.0f, 0.0f, -0.02f);
//	}
//	if (glfwGetKey(display->getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS) {
//		camera->increasePosition(0.0f, 0.0f, 0.02f);
//	}
//	if (glfwGetKey(display->getWindow(), GLFW_KEY_LEFT) == GLFW_PRESS) {
//		camera->increasePosition(-0.02f, 0.0f, 0.0f);
//	}
//	if (glfwGetKey(display->getWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS) {
//		camera->increasePosition(0.02f, 0.0f, 0.0f);
//	}
//}