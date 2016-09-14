#pragma once
#include <list>
#include "Graphics.h"
#include "Object.h"
#include "GameObject.h"
#include "Camera.h"
#include "Light.h"
#include "DebugHelper.h"

class Scene
{
public:
	Graphics graphics;

	std::list<GameObject*> gameObjects;
	std::list<Camera*> cameras;
	std::list<Light*> lights;

	Camera *mainCamera = nullptr;

public:
	Scene();

	void Init(Graphics &graphics);
	void SetScene(Scene *scene);

	// gameObjects
	std::list<GameObject*>& GetGameObjectList();

	void AddGameObject(GameObject *gameObject);
	GameObject* FindGameObject(std::string name);

	// cameras
	std::list<Camera*>& GetCameraList();

	void AddCamera(Camera *camera);
	Camera* GetMainCamera();
	void SetMainCamera(Camera *camera);

	// lights
	std::list<Light*>& GetLightList();

	void AddLight(Light *light);
};