#pragma once
#include <list>
#include "Graphics.h"
#include "GameObject.h"

class Scene
{
protected:
	Graphics graphics;

	std::list<GameObject> gameObjects;

public:
	Scene();

	void Init(Graphics &graphics);
	GameObject* FindGameObject(std::string name);
};