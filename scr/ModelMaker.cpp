#include"ModelMaker.h"

Model* ModelMaker::MakeModel(std::string modelDirection, std::string textureDirection,
	std::string fragmentShaderName, std::string vertexShaderName, Camera& camera) {

	Shader* shaderProgram = new Shader(&vertexShaderName[0], &fragmentShaderName[0]);

	//make model
	Model* model = new Model(modelDirection, textureDirection, *shaderProgram, camera);



	//adjust shaders
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 objectPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 objectModel = glm::mat4(1.0f);
	objectModel = glm::translate(objectModel, objectPos);

	shaderProgram->Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram->ID, "model"), 1, GL_FALSE, glm::value_ptr(objectModel));
	glUniform4f(glGetUniformLocation(shaderProgram->ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);

	return model;

}