#ifndef GLAPP_H
#define GLAPP_H
#include <string>
#include <iostream>
#include "Camera.h"
#include "Model.h"



class GlApp {
public:

	GLFWwindow* window;
	Camera camera;
	int width;
	int height;
	Model* mainModel;
	GlApp(const std::string& appName, int height, int width);
	void Start();
	void SetMainModel(std::string modelDirection, std::string textureDirection);

private:
	void InitialApp(const std::string& appName, int height, int width);
	void PreRender();
	void PostRender();
	void SetCameraAttribute();
	void SetCameraInput();
	void Terminate();

};
#endif