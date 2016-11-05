#pragma once
#include <vector>
#include <d3d11.h>
#include <DirectXMath.h>
#include "Graphics.h"
#include "Scene.h"
#include "GameScene.h"
#include "EditorGUI.h"
#include "ContentManager.h"
#include "GameObject.h"
#include "Input.h"

class EditorScene : public GameScene
{
private:
	EditorGUI gui;

	GameObject *selected;
	
	GameObject teapot, bottle;
	GameObject camera;
	GameObject light;

public:
	EditorScene();

	void LoadScene(GameScene *scene);

	void Start();
	void PreUpdate();
	void Update();
	void PostUpdate();
	void Render();
	void PostRender();
};