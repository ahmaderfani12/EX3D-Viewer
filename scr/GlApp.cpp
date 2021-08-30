#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include"GlApp.h"
#include "Texture.h"
#include "ModelMaker.h"
#include "UIHandler.h"
#include"SettingData.h"



GlApp::GlApp(const std::string& appName, int height, int width)
{
	InitialApp(appName, height, width);
}

void GlApp::Start() {

	//On start Model
	SetMainModel(PathHelper::GetRootPath() + "/files/backpack.obj", PathHelper::GetRootPath() + "/files/diffuse.png");
	SetGizmoModel(PathHelper::GetRootPath() + "/files/XYZ.fbx", PathHelper::GetRootPath() + "/files/Gradient.png");

	UIHandler ui = UIHandler(this);

	// Initialize ImGUI
	ui.InitializeImgui(window);



	while (!glfwWindowShouldClose(window))
	{
		PreRender();

		ui.PreRender();

		SetCameraAttribute();

		
		mainModel->Draw();
		if(SettingData::showGizmo)
			gizmoModel->Draw();

		ui.SetupPageLayouts();

		ui.RenderImguiElements();

		PostRender();

		if(!ui.IsCaptureMouse())
			SetCameraInput();
	}

	ui.DestroyImgui();
	Terminate();
}
void GlApp::SetMainModel(std::string modelDirection, std::string textureDirection)
{
	delete mainModel;
	mainModel = ModelMaker::MakeModel(modelDirection, textureDirection,
		PathHelper::GetRootPath()+"/files/default.frag", PathHelper::GetRootPath() + "/files/default.vert", camera);
}

void GlApp::SetGizmoModel(std::string modelDirection, std::string textureDirection)
{
	delete gizmoModel;
	gizmoModel = ModelMaker::MakeModel(modelDirection, textureDirection,
		PathHelper::GetRootPath() + "/files/gizmo.frag", PathHelper::GetRootPath() + "/files/default.vert", camera);
}

void GlApp::PreRender() {
	// Specify the color of the background
	glClearColor(SettingData::skyColor[0], SettingData::skyColor[1], SettingData::skyColor[2], 1.0f);
	// Clean the back buffer and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GlApp::PostRender() {
	// Swap the back buffer with the front buffer
	glfwSwapBuffers(window);
	// Take care of all GLFW events
	glfwPollEvents();
}

void GlApp::SetCameraAttribute() {
	// Updates and exports the camera matrix to the Vertex Shader(FOV, near & far plane)
	camera.updateMatrix(45.0f, 0.1f, 100.0f);
}



void GlApp::SetCameraInput() {
	camera.Inputs(window);
}

void GlApp::InitialApp(const std::string& appName, int height, int width)
{
	GlApp::height = height;
	GlApp::width = width;
	//init glfw
	glfwInit();
	// Tell GLFW what version of OpenGL 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Create a GLFWwindow object of H by W pixels and naming it 
	window = glfwCreateWindow(width, height, &appName[0], NULL, NULL);

	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);

	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	// Creates camera object & set initial position
	camera = Camera(width, height, glm::vec3(0.0f, 13.0f, 5.0f));
}

void GlApp::Terminate() {
	mainModel->DeleteShader();
	gizmoModel->DeleteShader();
	glfwDestroyWindow(window);
	glfwTerminate();
}

