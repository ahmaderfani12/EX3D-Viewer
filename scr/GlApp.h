#ifndef GLAPP_H
#define GLAPP_H
#include <string>
#include <iostream>
#include "Camera.h"
#include "Model.h"



class GlApp {
public:
	int width;
	int height;

	Camera camera;

	GLFWwindow* window;
	Model* mainModel;
	Model* gizmoModel;
	GlApp(const std::string& appName, int height, int width);
	void Start();
	void Update();
	void SetMainModel(std::string modelDirection, std::string textureDirection);

private:
	void InitialApp(const std::string& appName, int height, int width);
	void PreRender();
	void PostRender();
	void SetCameraAttribute();
	void SetCameraInput();
	void Terminate();

	void SetGizmoModel(std::string modelDirection, std::string textureDirection);

};
#endif