#pragma once
#include "ShaderProgram.h"

class StreamShader : public ShaderProgram {
public:
	StreamShader() : ShaderProgram::ShaderProgram("StreamVertexShader.txt", "StreamFragmentShader.txt") {};

protected:
	void bindAttributes() override;

};