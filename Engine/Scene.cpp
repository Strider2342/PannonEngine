#include "Scene.h"

Scene::Scene()
{
	graphics = Graphics();

	serializer = GameSerializer();

	gameObjects = std::vector<GameObject*>();
	globalAmbient = DirectX::XMFLOAT3(0.5f, 0.5f, 0.5f);
}

Scene::~Scene()
{
}

void Scene::Init(Graphics &graphics)
{
	this->graphics = graphics;
	serializer.SetGraphics(&graphics);

	lights = std::vector<Light::ShaderInput>();
	cameras = std::vector<Camera*>();

	meshes = std::vector<Mesh*>();
	textures = std::vector<Texture*>();
}

std::vector<GameObject*>* Scene::GetGameObjectList()
{
	return &gameObjects;
}

void Scene::AddGameObject(GameObject *gameObject)
{
	gameObjects.push_back(gameObject);
}
GameObject* Scene::FindGameObject(std::string name)
{
	std::vector<GameObject*>::iterator iterator;

	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects[i]->GetName() == name)
		{
			return gameObjects[i];
		}
	}

	return nullptr;
}

std::vector<Camera*>& Scene::GetCameraList()
{
	return cameras;
}

void Scene::ImportMesh(std::string path)
{
	ContentManager content = ContentManager();

	Mesh *mesh = content.LoadMesh(path);

	GameObject *gameObject = new GameObject();
	gameObject->AddComponent<MeshRenderer>();
	gameObject->GetComponent<MeshRenderer>()->Init(graphics.GetDevice(), graphics.GetDeviceContext());
	gameObject->GetComponent<MeshRenderer>()->SetCamera(mainCamera);
	gameObject->GetComponent<MeshRenderer>()->SetMesh(mesh);
	gameObject->GetComponent<MeshRenderer>()->SetLights(&lights);

	gameObject->Start();

	gameObjects.push_back(gameObject);
}

void Scene::AddCamera(Camera *camera)
{
	cameras.push_back(camera);
}

Camera* Scene::GetMainCamera()
{
	return mainCamera;
}

DirectX::XMFLOAT3& Scene::GetGlobalAmbient()
{
	return globalAmbient;
}

void Scene::SetMainCamera(Camera *camera)
{
	mainCamera = camera;
}

void Scene::SetGlobalAmbient(DirectX::XMFLOAT3 globalAmbient)
{
	this->globalAmbient = globalAmbient;
}

void Scene::ClearScene()
{
	gameObjects.clear();
	lights.clear();
}

void Scene::RefreshLights()
{
	lights.clear();

	for (int i = 0; i < gameObjects.size(); i++)
	{
		Light *light = gameObjects[i]->GetComponent<Light>();
		if (light)
		{
			Light::ShaderInput shaderinput = light->GetShaderInput();
			lights.push_back(shaderinput);
		}
	}

	for (int i = 0; i < gameObjects.size(); i++)
	{
		MeshRenderer *renderer = gameObjects[i]->GetComponent<MeshRenderer>();
		if (renderer)
		{
			renderer->SetLights(&lights);
		}
	}
}

void Scene::SetSceneProperties()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		MeshRenderer *renderer = gameObjects[i]->GetComponent<MeshRenderer>();
		if (renderer)
		{
			renderer->SetCamera(mainCamera);
			renderer->SetGlobalAmbient(globalAmbient);
		}
	}
}
