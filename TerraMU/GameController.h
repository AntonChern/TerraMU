#pragma once
class Map;
class Creature;
#include "Map.h"
//#include "MapObject.h"
#include "Entity.h"
#include "WayHandler.h"
#include "Creature.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <queue>
//#include <iostream>
//using namespace std;

class GameController {
private:
	static Map* map;
	//static Entity* player;

	//static Entity* destination;
	static Entity* cursor;
	static Camera* camera;

	static vec2 mousePosition;
	static vec2 lastMouseClick;

	//static queue<vec2>* way;
	//static vec3 initialPosition;

	//static float speed;
	static Creature* creature;
	
public:
	//static Entity* getDestination() { return GameController::destination; };

	//static bool isInMotion() { return GameController::way && !GameController::way->empty(); };

	static void cursorPosCallback(GLFWwindow* window, double xPos, double yPos);
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void cursorEnterCallback(GLFWwindow* window, int entered);
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

	static void setMap(Map* map) { GameController::map = map; };
	//static void setPlayer(Entity* player) { GameController::player = player; };

	static void setCursor(Entity* cursor) { GameController::cursor = cursor; };
	static void setCamera(Camera* camera) { GameController::camera = camera; };
	//static void setDestination(Entity* destination) { GameController::destination = destination; };

	//static void update(float deltaTime);

	static void go(float coordX, float coordY);
	static void changeVisibility(int posX, int posY);
	static void setCreature(Creature* creature) { GameController::creature = creature; };

	static Camera* getCamera() { return GameController::camera; };
	static Map* getMap() { return GameController::map; };

};