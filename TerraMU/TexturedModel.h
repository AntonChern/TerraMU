#pragma once
class RawModel;
class ModelTexture;
#include <glm/glm.hpp>
using namespace glm;

class TexturedModel {
private:
	RawModel *rawModel;
	ModelTexture *texture;

public:
	TexturedModel(RawModel *model, ModelTexture *texture) : rawModel(model), texture(texture) {};
	RawModel *getRawModel() { return rawModel; };
	ModelTexture *getTexture() { return texture; };

};

