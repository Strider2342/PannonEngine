#include "Scene.h"

Scene::Scene()
{

}

void Scene::Init(Graphics &graphics)
{
	this->graphics = graphics;

	test = GameObject();

	std::cout << "GameObject: ";
	test.GetMesh()->Sajt();
	std::cout << std::endl;

	std::cout << "Mesh: ";
	test.GetMesh()->GetGameObject()->Sajt();
	std::cout << std::endl;
}

void Scene::Load()
{

}

void Scene::Update()
{

}

void Scene::Draw()
{
	graphics.Begin();

	graphics.End();
}