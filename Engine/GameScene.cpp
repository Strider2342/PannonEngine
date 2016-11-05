#include "GameScene.h"

GameScene::GameScene()
{
	ImGui_ImplDX11_Init(graphics.GetHWND(), graphics.GetDevice(), graphics.GetDeviceContext());
}

GameScene* GameScene::Get()
{
	return this;
}

void GameScene::SetScene(GameScene *scene)
{
	this->gameObjects = scene->GetGameObjectList();
	//this->cameras = scene->GetCameraList();
}

void GameScene::CheckCollision()
{
	if (gameObjects.size() != 0)
	{
		for (int i = 0; i < gameObjects.size() - 1; i++)
		{
			Collider *collider1 = gameObjects[i]->GetComponent<Collider>();

			if (collider1 != nullptr)
			{
				for (int j = i + 1; j < gameObjects.size(); j++)
				{
					Collider *collider2 = gameObjects[j]->GetComponent<Collider>();

					if (collider2 != nullptr)
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
		gameObjects[i]->PostRender();
	}

	graphics.End();
}

void GameScene::PostRender()
{
	/*for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->PostRender();
	}*/
}

/*
void GameScene::ExportToFile()
{
	GameSerializer serializer = GameSerializer();
	json json_scene = serializer.ExportScene(this);

	std::cout << json_scene.dump() << std::endl;
}
*/