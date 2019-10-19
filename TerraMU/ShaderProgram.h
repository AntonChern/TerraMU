#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

class ShaderProgram {
private:
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
	int programID;

	void loadMatrix(int location, mat4 matrix);
	void loadMatrix(int location, mat3 matrix);
	int getUniformLocation(const GLchar* uniformName);
	virtual void getAllUniformLocations() = 0;
	virtual void bindAttributes() = 0;
	void bindAttribute(GLuint index, const GLchar *name);
};