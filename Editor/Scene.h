#pragma once
#include "Graphics.h"
#include "GameObject.h"

class Scene
{
private:
	Graphics graphics;

	GameObject test;

public:
	Scene();

	void Init(Graphics &graphics);
	void Load();
	void Update();
	void Draw();
};