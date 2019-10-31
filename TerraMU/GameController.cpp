#include "GameController.h"
#include "Display.h"
#include "WayHandler.h"

float GameController::getDeltaTime() {
	float currentTime = glfwGetTime();
	float deltaTime = currentTime - lastTime;
	lastTime = currentTime;
	return deltaTime;
}

void GameController::initialize() {
	lastTime = glfwGetTime();
}

void GameController::cursorPosCallback(GLFWwindow* window, double xPos, double yPos) {
	mousePosition = vec2(xPos, yPos);
	float aspect = (float)Display::getWidth() / (float)Display::getHeight();
	cursor->setPosition(aspect * (2 * (float)mousePosition.x / Display::getWidth() - 1.0f),
		-2 * (float)mousePosition.y / Display::getHeight() + 1.0f, 0.0f);
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
}

void GameController::go(float coordX, float coordY) {
	initialPosition = vec3(player->getPosition().x, player->getPosition().y - player->getScale().y / 2, 0);
	way = handler->buildWay((map->getScale().x / 2 + player->getPosition().x) * map->getColumns() / map->getScale().x,
		(map->getScale().y / 2 - (player->getPosition().y - player->getScale().y / 2)) * map->getRows() / map->getScale().y, coordX, coordY,
		map->getReachMap(), map->getColumns());
}

void GameController::update(float deltaTime) {
	if (way && !way->empty()) {
		vec2 flatLocalWay = way->front();
		flatLocalWay = vec2(flatLocalWay.x * map->getScale().x / map->getColumns(), -flatLocalWay.y * map->getScale().y / map->getRows());
		vec3 localWay = vec3(flatLocalWay.x, flatLocalWay.y, 0);
		vec4 expandedStep = scale(mat4(1.0f), vec3(speed * deltaTime, speed * deltaTime, 1.0f)) * normalize(vec4(localWay.x, localWay.y, localWay.z, 0));
		vec3 step = vec3(expandedStep.x, expandedStep.y, expandedStep.z);

		vec3 rest = (initialPosition + localWay) - vec3(player->getPosition().x, player->getPosition().y - player->getScale().y / 2, 0);

		if (length(step) > length(rest)) {
			way->pop();
			initialPosition += localWay;
			update((float)length(step - rest) / speed);
			step = rest;
		}

		int index = (int)(map->getRows() * (map->getScale().y / 2 - (player->getPosition().y - player->getScale().y / 2)) / map->getScale().y);
		player->increasePosition(step.x, step.y, 0);
		player->setPosition(player->getPosition().x, player->getPosition().y, index * 0.001f + 0.0015f);
		camera->increasePosition(step.x, step.y, 0);

		if (textureTime == 6) {
			if (step.y < -abs(step.x)) {
				textureStep = vec2(textureStep.x, 0.0f);
			}
			if (step.x <= -abs(step.y)) {
				textureStep = vec2(textureStep.x, 0.25f);
			}
			if (step.x >= abs(step.y)) {
				textureStep = vec2(textureStep.x, 0.5f);
			}
			if (step.y > abs(step.x)) {
				textureStep = vec2(textureStep.x, 0.75f);
			}

			if (textureTranslate + textureStep == vec2(1.0f, (textureTranslate + textureStep).y) || textureTranslate + textureStep == vec2(-1.0f / 3.0f, (textureTranslate + textureStep).y)) {
				textureStep.x *= -1;
			}
			textureTranslate.x += textureStep.x;
			textureTranslate.y = textureStep.y;
			textureTime = 0;
		}
		textureTime++;
	} else {
		textureTranslate = vec2(1.0f / 3.0f, textureTranslate.y);
	}

	mat3 texture(1.0f);
	texture = translate(texture, textureTranslate);
	texture = scale(texture, vec2(1.0f / 3.0f, 0.25f));
	player->setTextureMatrix(texture);
}