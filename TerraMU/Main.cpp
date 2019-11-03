#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>
#include "Camera.h"
#include "StaticShader.h"
#include "StreamShader.h"
#include "Display.h"
#include "MasterRenderer.h"
#include "Loader.h"
#include "ModelTexture.h"
#include "TexturedModel.h"
//#include "GameController.h"
#include "Entity.h"
#include "EntityFactory.h"
#include "Map.h"
#include "GoAction.h"
#include "WayHandler.h"
#include "Moveable.h"
#include "AnimationPendulum.h"
#include "Converter.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
using namespace std;
using namespace glm;

vec2 mousePosition;

static void cursorPositionCallback(GLFWwindow *window, double xPos, double yPos) {
	float aspect = (float)Display::getWidth() / (float)Display::getHeight();
	mousePosition = vec2(aspect * (2 * (float)xPos/Display::getWidth() - 1.0f), -2 * (float)yPos/Display::getHeight() + 1.0f);
	//cout << mousePosition.x << " : " << mousePosition.y << endl;
}

void initializeGLFW();
void initializeGLEW();

map<string, TexturedModel*>* EntityFactory::models = new map<string, TexturedModel*>();
list<Entity*>* EntityFactory::entities = new list<Entity*>();
Loader* EntityFactory::loader = nullptr;

map<Tile, MapObject*> Map::mapObjects = {
{GRASS_0, new MapObject(new GoAction(), true, true, "grass_0.png", 32, 32)},
{GRASS_1, new MapObject(new GoAction(), true, true, "grass_1.png", 32, 32)},
{GRASS_2, new MapObject(new GoAction(), true, true, "grass_2.png", 32, 32)},
{STONE_0, new MapObject(new GoAction(), true, true, "stone_0.png", 32, 32)},
{STONE_1, new MapObject(new GoAction(), true, true, "stone_1.png", 32, 32)},
{STONE_2, new MapObject(new GoAction(), true, true, "stone_2.png", 32, 32)},
{STONE_3, new MapObject(new GoAction(), true, true, "stone_3.png", 32, 32)},
{STONE_4, new MapObject(new GoAction(), true, true, "stone_4.png", 32, 32)},
{MONUMENT, new MapObject(new Action(), false, true, "monument.png", 32, 64)},
{TREE_SIZE_0, new MapObject(new Action(), false, true, "tree_size_0.png", 64, 72)},
{TREE_SIZE_1, new MapObject(new Action(), false, true, "tree_size_1.png", 96, 112)},
{TREE_SIZE_2, new MapObject(new Action(), false, true, "tree_size_2.png", 170, 187)},
{TREE_SIZE_3, new MapObject(new Action(), false, true, "tree_size_3.png", 271, 288)}
};

Map* Converter::map = nullptr;
Camera* Converter::camera = nullptr;

Map* GameController::map = nullptr;
Entity* GameController::player = nullptr;
Entity* GameController::cursor = nullptr;
Camera* GameController::camera = nullptr;
vec2 GameController::mousePosition = vec2(0.0f);
vec2 GameController::lastMouseClick = vec2(0.0f);
WayHandler* GameController::handler = new WayHandler();
float GameController::speed = 1.0f;
queue<vec2>* GameController::way = nullptr;
vec3 GameController::initialPosition = vec3(0);
Entity* GameController::destination = nullptr;

int main() {
	initializeGLFW();
	Display *display = new Display();
	initializeGLEW();

	Loader *loader = new Loader();
	EntityFactory::setLoader(loader);

	int size = 64;
	Map* map = new Map("tarkan.txt", vec3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 0.0f, 0.25f * size);

	Entity* cursor = EntityFactory::createEntity("cursor.png", vec3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 0.0f, 0.4f);

	float x = 0.125f * (1 - size);
	float y = 0.125f * (size - 1);

	Entity *player = EntityFactory::createEntity("magicGladiator.png",
		new AnimationPendulum(INFINITY, 6, vec2(1.0f / 3.0f, 0.0f), vec2(1.0f / 3.0f, 0.25f), 1.0f / 3.0f),
		vec3(x, y, 0.0015f), 0.0f, 0.0f, 0.0f, 0.25f);

	Entity* destination = EntityFactory::createEntity("destination.png",
		new AnimationPendulum(INFINITY, 5, vec2(7.0f / 8.0f, 0.0f), vec2(1.0f / 8.0f, 1.0f), 1.0f / 8.0f),
		vec3(0.0f, 0.0f, 0.0004f), 0.0f, 0.0f, 0.0f, 0.45f);

	Camera* camera = new Camera();
	camera->setPosition(x, y, 1.0f);
	
	//glfwSetInputMode(display->getWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetCursorPosCallback(display->getWindow(), GameController::cursorPosCallback);
	glfwSetMouseButtonCallback(display->getWindow(), GameController::mouseButtonCallback);
	glfwSetCursorEnterCallback(display->getWindow(), GameController::cursorEnterCallback);
	glfwSetKeyCallback(display->getWindow(), GameController::keyCallback);

	Converter::setMap(map);
	Converter::setCamera(camera);
	
	GameController::setMap(map);
	GameController::setPlayer(player);
	GameController::setCursor(cursor);
	GameController::setCamera(camera);
	GameController::setDestination(destination);
	float lastTime = glfwGetTime();

	MasterRenderer* renderer = new MasterRenderer();
	while (!display->isCloseRequested()) {
		vec2 playerPosition = Converter::fromOpenGLToMap(vec2(player->getPosition().x, player->getPosition().y));
		renderer->processEntities(map->getRectangleArea(playerPosition.x, playerPosition.y, 19, 19));

		renderer->processEntity(player);

		Entity* destination = GameController::getDestination();
		if (GameController::isInMotion()) {
			renderer->processEntity(destination);
		}

		renderer->render(camera);

		float currentTime = glfwGetTime();
		GameController::update(currentTime - lastTime);
		lastTime = currentTime;

		glfwPollEvents();
		display->update();
	}

	renderer->cleanUp();
	loader->cleanUp();
	delete renderer;
	delete loader;

	EntityFactory::cleanUp();

	delete camera;

	delete display;

	glfwTerminate();
	return 0;
}

void initializeGLFW() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

void initializeGLEW() {
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		cout << "Failed to initialize GLEW" << endl;
		exit(-1);
	}
}