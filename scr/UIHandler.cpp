#include"UIHandler.h"
#include "imgui.h"

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <windows.h>
#include <shobjidl.h> 
#include "FileIO.h"




void UIHandler::InitializeImgui(GLFWwindow* windowP)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(windowP, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void UIHandler::PreRender()
{
	// Tell OpenGL a new frame is about to begin 
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void UIHandler::SetupPageLayouts()
{
	// ImGui Page setup

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New Model","fbx,obj")) { LoadModel(); }
			if (ImGui::MenuItem("New Texture")) { LoadTexture(); }
			ImGui::Separator();
			if (ImGui::MenuItem("Exit")) {exit(3);}

			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	ImGui::Begin("X3DViewer");

	
	

	if (ImGui::Button("Open Model")) {

	}	
	ImGui::ShowDemoWindow();
	ImGui::Text("Hello there adventurer!");
	ImGui::End();
}

void UIHandler::RenderImguiElements()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UIHandler::DestroyImgui()
{
	// Deletes all ImGUI instances
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

bool UIHandler::IsCaptureMouse()
{
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	if (io.WantCaptureMouse)
		return true;
	else
		return false;
}

void UIHandler::LoadModel()
{
	std::string modelDirection = PathHelper::GetUserDirectory();
	if(!modelDirection.empty())
		app->SetMainModel(modelDirection, "");
}

void UIHandler::LoadTexture()
{
	std::string TextureDirection = PathHelper::GetUserDirectory();
	if (!TextureDirection.empty())
		app->SetMainModel(app->mainModel->returnMeshDirection(), TextureDirection);
}
