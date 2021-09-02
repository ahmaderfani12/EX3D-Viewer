#include"UIHandler.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <windows.h>
#include <shobjidl.h> 
#include "FileIO.h"
#include "SettingData.h"



UIHandler::UIHandler(GlApp* x)
{
	app = x;
}

UIHandler::UIHandler()
{
}


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


	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New Model", "fbx,obj")) { LoadModel(); }
			if (ImGui::MenuItem("New Texture")) { LoadTexture(); }
			ImGui::Separator();
			if (ImGui::MenuItem("Exit")) { exit(3); }

			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}


	ImGui::Begin("Setting");

	

	{
		ImGui::Spacing();
		ImGui::Text("Transform");
		ImGui::DragFloat3("Position", SettingData::mainModelPos, 0.1, -50.0, 50.0);
		ImGui::DragFloat3("Rotation", SettingData::mainModelAngle, 0.1);
		ImGui::DragFloat3("Scale", SettingData::mainModelScale, 0.1, -5.0, 5.0);
	}

	{
		ImGui::Spacing();
		ImGui::Text("Specular");
		ImGui::SliderFloat("amount", &SettingData::specular, 0.0f, 5.0f);
		ImGui::SliderFloat("power", &SettingData::specularPower, 1.0f, 20.0f);
	}
	{
		ImGui::Spacing();
		ImGui::Text("Rim");
		ImGui::SliderFloat("power ", &SettingData::rimPower, 0.0f, 5.0f);
		ImGui::SliderFloat("Strength", &SettingData::rimStrength, 1.0f, 10.0f);
		ImGui::ColorEdit3("Color", SettingData::rimColor);
		ImGui::NewLine();
	}
	

	if (ImGui::CollapsingHeader("Enviroment"))
	{
		
		ImGui::Spacing();
		ImGui::Text("Light Position");
		ImGui::DragFloat3("", SettingData::lightPosition,0.1,-5.0,5.0);
		ImGui::NewLine();
		ImGui::ColorEdit3("Sky Color",SettingData::skyColor);
		ImGui::Spacing();
		ImGui::ColorEdit3("Light Color", SettingData::lightColor);
		ImGui::Spacing();
		ImGui::ColorEdit3("Shadow Color", SettingData::lightShadowColor);
		ImGui::NewLine();
		ImGui::Checkbox("Show World Gizmo", &SettingData::showGizmo);
		
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
