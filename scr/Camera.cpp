#include"Camera.h"
#define PRECISION 0.000001

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

Camera::Camera(int width, int height, glm::vec3 position)
{
	Camera::width = width;
	Camera::height = height;
	normalPosition = glm::normalize(position);
	
}
Camera::Camera()
{
}
float Camera::zoom = 10.0;

void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
	// Initializes matrices since otherwise they will be the null matrix
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	// Makes camera look in the right direction from the right position(cam pos, target, up)

	//normalPosition = glm::rotate(normalPosition, glm::radians(0.1f), Up);

	view = glm::lookAt(normalPosition * zoom, glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	// Adds perspective to the scene
	projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);

	// Sets new camera matrix
	cameraMatrix = projection * view;
}

void Camera::Matrix(Shader& shader, const char* uniform)
{
	// Exports camera matrix
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}


  void Camera::Inputs(GLFWwindow* window)
{

	
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		if (glm::angle(normalPosition, Up) < 0.1 || glm::angle(normalPosition, Down) < 0.1) {
			normalPosition = glm::rotate(normalPosition, glm::radians(0.05f), rotateVector);
			return;
		}

		float mouseDragDistance;

		double mouseX;
		double mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		if (firstClick) {
			initialMousePos = glm::vec2(mouseX, mouseY);
			firstClick = false;
		}
		mousePos = glm::vec2(mouseX, mouseY);
		mouseDirection = mousePos - initialMousePos;
		mouseDirection = glm::length(mouseDirection) > 0.0f? mouseDirection = glm::normalize(mouseDirection):
			mouseDirection = glm::vec2(0.0, 0.0);

		mouseDragDistance = glm::clamp(glm::distance(initialMousePos, mousePos),0.0f,20.0f) ;
		
		 //inverse y to present real direction
		mouseDirection = glm::vec2(mouseDirection.x, mouseDirection.y * -1.0);

		cameraRight = glm::normalize(glm::cross(Up, normalPosition));
		cameraUp = glm::normalize(glm::cross(normalPosition, cameraRight));
		
		if (glm::length(mouseDirection) > 0) {
				cameraRight = mouseDirection.x * cameraRight;
				cameraUp = mouseDirection.y * cameraUp;
		}

		rotateVector =  cameraRight + cameraUp;
		rotateVector = glm::cross(rotateVector, normalPosition);

		normalPosition = glm::rotate(normalPosition, glm::radians( speed * mouseDragDistance / 5.0f), rotateVector);
		//std::cout << normalPosition.x *zoom<<" , "<< normalPosition.y * zoom << " , " << normalPosition.z * zoom << std::endl;

	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		firstClick = true;
	}
	glfwSetScrollCallback(window, scroll_callback);
}
  glm::vec3 Camera::GetPosition()
  {

	  return normalPosition * zoom;
  }
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Camera::zoom -= (float)yoffset;
	if (Camera::zoom < 1.0f)
		Camera::zoom = 1.0f;
	if (Camera::zoom > 45.0f)
		Camera::zoom = 45.0f;
}