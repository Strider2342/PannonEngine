#include "Scene.h"

Scene::Scene()
{ }

void Scene::Init(Graphics &graphics)
{
	this->graphics = graphics;

	gameObjects = std::list<GameObject*>();
}

void Scene::SetScene(Scene *scene)
{
	this->gameObjects = scene->GetGameObjectList();
	this->cameras = scene->GetCameraList();
	this->lights = scene->GetLightList();

	this->mainCamera = *(cameras.begin());
}

std::list<GameObject*>& Scene::GetGameObjectList()
{
	return gameObjects;
}

void Scene::AddGameObject(GameObject *gameObject)
{
	gameObjects.push_back(gameObject);
}
GameObject* Scene::FindGameObject(std::string name)
{
	std::list<GameObject*>::iterator iterator;

	for (iterator = gameObjects.begin(); iterator != gameObjects.end(); ++iterator)
	{
		GameObject *gameObject = *iterator;
		if (gameObject->GetName() == name)
		{
			return gameObject;
		}
	}

	return nullptr;
}

std::list<Camera*>& Scene::GetCameraList()
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

std::list<Light*>& Scene::GetLightList()
{
	return lights;
}