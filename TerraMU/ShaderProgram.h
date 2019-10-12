#pragma once
#include <GL/glew.h>

class ShaderProgram {
private:
	int programID;
	int vertexShaderID;
	int fragmentShaderID;

	GLuint loadShader(char const filePath[], int type);

public:
	ShaderProgram(char const vertexFile[], char const fragmentFile[]);
	void start();
	void stop();
	void cleanUp();
	int getProgramID();

protected:
	virtual void bindAttributes() = 0;
	void bindAttribute(GLuint index, const GLchar *name);
};