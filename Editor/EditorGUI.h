#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "imgui/imgui.h"
#include "imgui\imgui_impl_dx11.h"
#include "GUI.h"
#include "GameScene.h"
#include "GameObject.h"
#include "Component.h";
#include "Physics.h";
#include "MeshRenderer.h";
#include "Camera.h";
#include "Light.h";
#include "Script.h";

#include "FileFinder.h"

#define IM_ARRAYSIZE(_ARR) ((int)(sizeof(_ARR)/sizeof(*_ARR)))

class EditorGUI : public GUI
{
private:
	GameObject *selected = nullptr;
	std::vector<GameObject *> *gameObjects;

	bool showInspectorView = true;
	bool showHierarchyView = true;
	bool showMaterialEditor = false;
	bool showDebugConsole = true;
	bool showImportMeshWindow = false;
	bool showOpenSceneDialog = false;
	bool showSaveSceneDialog = false;
	bool showNewComponentDialog = false;

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
	void ImportMeshWindow();
	void OpenSceneDialog();
	void SaveSceneDialog();

	// components
	void NewComponentDialog();
	void TransformComponent();
	void PhysicsComponent();
	void MeshRendererComponent();
	void CameraComponent();
	void LightComponent();
	void ScriptComponent(std::string name);
	void SphereColliderComponent();
	void BoxColliderComponent();

	void Init();
	void AssembleGUI();

	void Render();
};