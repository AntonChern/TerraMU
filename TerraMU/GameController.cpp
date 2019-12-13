#include "GameController.h"
#include "Display.h"
#include "WayHandler.h"
#include "Maths.h"
#include "Converter.h"

void GameController::cursorPosCallback(GLFWwindow* window, double xPos, double yPos) {
	gui->unplaced(mousePosition.x * 2.0f / Display::getWidth() - 1, 1 - mousePosition.y * 2.0f / Display::getHeight());

	mousePosition = vec2(xPos, yPos);

	/*GuiElement* cursor = gui->getCursor();
	vec2 updatedMousePosition = Converter::fromDisplayToOpenGL(mousePosition);
	cursor->setPosition(2 * mousePosition.x / Display::getWidth() - 1, 1 - 2 * mousePosition.y / Display::getHeight(), 0.0f);*/

	gui->placed(mousePosition.x * 2.0f / Display::getWidth() - 1, 1 - mousePosition.y * 2.0f / Display::getHeight());
}

void GameController::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	vec2 mousePosMap = Converter::fromDisplayToMap(mousePosition);
	vec2 mousePosGui = Converter::fromDisplayToGui(mousePosition);
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		if (!gui->clicked(mousePosGui.x, mousePosGui.y)) {
			if (!player->isInMotion()) {
				player->getAvatar()->getAnimation()->play();
			}
			player->nullWay();

			map->interact(mousePosMap.x, mousePosMap.y);
		}
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		gui->unclicked(mousePosGui.x, mousePosGui.y);
	}
}

void GameController::cursorEnterCallback(GLFWwindow* window, int entered) {

}

void GameController::processPanel(GuiItem* currPanel) {
	list<GuiItem*> visiblePanels = *gui->getVisiblePanels();
	bool exists = false;
	for (GuiItem* panel : visiblePanels) {
		if (panel == currPanel) {
			exists = true;
			break;
		}
	}

	vec3 cameraOffset(0.0f);
	for (GuiItem* panel : visiblePanels) {
		cameraOffset += vec3(-panel->getScale().x * Camera::getWidth() / 2 / 2, 0.0f, 0.0f);
	}

	if (exists) {
		*gui->getVisiblePanels() = {};
	}
	else {
		*gui->getVisiblePanels() = {currPanel};
		cameraOffset += vec3(currPanel->getScale().x * Camera::getWidth() / 2 / 2, 0.0f, 0.0f);
	}
	camera->increasePosition(cameraOffset);
}

void GameController::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key == GLFW_KEY_V && action == GLFW_PRESS) {
		GameController::processPanel(gui->getInventory());
	}
	if (key == GLFW_KEY_C && action == GLFW_PRESS) {
		GameController::processPanel(gui->getPoints());
	}
}

void GameController::go(float coordX, float coordY) {
	player->go(coordX, coordY);
}
