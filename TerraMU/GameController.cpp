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
	//destination->getAnimation()->reset();
	//destination->getAnimation()->play();
	//creature->getAvatar()->getAnimation()->play();
	//initialPosition = vec3(creature->getAvatar()->getPosition().x, creature->getAvatar()->getPosition().y - creature->getAvatar()->getScale().y / 2, 0);
	////player->getAnimation()->play();
	////initialPosition = vec3(player->getPosition().x, player->getPosition().y - player->getScale().y / 2, 0);


	//vec2 origin = Converter::fromOpenGLToMap(vec2(creature->getAvatar()->getPosition().x, creature->getAvatar()->getPosition().y - creature->getAvatar()->getScale().y / 2));
	////vec2 origin = Converter::fromOpenGLToMap(vec2(player->getPosition().x, player->getPosition().y - player->getScale().y / 2));

	//way = WayHandler::buildWay(origin.x, origin.y, coordX, coordY, map->getReachMap(), map->getColumns(), map->getRows());

	//vec2 whither = Converter::fromMapToOpenGL(vec2(coordX, coordY));
	//destination->setPosition(whither.x, whither.y, destination->getPosition().z);

	creature->go(coordX, coordY);
}

//void GameController::update(float deltaTime) {
	//if (way && !way->empty()) {
	//	vec2 flatLocalWay = way->front();
	//	if (flatLocalWay == vec2(0.0f, 0.0f)) {
	//		way->pop();
	//		return;
	//	}
	//	flatLocalWay = vec2(flatLocalWay.x * map->getScale().x / map->getColumns(), -flatLocalWay.y * map->getScale().y / map->getRows());
	//	vec3 localWay = vec3(flatLocalWay.x, flatLocalWay.y, 0);
	//	vec4 expandedStep = scale(mat4(1.0f), vec3(speed * deltaTime, speed * deltaTime, 1.0f)) * normalize(vec4(localWay.x, localWay.y, localWay.z, 0));
	//	vec3 step = vec3(expandedStep.x, expandedStep.y, expandedStep.z);

	//	vec3 rest = (initialPosition + localWay) - vec3(creature->getAvatar()->getPosition().x, creature->getAvatar()->getPosition().y - creature->getAvatar()->getScale().y / 2, 0);
	//	//vec3 rest = (initialPosition + localWay) - vec3(player->getPosition().x, player->getPosition().y - player->getScale().y / 2, 0);

	//	if (length(step) > length(rest)) {
	//		way->pop();
	//		initialPosition += localWay;
	//		update((float)length(step - rest) / speed);
	//		step = rest;
	//	}


	//	int index = Converter::fromOpenGLToMap(vec2(creature->getAvatar()->getPosition().y)).y;
	//	creature->getAvatar()->increasePosition(step.x, step.y, 0);
	//	creature->getAvatar()->setPosition(creature->getAvatar()->getPosition().x, creature->getAvatar()->getPosition().y, index * 0.001f + 0.0015f);
	//	//int index = Converter::fromOpenGLToMap(vec2(player->getPosition().y)).y;
	//	//player->increasePosition(step.x, step.y, 0);
	//	//player->setPosition(player->getPosition().x, player->getPosition().y, index * 0.001f + 0.0015f);
	//	camera->increasePosition(step.x, step.y, 0);

	//	if (step.y < -abs(step.x)) {
	//		creature->getAvatar()->getAnimation()->setPosition(0.0f);
	//		//player->getAnimation()->setPosition(0.0f);
	//	}
	//	if (step.x <= -abs(step.y)) {
	//		creature->getAvatar()->getAnimation()->setPosition(0.25f);
	//		//player->getAnimation()->setPosition(0.25f);
	//	}
	//	if (step.x >= abs(step.y)) {
	//		creature->getAvatar()->getAnimation()->setPosition(0.5f);
	//		//player->getAnimation()->setPosition(0.5f);
	//	}
	//	if (step.y > abs(step.x)) {
	//		creature->getAvatar()->getAnimation()->setPosition(0.75f);
	//		//player->getAnimation()->setPosition(0.75f);
	//	}
	//} else {
	//	destination->getAnimation()->stop();
	//	creature->getAvatar()->getAnimation()->stop();
	//	creature->getAvatar()->getAnimation()->reset();
	//	//player->getAnimation()->stop();
	//	//player->getAnimation()->reset();
	//}

	//creature->update(deltaTime);
//}