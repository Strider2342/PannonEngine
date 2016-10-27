#pragma once
#include <vector>
#include <string>
#include "Graphics.h"
#include "imgui\imgui.h"
#include "imgui\imgui_impl_dx11.h"
#include "Scene.h"
#include "GameTime.h"
#include "Physics.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Collider.h"
#include "Camera.h"
#include "Light.h"
#include "DebugHelper.h"

class GameScene : public Scene
{
public:

protected:

public:
	GameScene();

	void SetScene(GameScene *scene);

	void CheckCollision();

	virtual void Start();
	virtual void PreUpdate();
	virtual void Update();
	virtual void PostUpdate();
	virtual void Render();
	virtual void PostRender();
};