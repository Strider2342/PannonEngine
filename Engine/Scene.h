#pragma once
#include <iostream>
#include <vector>
#include "Graphics.h"
#include "Object.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "Light.h"

#include "Mesh.h"
#include "Texture.h"

class Scene : public Object
{
protected:
	Graphics graphics;
	GameTime gameTime;

	std::vector<GameObject*> gameObjects;
	std::vector<Light::ShaderInput> lights;
	std::vector<Camera*> cameras;

	std::vector<Mesh*> meshes;
	std::vector<Texture*> textures;

	Camera *mainCamera = nullptr;

public:
	Scene();

	void Init(Graphics &graphics);

	std::vector<GameObject*>& GetGameObjectList();
	void AddGameObject(GameObject *gameObject);
	GameObject* FindGameObject(std::string name);

	std::vector<Camera*>& GetCameraList();
	void AddCamera(Camera *camera);
	Camera* GetMainCamera();
	void SetMainCamera(Camera *camera);

	void RefreshLights();
};