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

void Scene::RefreshLights()
{
	lights.clear();

	for (int i = 0; i < gameObjects.size(); i++)
	{
		Light *light = gameObjects[i]->GetComponent<Light>();
		if (light)
		{
			Light::ShaderInput input = light->GetShaderInput();
			lights.push_back(input);
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

void Scene::CheckCollision()
{
	for (int i = 0; i < gameObjects.size() - 1; i++)
	{
		Collider *collider1 = gameObjects[i]->GetComponent<Collider>();

		if (collider1 != NULL)
		{
			for (int j = i + 1; j < gameObjects.size(); j++)
			{
				Collider *collider2 = gameObjects[j]->GetComponent<Collider>();

				if (collider2 != NULL)
				{
					if (dynamic_cast<BoxCollider *>(collider1))
					{
						if (dynamic_cast<BoxCollider *>(collider2))
						{
							if (dynamic_cast<BoxCollider *>(collider1)->Colliding(dynamic_cast<BoxCollider *>(collider2)->GetCollider()))
							{
								gameObjects[i]->OnCollision();
								gameObjects[j]->OnCollision();
							}
						}
						else if (dynamic_cast<SphereCollider *>(collider2))
						{
							if (dynamic_cast<BoxCollider *>(collider1)->Colliding(dynamic_cast<SphereCollider *>(collider2)->GetCollider()))
							{
								gameObjects[i]->OnCollision();
								gameObjects[j]->OnCollision();
							}
						}
					}
					else if (dynamic_cast<SphereCollider *>(collider1))
					{
						if (dynamic_cast<BoxCollider *>(collider2))
						{
							if (dynamic_cast<SphereCollider *>(collider1)->Colliding(dynamic_cast<BoxCollider *>(collider2)->GetCollider()))
							{
								gameObjects[i]->OnCollision();
								gameObjects[j]->OnCollision();
							}
						}
						else if (dynamic_cast<SphereCollider *>(collider2))
						{
							if (dynamic_cast<SphereCollider *>(collider1)->Colliding(dynamic_cast<SphereCollider *>(collider2)->GetCollider()))
							{
								gameObjects[i]->OnCollision();
								gameObjects[j]->OnCollision();
							}
						}
					}
				}
			}
		}
	}
}

void Scene::Load()
{
}

void Scene::Start()
{
}

void Scene::PreUpdate()
{
	RefreshLights();
	CheckCollision();
}

void Scene::Update()
{
}

void Scene::PostUpdate()
{
	gameTime.SetPrevTime();
}

void Scene::Render()
{
}

void Scene::PostRender()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->PostRender();
	}
}
