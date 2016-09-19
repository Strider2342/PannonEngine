#pragma once
#include "Graphics.h"
#include "Scene.h"
#include "ContentManager.h"
#include "GameObject.h"

class Scene1 : public Scene
{
private:
	Camera camera;

public:
	Scene1();

	void Start();
	void Load();
	void Update();
	void Draw();
};