#pragma once
#include <GL/glew.h>
#include <list>
class RawModel;
using namespace std;

class Loader {
private:
	list<GLuint> *vaos;
	list<GLuint> *vbos;
	list<GLuint> *textures;

	GLuint createVao();
	void storeDataInAttributeList(int attributeNumber, int coordinateSize, float data[], int dataCount);
	void unbindVao();
	void bindIndicesBuffer(int indices[], int indicesCount);

public:
	Loader();
	~Loader();
	RawModel *loadToVao(float positions[], int positionsCount, int indices[], int indicesCount, float textureCoords[], int textureCoordsCount);
	GLuint loadTexture(char const filePath[]);
	void cleanUp();

};
