#include "GameScene.h"

GameScene::GameScene()
{
	ImGui_ImplDX11_Init(graphics.GetHWND(), graphics.GetDevice(), graphics.GetDeviceContext());
}

void GameScene::SetScene(GameScene *scene)
{
	this->gameObjects = scene->GetGameObjectList();
	this->cameras = scene->GetCameraList();

	this->mainCamera = *(cameras.begin());
}

void GameScene::CheckCollision()
{
	if (gameObjects.size() != 0)
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
}

void GameScene::Start()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Start();
	}
}

void GameScene::PreUpdate()
{
	RefreshLights();
	CheckCollision();

	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->PreUpdate();
	}
}

void GameScene::Update()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Update(gameTime, input);
	}
}

void GameScene::PostUpdate()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->PostUpdate();
	}

	input.SetPreviousPosition();
	gameTime.SetPrevTime();
}

void GameScene::Render()
{
	graphics.Begin();

	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Render();
	}

	graphics.End();
}

void GameScene::PostRender()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->PostRender();
	}
}