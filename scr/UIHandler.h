#ifndef UIHANDLER_H
#define UIHANDLER_H
#include "PathHelper.h"
#include "Model.h"
#include "GlApp.h"

class UIHandler {
public:

	UIHandler(GlApp* x);
	UIHandler();

	GlApp* app;

	void InitializeImgui(GLFWwindow* windowP);
	void PreRender();
	void SetupPageLayouts();
	void RenderImguiElements();
	void DestroyImgui();
	bool IsCaptureMouse();
	void LoadModel();
	void LoadTexture();
};

#endif