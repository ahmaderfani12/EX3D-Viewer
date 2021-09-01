#include "ShaderClass.h"
#include "Camera.h"
#ifndef MATERIAL_H
#define MATERIAL_H

//ToDo: make material class as parent and inherit different mat from it..
class Material {
public:
	enum class ShaderType
	{
		normal,
		gizmo

	}; 
	ShaderType shaderType;
	Shader* shader;
	Camera* camera;

	glm::vec3 objectPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 objectModel = glm::mat4(1.0f);

	 Material(ShaderType type, Shader* shader, Camera* camera);
	void UpdateShader();
	void UpdateNormal();
	void UpdateGizmo();
};

#endif