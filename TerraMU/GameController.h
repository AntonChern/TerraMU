#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
class Map;
#include "Map.h"
#include "MapObject.h"
#include "Entity.h"
#include "WayHandler.h"

class GameController {
private:
	static Map* map;
	static Entity* player;
	static Entity* cursor;
	static Camera* camera;

	static vec2 mouseOffset;

	static vec2 mousePosition;
	static vec2 lastMouseClick;

	static float lastTime;

	static WayHandler* handler;
	static queue<vec2>* way;
	static vec3 initialPosition;

	static vec2 textureTranslate;
	static vec2 textureStep;
	static int textureTime;

	static float speed;

	static float getDeltaTime();
	
public:
	static void initialize();

	static void cursorPosCallback(GLFWwindow* window, double xPos, double yPos);
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void cursorEnterCallback(GLFWwindow* window, int entered);
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

	static void setMap(Map* map) { GameController::map = map; };
	static void setPlayer(Entity* player) { GameController::player = player; };
	static void setCursor(Entity* cursor) { GameController::cursor = cursor; };
	static void setCamera(Camera* camera) { GameController::camera = camera; };

	static void update(float deltaTime);

	static void go(float coordX, float coordY);
	static void changeVisibility(int posX, int posY);

};