#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "Graphics.h"
#include "GameSerializer.h"
#include "GameTime.h"
#include "Input.h"
#include "GameObject.h"
#include "Collider.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "Light.h"

#include "Mesh.h"
#include "Texture.h"

class Scene
{
protected:
	Graphics graphics;
	GameTime gameTime;
	Input input;

	GameSerializer serializer;

	std::vector<GameObject*> gameObjects;
	std::vector<Light::ShaderInput> lights;
	std::vector<Camera*> cameras;

	std::vector<Mesh*> meshes;
	std::vector<Texture*> textures;

	DirectX::XMFLOAT3 globalAmbient;

	Camera *mainCamera = nullptr;

public:
	Scene();
	virtual ~Scene();

	void Init(Graphics &graphics);

	std::vector<GameObject*>* GetGameObjectList();
	void AddGameObject(GameObject *gameObject);
	GameObject* FindGameObject(std::string name);

	std::vector<Camera*>& GetCameraList();
	Camera* GetMainCamera();
	DirectX::XMFLOAT3& GetGlobalAmbient();

	void ImportMesh(std::string path);
	void AddCamera(Camera *camera);
	void SetMainCamera(Camera *camera);
	void SetGlobalAmbient(DirectX::XMFLOAT3 globalAmbient);

	void ClearScene();

	void RefreshLights();
	void SetSceneProperties();
};