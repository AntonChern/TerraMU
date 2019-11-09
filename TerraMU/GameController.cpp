#include "GameController.h"
#include "Display.h"
#include "WayHandler.h"
#include "Maths.h"
#include "Converter.h"

void GameController::cursorPosCallback(GLFWwindow* window, double xPos, double yPos) {
	mousePosition = vec2(xPos, yPos);
	vec2 mousePosition = Converter::fromDisplayToOpenGL(mousePosition);
	cursor->setPosition(mousePosition.x, mousePosition.y, 0.0f);
}

void GameController::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		creature->nullWay();

		lastMouseClick = Converter::fromDisplayToMap(mousePosition);
		map->interact(lastMouseClick.x, lastMouseClick.y);
	}
}

void GameController::cursorEnterCallback(GLFWwindow* window, int entered) {

}

void GameController::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

void GameController::go(float coordX, float coordY) {
	creature->go(coordX, coordY);
}

void GameController::update(float deltaTime) {
	creature->update(deltaTime);
}