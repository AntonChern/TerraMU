#include "GameController.h"
#include "Display.h"

void GameController::cursorPosCallback(GLFWwindow* window, double xPos, double yPos) {
	mousePosition = vec2(xPos, yPos);
}

void GameController::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		lastMouseClick = mousePosition;
		map->interact((2 * mousePosition.x / Display::getWidth() - map->getPosition().x + map->getScale().x - 1) * map->getColumns() / (2 * map->getScale().x),
			(2 * mousePosition.y / Display::getHeight() + map->getPosition().y + map->getScale().y - 1) * map->getRows() / (2 * map->getScale().y));
	}
}

void GameController::cursorEnterCallback(GLFWwindow* window, int entered) {

}

void GameController::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

void GameController::go() {
	cout << "Method GameController::go() has been called" << endl;
}