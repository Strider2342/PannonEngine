#pragma once
#include "Graphics.h"
#include "GameScene.h"
#include "ContentManager.h"

class Scene2 : public GameScene
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