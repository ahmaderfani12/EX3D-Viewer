#include "Model.h"

class ModelMaker {
public:
	static Model* MakeModel(std::string modelDirection, std::string textureDirection,
		std::string fragmentShaderName, std::string vertexShaderName, Camera& camera);
};
