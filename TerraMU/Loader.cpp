#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include "Loader.h"

Loader::Loader() {
	vaos = new list<GLuint>();
	vbos = new list<GLuint>();
	textures = new list<GLuint>();
}

Loader::~Loader() {
	delete vaos;
	delete vbos;
	delete textures;
}

GLuint Loader::createVao() {
	GLuint vaoID;
	glGenVertexArrays(1, &vaoID);
	vaos->push_back(vaoID);
	glBindVertexArray(vaoID);
	return vaoID;
}

void Loader::storeDataInAttributeList(int attributeNumber, int coordinateSize, float data[], int dataCount) {
	GLuint vboID;
	glGenBuffers(1, &vboID);
	vbos->push_back(vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * dataCount, data, GL_STATIC_DRAW);
	glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::unbindVao() {
	glBindVertexArray(0);
}

void Loader::bindIndicesBuffer(int indices[], int indicesCount) {
	GLuint vboID;
	glGenBuffers(1, &vboID);
	vbos->push_back(vboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indicesCount, indices, GL_STATIC_DRAW); //STATIC
}

void Loader::cleanUp() {
	for (GLuint vao : *vaos) {
		glDeleteVertexArrays(1, &vao);
	}
	for (GLuint vbo : *vbos) {
		glDeleteBuffers(1, &vbo);
	}
	for (GLuint texture : *textures) {
		glDeleteTextures(1, &texture);
	}
}

RawModel *Loader::loadToVao(float positions[], int positionsCount, int indices[], int indicesCount, float textureCoords[], int textureCoordsCount) {
	GLuint vaoID = createVao();
	bindIndicesBuffer(indices, indicesCount);
	storeDataInAttributeList(0, 3, positions, positionsCount);
	storeDataInAttributeList(1, 2, textureCoords, textureCoordsCount);
	unbindVao();
	return new RawModel(vaoID, indicesCount);
}

GLuint Loader::loadTexture(char const filePath[]) {
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	//Настройка текстуры
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int width;
	int height;
	unsigned char* image = SOIL_load_image(filePath, &width, &height, 0, SOIL_LOAD_RGBA);
	/*GLuint image = SOIL_load_OGL_texture(
		fileName,
		SOIL_LOAD_RGB,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
	);*/

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(image);

	return textureID;
}