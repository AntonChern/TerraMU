#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>
#include "StaticShader.h"
#include "StreamShader.h"
#include "Display.h"
#include "Renderer.h"
#include "Loader.h"
#include "ModelTexture.h"
#include "TexturedModel.h"
#include "Camera.h"
//#include "GameController.h"
#include "Entity.h"
#include "EntityBuilder.h"
#include "Map.h"
#include "GoAction.h"
#include "WayHandler.h"
#include "Moveable.h"
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

map<string, Entity*>* EntityBuilder::entities = new map<string, Entity*>();
list<TexturedModel*>* EntityBuilder::models = new list<TexturedModel*>();

map<Tile, MapObject*> Map::mapObjects = {
	{GRASS_0, new MapObject(new GoAction(), true, true, "grass_0.png", 32, 32)},
	{GRASS_1, new MapObject(new GoAction(), true, true, "grass_1.png", 32, 32)},
	{GRASS_2, new MapObject(new GoAction(), true, true, "grass_2.png", 32, 32)},
	{STONE_0, new MapObject(new GoAction(), true, true, "stone_0.png", 32, 32)},
	{STONE_1, new MapObject(new GoAction(), true, true, "stone_1.png", 32, 32)},
	{STONE_2, new MapObject(new GoAction(), true, true, "stone_2.png", 32, 32)},
	{STONE_3, new MapObject(new GoAction(), true, true, "stone_3.png", 32, 32)},
	{STONE_4, new MapObject(new GoAction(), true, true, "stone_4.png", 32, 32)},
	{MONUMENT, new MapObject(new Action(), false, true, "monument.png", 32, 64)}
};

Map* GameController::map = nullptr;
Entity* GameController::player = nullptr;
Entity* GameController::cursor = nullptr;
Camera* GameController::camera = nullptr;
vec2 GameController::mouseOffset = vec2(0.0f);
vec2 GameController::mousePosition = vec2(0.0f);
vec2 GameController::lastMouseClick = vec2(0.0f);
float GameController::lastTime = 0.0f;
WayHandler* GameController::handler = new WayHandler();
float GameController::speed = 1.0f;
queue<vec2>* GameController::way = nullptr;
vec3 GameController::initialPosition = vec3(0);
vec2 GameController::textureTranslate = vec2(1.0f / 3.0f, 0.0f);
vec2 GameController::textureStep = vec2(1.0f / 3.0f, 0.0f);
int GameController::textureTime = 6;

