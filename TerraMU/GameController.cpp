#include "GameController.h"
#include "Display.h"
#include "WayHandler.h"
#include "Maths.h"
#include "Converter.h"

void GameController::cursorPosCallback(GLFWwindow* window, double xPos, double yPos) {
	gui->getInventory()->unplaced(mousePosition.x * 2.0f / Display::getWidth() - 1, 1 - mousePosition.y * 2.0f / Display::getHeight());

	mousePosition = vec2(xPos, yPos);

	GuiElement* cursor = gui->getCursor();
	vec2 mousePosition = Converter::fromDisplayToOpenGL(mousePosition);
	cursor->setPosition(mousePosition.x, mousePosition.y, 0.0f);

	gui->getInventory()->placed(mousePosition.x * 2.0f / Display::getWidth() - 1, 1 - mousePosition.y * 2.0f / Display::getHeight());
}

void GameController::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		if (!player->isInMotion()) {
			player->getAvatar()->getAnimation()->play();
		}
		player->nullWay();

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
	if (key == GLFW_KEY_V && action == GLFW_PRESS) {
		GuiItem* inventory = gui->getInventory();
		vec3 cameraOffset(0.0f);
		if (inventory->getIsVisible()) {
			cameraOffset = vec3(-inventory->getScale().x * Camera::getWidth() / 2 / 2, 0.0f, 0.0f);
		}
		else {
			cameraOffset = vec3(inventory->getScale().x * Camera::getWidth() / 2 / 2, 0.0f, 0.0f);
		}
		camera->increasePosition(cameraOffset);
		inventory->changeVisibility();
	}
}

void GameController::go(float coordX, float coordY) {
	player->go(coordX, coordY);
}
