#include "Scene1.h"

Scene1::Scene1()
{ }

void Scene1::Start()
{
	gameObjects.push_back(&proba);

	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Start();
	}
}

void Scene1::Load()
{
	/*ContentManager content = ContentManager();
	content.Init(graphics.GetDevice(), graphics.GetDeviceContext());*/
}

void Scene1::Update()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Update(gameTime);
	}
}

void Scene1::Draw()
{
	graphics.Begin();

	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Render();
	}

	graphics.End();
}