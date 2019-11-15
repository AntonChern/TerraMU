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
#include "GuiElement.h"
#include "GuiRenderer.h"
#include "GuiElementFactory.h"
#include "Gui.h"
#include "SlotArray.h"
#include "Label.h"
#include "Frame.h"
#include "TextField.h"
#include "GuiItemBuilder.h"
#include "Converter.h"
#include "Player.h"
#include "Monster.h"
#include "MobSpawner.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
using namespace std;
using namespace glm;

void initializeGLFW();
void initializeGLEW();

map<string, TexturedModel*>* EntityFactory::models = new map<string, TexturedModel*>();
list<Entity*>* EntityFactory::entities = new list<Entity*>();
Loader* EntityFactory::loader = nullptr;
list<RawModel*>* EntityFactory::rawModels = new list<RawModel*>();

list<GuiElement*>* GuiElementFactory::guis = new list<GuiElement*>();
Loader* GuiElementFactory::loader = nullptr;

map<Tile, MapObject*> Map::mapObjects = {
{GRASS_0, new MapObject(new GoAction(), true, "grass_0.png", 32, 32)},
{GRASS_1, new MapObject(new GoAction(), true, "grass_1.png", 32, 32)},
{GRASS_2, new MapObject(new GoAction(), true, "grass_2.png", 32, 32)},
{STONE_0, new MapObject(new GoAction(), true, "stone_0.png", 32, 32)},
{STONE_1, new MapObject(new GoAction(), true, "stone_1.png", 32, 32)},
{STONE_2, new MapObject(new GoAction(), true, "stone_2.png", 32, 32)},
{STONE_3, new MapObject(new GoAction(), true, "stone_3.png", 32, 32)},
{STONE_4, new MapObject(new GoAction(), true, "stone_4.png", 32, 32)},
{MONUMENT, new MapObject(new Action(), false, "monument.png", 32, 64)},
{TREE_SIZE_0, new MapObject(new Action(), false, "tree_size_0.png", 64, 72)},
{TREE_SIZE_1, new MapObject(new Action(), false, "tree_size_1.png", 96, 112)},
{TREE_SIZE_2, new MapObject(new Action(), false, "tree_size_2.png", 170, 187)},
{TREE_SIZE_3, new MapObject(new Action(), false, "tree_size_3.png", 271, 288)},
{HOUSE_0_MIDDLE_FRONT_WALL, new MapObject(new Action(), false, "house_0_middle_front_wall.png", 32, 96)},
{HOUSE_0_LEFT_FRONT_WALL, new MapObject(new Action(), false, "house_0_left_front_wall.png", 93, 96)},
{HOUSE_0_RIGHT_FRONT_WALL, new MapObject(new Action(), false, "house_0_right_front_wall.png", 93, 96)},
{HOUSE_0_DOOR, new MapObject(new Action(), false, "house_0_door.png", 32, 96)},
{HOUSE_0_WINDOW, new MapObject(new Action(), false, "house_0_window.png", 32, 96)},
{HOUSE_0_LEFT_MIDDLE_WALL, new MapObject(new Action(), false, "house_0_left_middle_wall.png", 93, 96)},
{HOUSE_0_RIGHT_MIDDLE_WALL, new MapObject(new Action(), false, "house_0_right_middle_wall.png", 93, 96)},
{HOUSE_0_LEFT_BACK_WALL, new MapObject(new Action(), false, "house_0_left_back_wall.png", 92, 110)},
{HOUSE_0_RIGHT_BACK_WALL, new MapObject(new Action(), false, "house_0_right_back_wall.png", 93, 110)},
{HOUSE_0_MIDDLE_BACK_WALL, new MapObject(new Action(), false, "house_0_middle_back_wall.png", 32, 100)},
{HOUSE_0_MIDDLE_WALL, new MapObject(new Action(), false, "house_0_middle_wall.png", 32, 96)},
{HOUSE_0_FLOOR, new MapObject(new GoAction(), true, "house_0_floor.png", 32, 32)}
};

float WayHandler::radius = 0.0f;
bool** WayHandler::wayMap = nullptr;
WayHandler::Point*** WayHandler::map = nullptr;
WayHandler::Point* WayHandler::end = nullptr;
WayHandler::Point* WayHandler::start = nullptr;
list<WayHandler::Point*> WayHandler::wayAStar = {};
list<vec2>* WayHandler::resultWay = nullptr;

Map* GameController::map = nullptr;
Player* GameController::player = nullptr;
Camera* GameController::camera = nullptr;
vec2 GameController::mousePosition = vec2(-1.0f);
vec2 GameController::lastMouseClick = vec2(0.0f);
Gui* GameController::gui = nullptr;

