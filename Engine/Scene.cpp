#include "Scene.h"

Scene::Scene()
{ }

void Scene::Init(Graphics &graphics)
{
	this->graphics = graphics;

	gameObjects = std::vector<GameObject*>();
}

void Scene::SetScene(Scene *scene)
{
	this->gameObjects = scene->GetGameObjectList();
	this->cameras = scene->GetCameraList();
	this->lights = scene->GetLightList();

	this->mainCamera = *(cameras.begin());
}

std::vector<GameObject*>& Scene::GetGameObjectList()
{
	return gameObjects;
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

void Scene::AddCamera(Camera *camera)
{
	cameras.push_back(camera);
}

Camera* Scene::GetMainCamera()
{
	return mainCamera;
}

void Scene::SetMainCamera(Camera *camera)
{
	mainCamera = camera;
}

std::vector<Light*>& Scene::GetLightList()
{
	return lights;
}

void Scene::AddLight(Light *light)
{
	lights.push_back(light);
}
