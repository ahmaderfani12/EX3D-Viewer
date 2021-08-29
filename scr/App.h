#include <string>
#include <iostream>

#include "Camera.h"

class App {
public:

	GLFWwindow* window;
	Camera camera;


	App( std::string appName, int height, int width);
	App();
	void Start();

};