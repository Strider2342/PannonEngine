#pragma once
#include "Graphics.h"
#include "GameScene.h"
#include "ContentManager.h"
#include "GameObject.h"

class Scene1 : public GameScene
{
private:
	Camera camera;

	GameObject proba;

public:
	Scene1();

	void Start();
	void Load();
	void Update();
	void Draw();
};