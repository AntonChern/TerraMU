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

map<Tile, MapObject*> Map::mapObjects = {
	{GRASS_0, new MapObject(new GoAction(), true, "grass_0.png", 32, 32)},
	{GRASS_1, new MapObject(new GoAction(), true, "grass_1.png", 32, 32)},
	{GRASS_2, new MapObject(new GoAction(), true, "grass_2.png", 32, 32)},
	{STONE_0, new MapObject(new GoAction(), true, "stone_0.png", 32, 32)},
	{STONE_1, new MapObject(new GoAction(), true, "stone_1.png", 32, 32)},
	{STONE_2, new MapObject(new GoAction(), true, "stone_2.png", 32, 32)},
	{STONE_3, new MapObject(new GoAction(), true, "stone_3.png", 32, 32)},
	{STONE_4, new MapObject(new GoAction(), true, "stone_4.png", 32, 32)},
	{MONUMENT, new MapObject(new Action(), true, "monument.png", 32, 64)}
};

Map* GameController::map = nullptr;
Entity* GameController::player = nullptr;
vec2 GameController::mousePosition = vec2(0.0f);
vec2 GameController::lastMouseClick = vec2(0.0f);

int main() {
	initializeGLFW();
	Display *display = new Display();
	initializeGLEW();

	Loader *loader = new Loader();
	StreamShader *shader = new StreamShader();
	Renderer *renderer = new Renderer(shader);

	//Entity* map = EntityBuilder::createEntity(loader, "map.png", vec3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 0.0f, 25.0f);

	int size = 4;
	Tile** base = new Tile*[size];
	for (int i = 0; i < size; i++) {
		base[i] = new Tile[size];
	}
	Tile** hat = new Tile * [size];
	for (int i = 0; i < size; i++) {
		hat[i] = new Tile[size];
	}

	base[0][0] = GRASS_0;
	base[0][1] = GRASS_0;
	base[0][2] = STONE_0;
	base[0][3] = STONE_0;
	base[1][0] = STONE_0;
	base[1][1] = STONE_0;
	base[1][2] = STONE_0;
	base[1][3] = STONE_0;
	base[2][0] = GRASS_0;
	base[2][1] = GRASS_0;
	base[2][2] = STONE_0;
	base[2][3] = STONE_0;
	base[3][0] = STONE_0;
	base[3][1] = STONE_0;
	base[3][2] = STONE_0;
	base[3][3] = STONE_0;


	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			hat[i][j] = EMPTY;
		}
	}
	hat[0][3] = MONUMENT;

	Map* map = new Map("lorencia.txt", vec3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 0.0f, 0.25f * 128);
	//Map* map = new Map(size, size, base, hat, vec3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 0.0f, 0.25f * 2);

	Entity* cursor = EntityBuilder::createEntity(loader, "cursor.png", vec3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 0.0f, 0.2f);

	Entity *player = EntityBuilder::createEntity(loader, "magicGladiator.png", vec3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 0.0f, 0.25f);

	Camera *camera = new Camera();
	camera->setPosition(0.0f, 0.0f, 1.0f);

	//KeyboardController *controller = new KeyboardController(camera, display);
	
	glfwSetInputMode(display->getWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetCursorPosCallback(display->getWindow(), GameController::cursorPosCallback);
	glfwSetMouseButtonCallback(display->getWindow(), GameController::mouseButtonCallback);
	glfwSetCursorEnterCallback(display->getWindow(), GameController::cursorEnterCallback);
	glfwSetKeyCallback(display->getWindow(), GameController::keyCallback);

	GameController::setMap(map);
	GameController::setPlayer(player);

	vec2 textureTranslate;
	while (!display->isCloseRequested())
	{
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
		texture = scale(texture, vec2(1.0f/3.0f, 0.25f));
		player->setTextureMatrix(texture);

		cursor->setPosition(mousePosition.x, mousePosition.y, 0.0f);

		shader->start();
		shader->loadViewMatrix(camera);
		map->drawRectangleArea(renderer, loader, shader,
			map->getColumns() * (map->getScale().x - map->getPosition().x) / (2 * map->getScale().x),
			map->getRows() * (map->getScale().y + map->getPosition().y) / (2 * map->getScale().y), 16, 10);
		//renderer->render(map, shader);
		renderer->render(player, shader);
		renderer->render(cursor, shader);
		glfwPollEvents();
		shader->stop();

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