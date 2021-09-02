#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include"Shader.h"

class Camera
{
public:
	// Stores the main vectors of the camera
	glm::vec3 normalPosition;
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 Down = glm::vec3(0.0f, -1.0f, 0.0f);
	glm::mat4 cameraMatrix = glm::mat4(1.0f);


	bool firstClick = true;

	// Stores the width and height of the window
	int width;
	int height;


	// Adjust the speed of the camera and it's sensitivity when looking around
	float speed = 0.1f;
	float sensitivity = 100.0f;
	static float zoom;

	// Camera constructor to set up initial values
	Camera(int width, int height, glm::vec3 position = glm::vec3(1.0, 0.2, 1.0));
	Camera();

	// Updates the camera matrix to the Vertex Shader
	void updateMatrix(float FOVdeg, float nearPlane, float farPlane);
	// Exports the camera matrix to a shader
	void Matrix(Shader& shader, const char* uniform);
	// Handles camera inputs
	void Inputs(GLFWwindow* window);

	glm::vec3 GetPosition();

private:

	glm::vec2 mousePos = glm::vec2(0.0f, 0.0f);
	glm::vec2 initialMousePos = glm::vec2(0.0f, 0.0f);
	glm::vec2 mouseDirection = glm::vec2(0.0f, 0.0f);
	glm::vec3 rotateVector = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 rotateVectorY = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraRight = glm::vec3(1.0, 0.0, 0.0);
	glm::vec3 cameraUp = glm::vec3(0.0, 1.0, 0.0);
};

#endif