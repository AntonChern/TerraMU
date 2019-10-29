#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
class Map;
#include "Map.h"
#include "MapObject.h"
#include "Entity.h"

class GameController {
private:
	static Map* map;
	static Entity* player;

	static vec2 mousePosition;
	static vec2 lastMouseClick;
	
public:
	static void cursorPosCallback(GLFWwindow* window, double xPos, double yPos);
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void cursorEnterCallback(GLFWwindow* window, int entered);
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

	static void setMap(Map* map) { GameController::map = map; };
	static void setPlayer(Entity* player) { GameController::player = player; };

	static void go(float coordX, float coordY);
	static void changeVisibility(int posX, int posY);

	static void showInventory();
	static void hideInventory();

	static void showChest();
	static void hideChest();

	static void showPoints();
	static void hidePoints();


};