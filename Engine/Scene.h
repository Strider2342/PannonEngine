#pragma once
#include <list>
#include "Graphics.h"
#include "Object.h"
#include "GameObject.h"
#include "Camera.h"

class Scene
{
protected:
	Graphics graphics;

	std::list<GameObject*> gameObjects;
	std::list<Camera*> cameras;

	Camera *mainCamera = nullptr;

public:
	Scene();

	void Init(Graphics &graphics);

	void AddGameObject(GameObject *gameObject);
	GameObject* FindGameObject(std::string name);

	void AddCamera(Camera *camera);

	Camera* GetMainCamera();

	void SetMainCamera(Camera *camera);
};