#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "GameObject.h"

#define IM_ARRAYSIZE(_ARR) ((int)(sizeof(_ARR)/sizeof(*_ARR)))

class EditorGUI
{
private:
	GameObject *selected;

	bool showInspectorView = true;
	bool showHierarchyView = true;
	bool showMaterialEditor = false;
	bool showDebugConsole = true;

public:
	EditorGUI();

	void MenuBar();
	void FileMenu();
	void ViewMenu();
	void CreateMenu();
	void HelpMenu();

	void Views();
	void InspectorView();
	void HierarchyView();
	void MaterialEditor();
	void DebugConsole();
	void GameCanvas();

	void AssembleGUI();
};