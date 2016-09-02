#pragma once
#include "Graphics.h"
#include "Scene.h"
#include "GameObject.h"

class Scene1 : public Scene
{
private:
	GameObject test;

public:
	Scene1();

	void Load();
	void Update();
	void Draw();
};