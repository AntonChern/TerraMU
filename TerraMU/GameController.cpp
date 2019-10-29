#include "GameController.h"
#include "Display.h"

void GameController::cursorPosCallback(GLFWwindow* window, double xPos, double yPos) {
	mousePosition = vec2(xPos, yPos);
}

void GameController::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		lastMouseClick = mousePosition;
		float aspect = (float)Display::getWidth() / (float)Display::getHeight();
		map->interact((2 * lastMouseClick.x / Display::getWidth() * aspect - map->getPosition().x + map->getScale().x - aspect) * map->getColumns() / (2 * map->getScale().x),
			(2 * lastMouseClick.y / Display::getHeight() + map->getPosition().y + map->getScale().y - 1) * map->getRows() / (2 * map->getScale().y));
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
	cout << "Method GameController::go() has been called at point " << coordX << " : " << coordY << endl;
}