int main() {
	initializeGLFW();
	Display *display = new Display();
	initializeGLEW();

	Loader *loader = new Loader();
	StreamShader *shader = new StreamShader();
	Renderer *renderer = new Renderer(shader);

	//Entity* map = EntityBuilder::createEntity(loader, "map.png", vec3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 0.0f, 25.0f);

	int size = 9;
	Tile** base = new Tile*[size];
	for (int i = 0; i < size; i++) {
		base[i] = new Tile[size];
	}
	Tile** hat = new Tile * [size];
	for (int i = 0; i < size; i++) {
		hat[i] = new Tile[size];
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			base[i][j] = GRASS_0;
		}
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			hat[i][j] = EMPTY;
		}
	}

	base[3][3] = STONE_4;
	base[3][4] = STONE_4;
	base[3][5] = STONE_4;
	base[4][3] = STONE_4;
	base[4][4] = STONE_4;
	base[4][5] = STONE_4;
	base[5][3] = STONE_4;
	base[5][4] = STONE_4;
	base[5][5] = STONE_4;

	base[2][3] = STONE_2;
	base[2][4] = STONE_2;
	base[2][5] = STONE_2;
	base[3][2] = STONE_2;
	base[3][6] = STONE_2;
	base[4][2] = STONE_2;
	base[4][6] = STONE_2;
	base[5][2] = STONE_2;
	base[5][6] = STONE_2;
	base[6][3] = STONE_2;
	base[6][4] = STONE_2;
	base[6][5] = STONE_2;

	hat[1][3] = MONUMENT;
	hat[1][4] = MONUMENT;
	hat[2][2] = MONUMENT;
	hat[2][6] = MONUMENT;
	hat[4][0] = MONUMENT;
	hat[4][1] = MONUMENT;
	hat[6][2] = MONUMENT;
	hat[6][6] = MONUMENT;
	hat[7][3] = MONUMENT;
	hat[7][4] = MONUMENT;
	hat[7][5] = MONUMENT;
	hat[8][5] = MONUMENT;

	//Map* map = new Map("lorencia.txt", vec3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 0.0f, 0.25f * 255);
	Map* map = new Map(size, size, base, hat, vec3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 0.0f, 0.25f * size);

	Entity* cursor = EntityBuilder::createEntity(loader, "cursor.png", vec3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 0.0f, 0.4f);

	Entity *player = EntityBuilder::createEntity(loader, "magicGladiator.png", vec3(0.125f * (1 - size), 0.125f * (size - 1), 0.0f), 0.0f, 0.0f, 0.0f, 0.25f);
	mat3 texture(1.0f);
	texture = translate(texture, vec2(1.0f / 3.0f, 0.0f));
	texture = scale(texture, vec2(1.0f / 3.0f, 0.25f));
	player->setTextureMatrix(texture);

	Camera *camera = new Camera();
	camera->setPosition(0.125f * (1 - size), 0.125f * (size - 1), 1.0f);

	//KeyboardController *controller = new KeyboardController(camera, display);
	
	//glfwSetInputMode(display->getWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetCursorPosCallback(display->getWindow(), GameController::cursorPosCallback);
	glfwSetMouseButtonCallback(display->getWindow(), GameController::mouseButtonCallback);
	glfwSetCursorEnterCallback(display->getWindow(), GameController::cursorEnterCallback);
	glfwSetKeyCallback(display->getWindow(), GameController::keyCallback);

	GameController::setMap(map);
	GameController::setPlayer(player);
	GameController::setCursor(cursor);
	GameController::setCamera(camera);

	GameController::initialize();

	float lastTime = glfwGetTime();

	vec2 textureTranslate;
	while (!display->isCloseRequested()) {
		//player->increaseRotationY(50.0f);
		//entity->increasePosition(0.0f, 0.0f, -0.01f);
		//controller->process();
	
		renderer->prepare();

		vec4 direction(0.0f);
		if (glfwGetKey(display->getWindow(), GLFW_KEY_UP) == GLFW_PRESS) {
			direction += vec4(0.0f, -1.0f, 0.0f, 0.0f);
		}
		if (glfwGetKey(display->getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS) {
			direction += vec4(0.0f, 1.0f, 0.0f, 0.0f);
		}
		if (glfwGetKey(display->getWindow(), GLFW_KEY_LEFT) == GLFW_PRESS) {
			direction += vec4(1.0f, 0.0f, 0.0f, 0.0f);
		}
		if (glfwGetKey(display->getWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS) {
			direction += vec4(-1.0f, 0.0f, 0.0f, 0.0f);
		}

		if (direction != vec4(0.0f)) {
			direction = normalize(direction);
			textureTranslate += vec2(1.0f/3.0f, 0.0f);
			textureTranslate = vec2(textureTranslate.x > 1.0f ? textureTranslate.x - 1.0f : textureTranslate.x, textureTranslate.y);
		}
		else {
			textureTranslate = vec2(0.0f, textureTranslate.y);
		}

		vec4 move = scale(mat4(1.0f), vec3(0.02f)) * direction;
		//map->increasePosition(move.x, move.y, move.z);
		map->increasePosition(move.x, move.y, move.z);
		/*camera->increasePosition(-move.x, -move.y, -move.z);
		player->increasePosition(-move.x, -move.y, -move.z);
		cursor->increasePosition(-move.x, -move.y, -move.z);*/


		if (direction.x < 0) {
			textureTranslate = vec2(textureTranslate.x, 0.5f);
		}
		if (direction.x > 0) {
			textureTranslate = vec2(textureTranslate.x, 0.25f);
		}
		if (direction.x == 0) {
		    if (direction.y < 0) {
			    textureTranslate = vec2(textureTranslate.x, 0.75f);
		    }
		    if (direction.y > 0) {
		    	textureTranslate = vec2(textureTranslate.x, 0.0f);
		    }
		}

		mat3 texture(1.0f);
		texture = translate(texture, vec2(1.0f / 3.0f, 0.0f) + textureTranslate);
		texture = scale(texture, vec2(1.0f / 3.0f, 0.25f));
		//player->setTextureMatrix(texture);


		shader->start();
		shader->loadViewMatrix(camera);
		map->drawRectangleArea(renderer, loader, shader,
			map->getColumns() * (map->getScale().x + player->getPosition().x) / (2 * map->getScale().x),
			map->getRows() * (map->getScale().y - player->getPosition().y) / (2 * map->getScale().y), 16, 10);
		//renderer->render(map, shader);
		renderer->render(player, shader);
		//renderer->render(cursor, shader);
		glfwPollEvents();
		shader->stop();

		float currentTime = glfwGetTime();
		GameController::update(currentTime - lastTime);
		lastTime = currentTime;
		display->update();
	}

	shader->cleanUp();
	loader->cleanUp();
	delete shader;
	delete renderer;
	delete loader;

	EntityBuilder::cleanUp();

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