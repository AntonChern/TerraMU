#include "ShaderProgram.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <GL/glew.h>
using namespace std;

ShaderProgram::ShaderProgram(char const vertexFile[], char const fragmentFile[]) {
	vertexShaderID = loadShader(vertexFile, GL_VERTEX_SHADER);
	fragmentShaderID = loadShader(fragmentFile, GL_FRAGMENT_SHADER);
	programID = glCreateProgram();

	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	bindAttributes();
	glLinkProgram(programID);
}

GLuint ShaderProgram::loadShader(char const filePath[], int type) {
	string shaderSource("");

	ifstream fin(filePath);
	if (!fin.is_open()) {
		cout << "File reading error" << endl;
		exit(-1);
	}

	string currentString("");
	while (!fin.eof()) {
		getline(fin, currentString);
		shaderSource.append(currentString).append("\n");
	}

	fin.close();

	GLuint shaderID = glCreateShader(type);

	const char* source = shaderSource.c_str();
	glShaderSource(shaderID, 1, &source, NULL);
	glCompileShader(shaderID);

	GLint success = 0;
	GLchar infoLog[512];
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
		cout << "Shader compilation failed\n" << infoLog << endl;
		exit(-1);
	}

	return shaderID;
}

void ShaderProgram::start() {
	glUseProgram(programID);
}

void ShaderProgram::stop() {
	glUseProgram(0);
}

void ShaderProgram::cleanUp() {
	stop();
	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
	glDeleteProgram(programID);
}

int ShaderProgram::getProgramID() {
	return programID;
}

void ShaderProgram::bindAttribute(GLuint index, const GLchar* name) {
	glBindAttribLocation(programID, index, name);
}

void ShaderProgram::bindAttributes() {};