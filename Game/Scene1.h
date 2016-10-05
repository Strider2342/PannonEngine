#pragma once
#include "Graphics.h"
#include "Scene.h"
#include "ContentManager.h"

#include "MyFirstScript.h"
#include "TestScript1.h"
#include "TestScript2.h"

class Scene1 : public Scene
{
private:
	GameObject camera;
	GameObject test;
	GameObject teapot, teapot2;
	GameObject light1, light2;

public:
	Scene1();

	void Start();
	void Load();
	void Update();
	void Draw();
};