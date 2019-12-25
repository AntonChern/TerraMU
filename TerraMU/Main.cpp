#define GLEW_STATIC
#define GLM_FORCE_RADIANS
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
#include "GameController.h"
#include "Entity.h"
#include "EntityFactory.h"
#include "Map.h"
#include "GoAction.h"
#include "WayHandler.h"
//#include "Moveable.h"
#include "AnimationPendulum.h"
#include "GuiElement.h"
#include "GuiRenderer.h"
#include "GuiElementFactory.h"
#include "Gui.h"
//#include "SlotArray.h"
//#include "Label.h"
//#include "Frame.h"
//#include "TextField.h"
//#include "GuiItemBuilder.h"
#include "Converter.h"
#include "Player.h"
#include "Monster.h"
#include "MobSpawner.h"
#include "MapObject.h"
#include "Item.h"
#include "Tile.h"
//#include "Cursor.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
using namespace std;
using namespace glm;

void initializeGLFW();
void initializeGLEW();

map<string, TexturedModel*> EntityFactory::models = {};
list<Entity*> EntityFactory::entities = {};
Loader* EntityFactory::loader = nullptr;
list<RawModel*> EntityFactory::rawModels = {};
//list<Item*> EntityFactory::items = {};

list<GuiElement*> GuiElementFactory::guis = {};
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
{HOUSE_0_FLOOR, new MapObject(new GoAction(), true, "house_0_floor.png", 32, 32)},
{GROUND, new MapObject(new GoAction(), true, "ground.png", 32, 32)},
{WATER, new MapObject(new Action(), false, "water.png", 32, 32)},
{STONE_WALL, new MapObject(new Action(), false, "stone_wall.png", 32, 32)},
{STONE_WALL_LEFT, new MapObject(new Action(), false, "stone_wall_left.png", 32, 32)},
{STONE_WALL_DOWN, new MapObject(new Action(), false, "stone_wall_down.png", 32, 32)},
{STONE_WALL_RIGHT, new MapObject(new Action(), false, "stone_wall_right.png", 32, 32)},
{STONE_WALL_UP, new MapObject(new Action(), false, "stone_wall_up.png", 32, 32)},
{STONE_WALL_LEFT_DOWN, new MapObject(new Action(), false, "stone_wall_left_down.png", 32, 32)},
{STONE_WALL_LEFT_RIGHT, new MapObject(new Action(), false, "stone_wall_left_right.png", 32, 32)},
{STONE_WALL_LEFT_UP, new MapObject(new Action(), false, "stone_wall_left_up.png", 32, 32)},
{STONE_WALL_RIGHT_DOWN, new MapObject(new Action(), false, "stone_wall_right_down.png", 32, 32)},
{STONE_WALL_UP_DOWN, new MapObject(new Action(), false, "stone_wall_up_down.png", 32, 32)},
{STONE_WALL_RIGHT_UP, new MapObject(new Action(), false, "stone_wall_right_up.png", 32, 32)},
{STONE_WALL_LEFT_RIGHT_UP, new MapObject(new Action(), false, "stone_wall_left_right_up.png", 32, 32)},
{STONE_WALL_LEFT_UP_DOWN, new MapObject(new Action(), false, "stone_wall_left_up_down.png", 32, 32)},
{STONE_WALL_LEFT_RIGHT_DOWN, new MapObject(new Action(), false, "stone_wall_left_right_down.png", 32, 32)},
{STONE_WALL_RIGHT_UP_DOWN, new MapObject(new Action(), false, "stone_wall_right_up_down.png", 32, 32)},
{STONE_WALL_LEFT_RIGHT_UP_DOWN, new MapObject(new Action(), false, "stone_wall_left_right_up_down.png", 32, 32)},
{MONUMENT_DRAGON, new MapObject(new Action(), false, "monument_dragon.png", 32, 64)},
{WATER_LILY_BEAUTIFUL, new MapObject(new Action(), false, "water_lily_beautiful.png", 32, 32)},
{WATER_LILY_LITTLE, new MapObject(new Action(), false, "water_lily_little.png", 32, 32)},
{WATER_LILY_BIG, new MapObject(new Action(), false, "water_lily_big.png", 32, 32)},
{FLOWER_RED, new MapObject(new GoAction(), true, "flower_red.png", 32, 32)},
{FLOWER_YELLOW, new MapObject(new GoAction(), true, "flower_yellow.png", 32, 32)},
{FLOWER_WHITE, new MapObject(new GoAction(), true, "flower_white.png", 32, 32)},
{GRASS_VOLUME, new MapObject(new GoAction(), true, "grass_volume.png", 32, 32)},
{STONE_VOLUME, new MapObject(new Action(), false, "stone_volume.png", 32, 32)},
{STUMP, new MapObject(new Action(), false, "stump.png", 32, 32)},
{FERN, new MapObject(new GoAction(), true, "fern.png", 32, 32)},
{WIDE_SIGN, new MapObject(new Action(), false, "wide_sign.png", 32, 32)},
{DOUBLE_SIGN, new MapObject(new Action(), false, "double_sign.png", 32, 32)},
{LOG, new MapObject(new Action(), false, "log.png", 32, 32)},
{EXTINCT_FIRE, new MapObject(new Action(), false, "extinct_fire.png", 32, 32)},
{TREE_LITTLE, new MapObject(new Action(), false, "tree_little.png", 32, 64)},
{TREE_DRIED, new MapObject(new Action(), false, "tree_dried.png", 32, 64)},
{FOUNTAIN_LEFT_BACK, new MapObject(new Action(), false, "fountain_left_back.png", 32, 64)},
{FOUNTAIN_LEFT_MIDDLE, new MapObject(new Action(), false, "fountain_left_middle.png", 32, 32)},
{FOUNTAIN_LEFT_FRONT, new MapObject(new Action(), false, "fountain_left_front.png", 32, 32)},
{FOUNTAIN_MIDDLELEFT_BACK, new MapObject(new Action(), false, "fountain_middleleft_back.png", 32, 64)},
{FOUNTAIN_MIDDLELEFT_MIDDLE, new MapObject(new Action(), false, "fountain_middleleft_middle.png", 32, 32)},
{FOUNTAIN_MIDDLELEFT_FRONT, new MapObject(new Action(), false, "fountain_middleleft_front.png", 32, 32)},
{FOUNTAIN_MIDDLERIGHT_BACK, new MapObject(new Action(), false, "fountain_middleright_back.png", 32, 64)},
{FOUNTAIN_MIDDLERIGHT_MIDDLE, new MapObject(new Action(), false, "fountain_middleright_middle.png", 32, 32)},
{FOUNTAIN_MIDDLERIGHT_FRONT, new MapObject(new Action(), false, "fountain_middleright_front.png", 32, 32)},
{FOUNTAIN_RIGHT_BACK, new MapObject(new Action(), false, "fountain_right_back.png", 32, 64)},
{FOUNTAIN_RIGHT_MIDDLE, new MapObject(new Action(), false, "fountain_right_middle.png", 32, 32)},
{FOUNTAIN_RIGHT_FRONT, new MapObject(new Action(), false, "fountain_right_front.png", 32, 32)},
{TENT_LEFT_BACK, new MapObject(new Action(), false, "tent_left_back.png", 32, 64)},
{TENT_LEFT_FRONT, new MapObject(new Action(), false, "tent_left_front.png", 32, 32)},
{TENT_MIDDLE_BACK, new MapObject(new Action(), false, "tent_middle_back.png", 32, 64)},
{TENT_MIDDLE_FRONT, new MapObject(new Action(), false, "tent_middle_front.png", 32, 32)},
{TENT_RIGHT_BACK, new MapObject(new Action(), false, "tent_right_back.png", 32, 64)},
{TENT_RIGHT_FRONT, new MapObject(new Action(), false, "tent_right_front.png", 32, 32)}
};

