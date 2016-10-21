#pragma once
#include <iostream>
#include <string>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "GameObject.h"
#include "Component.h";
#include "Physics.h";
#include "MeshRenderer.h";
#include "Camera.h";
#include "Light.h";
#include "Script.h";

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

	// menus
	void MenuBar();
	void FileMenu();
	void ViewMenu();
	void CreateMenu();
	void HelpMenu();

	// views
	void Views();
	void InspectorView();
	void HierarchyView();
	void MaterialEditor();
	void DebugConsole();
	void GameCanvas();

	// components
	void TransformComponent();
	void PhysicsComponent();
	void MeshRendererComponent();
	void CameraComponent();
	void LightComponent();
	void ScriptComponent();
	void SphereColliderComponent();
	void BoxColliderComponent();

	void AssembleGUI();

	void SetSelected(GameObject *selected);
};