#pragma once
#include "Graphics.h"
#include "Scene.h"
#include "ContentManager.h"

class Scene2 : public Scene
{
private:
	GameObject camera;
	GameObject test;

public:
	Scene2();

	void Start();
	void Load();
	void Update();
	void Render();
};