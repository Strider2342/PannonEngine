#pragma once
#include <vector>
#include "Graphics.h"
#include "GameTime.h"
#include "Object.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Collider.h"
#include "Camera.h"
#include "Light.h"
#include "DebugHelper.h"

class Scene
{
public:
	Graphics graphics;

	GameTime gameTime;

	std::vector<GameObject*> gameObjects;
	std::vector<Camera*> cameras;
	
	std::vector<Light::ShaderInput> lights;

	Camera *mainCamera = nullptr;

public:
	Scene();

	void Init(Graphics &graphics);
	void SetScene(Scene *scene);

	// gameObjects
	std::vector<GameObject*>& GetGameObjectList();
	void AddGameObject(GameObject *gameObject);
	GameObject* FindGameObject(std::string name);

	// cameras
	std::vector<Camera*>& GetCameraList();
	void AddCamera(Camera *camera);
	Camera* GetMainCamera();
	void SetMainCamera(Camera *camera);
	
	void RefreshLights();

	void Start();
	void PreUpdate();
	void Update();
	void PostUpdate();
	void Render();
};