//map<int, Item*> items = {
//	{0, new Item("apple.png", "Apple")}
//};

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
//list<Action*> GameController::actions = {};

int main() {
	initializeGLFW();
	Display *display = new Display();
	initializeGLEW();

	Loader *loader = new Loader();
	EntityFactory::setLoader(loader);
	GuiElementFactory::setLoader(loader);

	int size = 128;
	Map* map = new Map("Lorenzia_128_1.txt", vec3(0.0f), 0.0f, 0.0f, 0.0f, 0.25f * size);
	Entity* background = EntityFactory::createEntity("forest.png", vec3(0.0f, 0.0f, -1.0f), 0.0f, 0.0f, 0.0f, vec3(map->getScale().x * 4608 / 4096, map->getScale().y * 4416 / 4096, map->getScale().z));

	float x = 0.125f * (1 - size);
	float y = 0.125f * (size - 1);

	Entity* destination = EntityFactory::createEntity("destination.png",
		new AnimationPendulum(INFINITY, 5 * 0.015f, vec2(7.0f / 8.0f, 0.0f), vec2(1.0f / 8.0f, 1.0f), 1.0f / 8.0f),
		vec3(0.0f, 0.0f, 0.0004f), 0.0f, 0.0f, 0.0f, 0.45f);

	Camera* camera = new Camera();

	Entity *playerAvatar = EntityFactory::createEntity("darkWizard.png",
		new AnimationPendulum(INFINITY, 6 * 0.015f, vec2(1.0f / 3.0f, 0.0f), vec2(1.0f / 3.0f, 0.25f), 1.0f / 3.0f),
		vec3(0.0f, 0.0f, 0.065f), 0.0f, 0.0f, 0.0f, 0.25f);
	Player* player = new Player(playerAvatar, 1.0f, /*(float)map->getScale().x / map->getColumns() * 3*/ INFINITY, 100, destination);

	camera->setPosition(playerAvatar->getPosition().x, playerAvatar->getPosition().y, 1);

	GameController::setMap(map);
	GameController::setPlayer(player);
	GameController::setCamera(camera);
	
	vec2 ghostBossSpawnerLocation = Converter::fromMapToOpenGL(vec2(119.0f + 0.5f, 20.0f));
	MobSpawner* ghostBossSpawner = new MobSpawner("ghostBoss.png",
		INFINITY, 6 * 0.015f, vec2(1.0f / 3.0f, 0.0f), vec2(1.0f / 3.0f, 0.25f), 1.0f / 3.0f,
		vec3(ghostBossSpawnerLocation.x, ghostBossSpawnerLocation.y, Converter::fromOpenGLToMap(vec2(ghostBossSpawnerLocation.y)).y * 0.001f + 0.001f), 0.0f, 0.0f, 0.0f, 0.25f,
		0.8f, false, (float)map->getScale().x / (float)map->getColumns() * 6, 250, 0.7f, 100,
		20, 1);

	vec2 ghostSpawnerLocation = Converter::fromMapToOpenGL(vec2(117.0f + 0.5f, 20.0f));
	MobSpawner* ghostSpawner = new MobSpawner("ghost.png",
		INFINITY, 6 * 0.015f, vec2(1.0f / 3.0f, 0.0f), vec2(1.0f / 3.0f, 0.25f), 1.0f / 3.0f,
		vec3(ghostSpawnerLocation.x, ghostSpawnerLocation.y, Converter::fromOpenGLToMap(vec2(ghostSpawnerLocation.y)).y * 0.001f + 0.001f), 0.0f, 0.0f, 0.0f, 0.25f,
		0.75f, false, (float)map->getScale().x / (float)map->getColumns() * 4.5, 100, 0.7f, 100,
		10, 3);

	vec2 skeletonSpawnerLocation = Converter::fromMapToOpenGL(vec2(95.0f + 0.5f, 94.0f));
	MobSpawner* skeletonSpawner = new MobSpawner("skeleton.png",
		INFINITY, 6 * 0.015f, vec2(1.0f / 3.0f, 0.0f), vec2(1.0f / 3.0f, 0.25f), 1.0f / 3.0f,
		vec3(skeletonSpawnerLocation.x, skeletonSpawnerLocation.y, Converter::fromOpenGLToMap(vec2(skeletonSpawnerLocation.y)).y * 0.001f + 0.001f), 0.0f, 0.0f, 0.0f, 0.25f,
		0.7f, false, (float)map->getScale().x / (float)map->getColumns() * 5, 100, 0.7f, 100,
		5, 2);

	vec2 goblinSpawnerLocation = Converter::fromMapToOpenGL(vec2(0.0f + 0.5f, 77.0f));
	MobSpawner* goblinSpawner = new MobSpawner("goblin.png",
		INFINITY, 6 * 0.015f, vec2(1.0f / 3.0f, 0.0f), vec2(1.0f / 3.0f, 0.25f), 1.0f / 3.0f,
		vec3(goblinSpawnerLocation.x, goblinSpawnerLocation.y, Converter::fromOpenGLToMap(vec2(goblinSpawnerLocation.y)).y * 0.001f + 0.001f), 0.0f, 0.0f, 0.0f, 0.25f,
		0.8f, false, (float)map->getScale().x / map->getColumns() * 3.5, 100, 0.7f, 100,
		10, 3);

	vec2 batSpawnerLocation = Converter::fromMapToOpenGL(vec2(69.0f + 0.5f, 93.0f));
	MobSpawner* batSpawner = new MobSpawner("bat.png",
		INFINITY, 6 * 0.015f, vec2(1.0f / 3.0f, 0.0f), vec2(1.0f / 3.0f, 0.25f), 1.0f / 3.0f,
		vec3(batSpawnerLocation.x, batSpawnerLocation.y, Converter::fromOpenGLToMap(vec2(batSpawnerLocation.y)).y * 0.001f + 0.001f), 0.0f, 0.0f, 0.0f, 0.25f,
		0.6f, true, (float)map->getScale().x / map->getColumns() * 3, 50, 0.7f, 100,
		15, 5);

	map->addMobSpawner(ghostBossSpawner);
	map->addMobSpawner(ghostSpawner);
	map->addMobSpawner(skeletonSpawner);
	map->addMobSpawner(goblinSpawner);
	map->addMobSpawner(batSpawner);

	WayHandler::initialize();

	/*GLFWimage image;
	int width;
	int height;
	unsigned char* pixels = SOIL_load_image("cursor.png", &width, &height, 0, SOIL_LOAD_RGBA);

	
	image.height = width;
	image.width = width;
	image.pixels = pixels;

	GLFWcursor* mouse = glfwCreateCursor(&image, 0, 0);
	glfwSetCursor(display->getWindow(), mouse);

	SOIL_free_image_data(pixels);*/


	//glfwSetInputMode(display->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(display->getWindow(), GameController::cursorPosCallback);
	glfwSetMouseButtonCallback(display->getWindow(), GameController::mouseButtonCallback);
	glfwSetCursorEnterCallback(display->getWindow(), GameController::cursorEnterCallback);
	glfwSetKeyCallback(display->getWindow(), GameController::keyCallback);

	Gui* gui = new Gui(display->getWindow());
	GameController::setGui(gui);

	float lastTime = glfwGetTime();
	MasterRenderer* renderer = new MasterRenderer();
	GuiRenderer* guiRenderer = new GuiRenderer();

	map->addItem(new Item("scroll.png", "Scroll"), 69, 69);
	map->addItem(new Item("book.png", "Book"), 67, 67);
	map->addItem(new Item("apple.png", "Apple"), 67, 63);

	while (!display->isCloseRequested()) {

		vec2 playerPosition = Converter::fromOpenGLToMap(vec2(player->getAvatar()->getPosition().x, player->getAvatar()->getPosition().y));
		renderer->processEntities(map->getRectangleArea(playerPosition.x, playerPosition.y, 19, 19));
		renderer->processEntity(background);

		for (MobSpawner* spawner : *map->getSpawners()) {
			for (Monster* mob : *spawner->getMobs()) {
				renderer->processEntity(mob->getAvatar());
			}
		}

		if (!player->containsTask() && player->isInMotion()) {
			renderer->processEntity(player->getDestination());
		}

		renderer->processEntity(player->getAvatar());

		renderer->render(camera);
		guiRenderer->render(map->getTitles(playerPosition.x, playerPosition.y, 19, 19));
		guiRenderer->render(gui->getGuiElements());

		float currentTime = glfwGetTime();

		GameController::update(currentTime - lastTime);

		lastTime = currentTime;

		glfwPollEvents();
		display->update();
	}

	WayHandler::deinitialize();

	renderer->cleanUp();
	guiRenderer->cleanUp();
	loader->cleanUp();
	delete guiRenderer;
	delete renderer;
	delete loader;

	delete gui;

	GuiElementFactory::cleanUp();
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