#include"ModelMaker.h"

Model* ModelMaker::MakeModel(std::string modelDirection, std::string textureDirection,
	std::string fragmentShaderName, std::string vertexShaderName, Camera& camera) {

	Shader* shaderProgram = new Shader(&vertexShaderName[0], &fragmentShaderName[0]);

	Model* model = new Model(modelDirection, textureDirection, *shaderProgram, camera);

	//adjust position(vertex shader)
	glm::vec3 objectPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 objectModel = glm::mat4(1.0f);
	objectModel = glm::translate(objectModel, objectPos);

	shaderProgram->Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram->ID, "model"), 1, GL_FALSE, glm::value_ptr(objectModel));
	return model;

}