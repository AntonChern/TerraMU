#pragma once
#include "ShaderProgram.h"
#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

class StreamShader : public ShaderProgram {
private:
	int transformLocation;
	int projectionLocation;
	int viewLocation;

public:
	//using ShaderProgram::ShaderProgram;
	StreamShader();
	void loadTransormMatrix(mat4 matrix);
	void loadProjectionMatrix(mat4 matrix);
	void loadViewMatrix(Camera *camera);

protected:
	void bindAttributes() override;
	void getAllUniformLocations() override;
};