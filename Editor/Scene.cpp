#include "Scene.h"

Scene::Scene()
{ }

void Scene::Init(Graphics &graphics)
{
	this->graphics = graphics;

	gameObjects = std::list<GameObject>();
}

GameObject* Scene::FindGameObject(std::string name)
{
	std::list<GameObject>::iterator iterator;

	for (iterator = gameObjects.begin(); iterator != gameObjects.end(); ++iterator)
	{
		if ((*iterator).GetName() == name)
		{
			return &(*iterator);
		}
	}

	return nullptr;
}
