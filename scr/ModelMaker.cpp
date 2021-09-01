#include"ModelMaker.h"

Model* ModelMaker::MakeModel(std::string modelDirection, std::string textureDirection,
	std::string fragmentShaderName, std::string vertexShaderName, Camera& camera, Material::ShaderType shaderType) {

	Shader* shaderProgram = new Shader(&vertexShaderName[0], &fragmentShaderName[0]);

	Model* model = new Model(modelDirection, textureDirection, *shaderProgram, camera, shaderType);

	
	return model;

}