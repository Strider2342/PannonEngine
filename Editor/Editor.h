#pragma once
#include <vector>
#include <d3d11.h>
#include <DirectXMath.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "Scene.h"
#include "EditorGraphics.h"
#include "EditorGUI.h"
#include "ContentManager.h"
#include "GameObject.h"
#include "Input.h"

class Editor : public Scene
{
private:
	EditorGraphics *graphics;
	EditorGUI gui;

	GameObject *selected;
	
	GameObject *teapot;
	GameObject *camera;
	GameObject *light;

	std::vector<GameObject *> gameObjects;
	std::vector<Light::ShaderInput> lights;

public:
	Editor();
	
	void Init(EditorGraphics *graphics);

	void Start();
	void Load();
	void Update();
	void Draw();

	void RefreshLights();
};