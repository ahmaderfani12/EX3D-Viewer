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
//ToDo:delete this
static float col1[3] = { 1.0f, 0.0f, 0.2f };
static float col2[3] = { 0.4f, 0.7f, 0.0f };
static float vecf[] = { 0.10f, 0.20f, 0.30f };
float s;
static float vec4a[4] = { 0.10f, 0.20f, 0.30f, 0.44f };
void UIHandler::SetupPageLayouts()
{
	

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


	ImGui::Begin("Setting");

	
	
	if (ImGui::CollapsingHeader("Material"))
	{
		ImGui::Spacing();
		ImGui::ColorEdit3("Tint Color", col1);
		ImGui::Spacing();
		ImGui::Text("Specular");
		ImGui::SliderFloat("", &s, 0.0f, 1.0f);
	}

	if (ImGui::CollapsingHeader("Enviroment"))
	{
		
		ImGui::Spacing();
		ImGui::Text("Light Position");
		ImGui::DragFloat3("", vecf);
		ImGui::Spacing();
		ImGui::ColorEdit3("Sky Color", col1);
		ImGui::ColorEdit3("Light Color 1", col1);
		ImGui::ColorEdit3("Light Color 2", col2);
		
	}


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