int main() {
	initializeGLFW();
	Display *display = new Display();
	initializeGLEW();

	Loader *loader = new Loader();
	EntityFactory::setLoader(loader);
	GuiElementFactory::setLoader(loader);

	int size = 64;
	Map* map = new Map("tarkan.txt", vec3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 0.0f, 0.25f * size);

	float x = 0.125f * (1 - size);
	float y = 0.125f * (size - 1);

	Entity* destination = EntityFactory::createEntity("destination.png",
		new AnimationPendulum(INFINITY, 5 * 0.015f, vec2(7.0f / 8.0f, 0.0f), vec2(1.0f / 8.0f, 1.0f), 1.0f / 8.0f),
		vec3(0.0f, 0.0f, 0.0004f), 0.0f, 0.0f, 0.0f, 0.45f);

	Camera* camera = new Camera();
	camera->setPosition(x, y, 1.0f);

	Entity *playerAvatar = EntityFactory::createEntity("darkWizard.png",
		new AnimationPendulum(INFINITY, 6 * 0.015f, vec2(1.0f / 3.0f, 0.0f), vec2(1.0f / 3.0f, 0.25f), 1.0f / 3.0f),
		vec3(x, y, 0.0015f), 0.0f, 0.0f, 0.0f, 0.25f);
	Player* player = new Player(playerAvatar, 1.0f, /*(float)map->getScale().x / map->getColumns() * 3*/ INFINITY, destination);

	GameController::setMap(map);
	GameController::setPlayer(player);
	GameController::setCamera(camera);
	
	vec2 skeletonSpawnerLocation = Converter::fromMapToOpenGL(vec2(12.0f + 0.5f, 2.0f));
	MobSpawner* skeletonSpawner = new MobSpawner("skeleton.png",
		INFINITY, 6 * 0.015f, vec2(1.0f / 3.0f, 0.0f), vec2(1.0f / 3.0f, 0.25f), 1.0f / 3.0f,
		vec3(skeletonSpawnerLocation.x, skeletonSpawnerLocation.y, Converter::fromOpenGLToMap(vec2(skeletonSpawnerLocation.y)).y * 0.001f + 0.0015f), 0.0f, 0.0f, 0.0f, 0.25f,
		0.6f, false, (float)map->getScale().x / (float)map->getColumns() * 3, 0.7f, 100,
		500, 1);

	vec2 goblinSpawnerLocation = Converter::fromMapToOpenGL(vec2(4.0f + 0.5f, 0.0f));
	MobSpawner* goblinSpawner = new MobSpawner("goblin.png",
		INFINITY, 6 * 0.015f, vec2(1.0f / 3.0f, 0.0f), vec2(1.0f / 3.0f, 0.25f), 1.0f / 3.0f,
		vec3(goblinSpawnerLocation.x, goblinSpawnerLocation.y, Converter::fromOpenGLToMap(vec2(goblinSpawnerLocation.y)).y * 0.001f + 0.0015f), 0.0f, 0.0f, 0.0f, 0.25f,
		0.75f, false, (float)map->getScale().x / map->getColumns() * 5, 0.7f, 100,
		100, 3);

	vec2 batSpawnerLocation = Converter::fromMapToOpenGL(vec2(7.0f + 0.5f, 8.0f));
	MobSpawner* batSpawner = new MobSpawner("bat.png",
		INFINITY, 6 * 0.015f, vec2(1.0f / 3.0f, 0.0f), vec2(1.0f / 3.0f, 0.25f), 1.0f / 3.0f,
		vec3(batSpawnerLocation.x, batSpawnerLocation.y, Converter::fromOpenGLToMap(vec2(batSpawnerLocation.y)).y * 0.001f + 0.0015f), 0.0f, 0.0f, 0.0f, 0.25f,
		0.6f, true, (float)map->getScale().x / map->getColumns() * 3, 0.7f, 100,
		375, 3);


	//map->addMobSpawner(skeletonSpawner);
	map->addMobSpawner(goblinSpawner);
	//map->addMobSpawner(batSpawner);
	
	glfwSetInputMode(display->getWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetCursorPosCallback(display->getWindow(), GameController::cursorPosCallback);
	glfwSetMouseButtonCallback(display->getWindow(), GameController::mouseButtonCallback);
	glfwSetCursorEnterCallback(display->getWindow(), GameController::cursorEnterCallback);
	glfwSetKeyCallback(display->getWindow(), GameController::keyCallback);

	Gui* gui = new Gui();
	GameController::setGui(gui);

	float lastTime = glfwGetTime();
	MasterRenderer* renderer = new MasterRenderer();
	GuiRenderer* guiRenderer = new GuiRenderer();

	while (!display->isCloseRequested()) {
    vec2 playerPosition = Converter::fromOpenGLToMap(vec2(player->getAvatar()->getPosition().x, player->getAvatar()->getPosition().y));
		list<Entity*> mapObjects = map->getRectangleArea(playerPosition.x, playerPosition.y, 19, 19);

		renderer->processEntities(mapObjects);

		renderer->processEntity(player->getAvatar());

		for (MobSpawner* spawner : *map->getSpawners()) {
			for (Monster* mob : *spawner->getMobs()) {
				renderer->processEntity(mob->getAvatar());
			}
		}

		if (player->isInMotion()) {
			renderer->processEntity(player->getDestination());
		}

		renderer->render(camera);
		guiRenderer->render(gui->getGuiElements());

		float currentTime = glfwGetTime();

		player->update(currentTime - lastTime);

		for (MobSpawner* spawner : *map->getSpawners()) {
			spawner->update();
			for (Monster* mob : *spawner->getMobs()) {
				mob->update(currentTime - lastTime);
			}
		}
		map->nullMobMap();

		lastTime = currentTime;

		glfwPollEvents();
		display->update();

		EntityFactory::cleanEntities(mapObjects);
	}

	renderer->cleanUp();
	guiRenderer->cleanUp();
	loader->cleanUp();
	delete guiRenderer;
	delete renderer;
	delete loader;

	EntityFactory::cleanUp();
	GuiElementFactory::cleanUp();

	delete camera;

	delete gui;

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