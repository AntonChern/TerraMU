#include "GameController.h"
#include "Display.h"
#include "WayHandler.h"
#include "Maths.h"

void GameController::cursorPosCallback(GLFWwindow* window, double xPos, double yPos) {
	gui->getInventory()->unplaced(mousePosition.x * 2.0f / Display::getWidth() - 1, 1 - mousePosition.y * 2.0f / Display::getHeight());

	mousePosition = vec2(xPos, yPos);

	GuiElement* cursor = gui->getCursor();
	cursor->setPosition(vec3(2 * (float)mousePosition.x / Display::getWidth() - 1.0f,
		-2 * (float)mousePosition.y / Display::getHeight() + 1.0f, 0.0f));

	gui->getInventory()->placed(mousePosition.x * 2.0f / Display::getWidth() - 1, 1 - mousePosition.y * 2.0f / Display::getHeight());
}

void GameController::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		if (way) {
			delete way;
			way = nullptr;
		}

		lastMouseClick = mousePosition;
		float aspect = (float)Display::getWidth() / (float)Display::getHeight();
		map->interact((2 * lastMouseClick.x / Display::getWidth() * aspect + player->getPosition().x + map->getScale().x / 2 - aspect) * map->getColumns() / map->getScale().x,
			(2 * lastMouseClick.y / Display::getHeight() - player->getPosition().y + map->getScale().y / 2 - 1) * map->getRows() / map->getScale().y);
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
	destination->getAnimation()->reset();
	destination->getAnimation()->play();
	player->getAnimation()->play();
	initialPosition = vec3(player->getPosition().x, player->getPosition().y - player->getScale().y / 2, 0);

	way = handler->buildWay((map->getScale().x / 2 + player->getPosition().x) * map->getColumns() / map->getScale().x,
		(map->getScale().y / 2 - (player->getPosition().y - player->getScale().y / 2)) * map->getRows() / map->getScale().y, coordX, coordY,
		map->getReachMap(), map->getColumns());

	destination->setPosition((coordX - (float)map->getColumns() / 2) * map->getScale().x / map->getColumns() + map->getPosition().x,
		((float)map->getRows() / 2 - coordY) * map->getScale().y / map->getRows() + map->getPosition().y,
		destination->getPosition().z);
}

void GameController::updateMonster(Entity* creature, float deltaTime) {
	if (way && !way->empty()) {
		vec2 flatLocalWay = way->front();
		flatLocalWay = vec2(flatLocalWay.x * map->getScale().x / map->getColumns(), -flatLocalWay.y * map->getScale().y / map->getRows());
		vec3 localWay = vec3(flatLocalWay.x, flatLocalWay.y, 0);
		vec4 expandedStep = scale(mat4(1.0f), vec3(speed * deltaTime, speed * deltaTime, 1.0f)) * normalize(vec4(localWay.x, localWay.y, localWay.z, 0));
		vec3 step = vec3(expandedStep.x, expandedStep.y, expandedStep.z);

		vec3 rest = (initialPosition + localWay) - vec3(creature->getPosition().x, creature->getPosition().y - creature->getScale().y / 2, 0);

		if (length(step) > length(rest)) {
			way->pop();
			initialPosition += localWay;
			update((float)length(step - rest) / speed);
			step = rest;
		}

		int index = (int)(map->getRows() * (map->getScale().y / 2 - (creature->getPosition().y - creature->getScale().y / 2)) / map->getScale().y);
		creature->increasePosition(step.x, step.y, 0);
		creature->setPosition(creature->getPosition().x, creature->getPosition().y, index * 0.001f + 0.0015f);

		if (step.y < -abs(step.x)) {
			creature->getAnimation()->setPosition(0.0f);
		}
		if (step.x <= -abs(step.y)) {
			creature->getAnimation()->setPosition(0.25f);
		}
		if (step.x >= abs(step.y)) {
			creature->getAnimation()->setPosition(0.5f);
		}
		if (step.y > abs(step.x)) {
			creature->getAnimation()->setPosition(0.75f);
		}

	}
	else {
		/*creature->getAnimation()->stop();
		creature->getAnimation()->reset();*/
	}
}

void GameController::updatePlayer(Entity* creature, float deltaTime) {
	if (way && !way->empty()) {
		vec2 flatLocalWay = way->front();
		flatLocalWay = vec2(flatLocalWay.x * map->getScale().x / map->getColumns(), -flatLocalWay.y * map->getScale().y / map->getRows());
		vec3 localWay = vec3(flatLocalWay.x, flatLocalWay.y, 0);
		vec4 expandedStep = scale(mat4(1.0f), vec3(speed * deltaTime, speed * deltaTime, 1.0f)) * normalize(vec4(localWay.x, localWay.y, localWay.z, 0));
		vec3 step = vec3(expandedStep.x, expandedStep.y, expandedStep.z);

		vec3 rest = (initialPosition + localWay) - vec3(creature->getPosition().x, creature->getPosition().y - creature->getScale().y / 2, 0);

		if (length(step) > length(rest)) {
			way->pop();
			initialPosition += localWay;
			update((float)length(step - rest) / speed);
			step = rest;
		}

		int index = (int)(map->getRows() * (map->getScale().y / 2 - (creature->getPosition().y - creature->getScale().y / 2)) / map->getScale().y);
		creature->increasePosition(step.x, step.y, 0);
		creature->setPosition(creature->getPosition().x, creature->getPosition().y, index * 0.001f + 0.0015f);
		camera->increasePosition(step.x, step.y, 0);

		if (step.y < -abs(step.x)) {
			creature->getAnimation()->setPosition(0.0f);
		}
		if (step.x <= -abs(step.y)) {
			creature->getAnimation()->setPosition(0.25f);
		}
		if (step.x >= abs(step.y)) {
			creature->getAnimation()->setPosition(0.5f);
		}
		if (step.y > abs(step.x)) {
			creature->getAnimation()->setPosition(0.75f);
		}

	} else {
		destination->getAnimation()->stop();
		creature->getAnimation()->stop();
		creature->getAnimation()->reset();
	}
}

void GameController::update(float deltaTime) {
	updatePlayer(player, deltaTime);
	for (Entity* monster : monsters) {
		updateMonster(monster, deltaTime);
	}
}

void GameController::addMonsters(list<Entity*> monsters) {
	for (Entity* monster : monsters) {
		addMonster(monster);
	}
}