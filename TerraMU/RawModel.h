#pragma once
#include <GL/glew.h>

class RawModel {
private:
	GLuint vaoID;
	int vertexCount;
public:
	RawModel(int vaoID, int vertexCount) : vaoID(vaoID), vertexCount(vertexCount) {};
	GLuint getVaoID() { return vaoID; };
	int getVertexCount() { return vertexCount; };
};

