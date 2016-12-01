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
	this->gameObjects = *(scene->GetGameObjectList());
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
	SetSceneProperties();
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

void GameScene::ImportFromFile(std::string filename)
{
	std::ifstream file(filename);
	std::string text = "";
	std::string scripts = "";

	if (file.is_open())
	{
		std::string line;
		while (getline(file, line))
		{
			text += line;
		}
		file.close();
	}

	json scene_json = json::parse(text.c_str())["scene"];

	gameObjects.clear();

	// global ambient light
	DirectX::XMFLOAT3 globalAmbient = DirectX::XMFLOAT3(scene_json["globalAmbient"]["x"], scene_json["globalAmbient"]["y"], scene_json["globalAmbient"]["z"]);
	SetGlobalAmbient(globalAmbient);

	serializer.ClearScripts();

	// game objects
	json gameObjects_json = scene_json["gameObjects"];
	int i = 0;
	for (json::iterator it = gameObjects_json.begin(); it != gameObjects_json.end(); ++it, i++)
	{
		AddGameObject(serializer.ImportGameObject((*it), globalAmbient, i));
	}

	std::cout << serializer.GetScripts();
}

void GameScene::ExportToFile(std::string filename)
{
	json json_object;
	json game_objects_json;

	json_object["scene"]["globalAmbient"]["x"] = globalAmbient.x;
	json_object["scene"]["globalAmbient"]["y"] = globalAmbient.y;
	json_object["scene"]["globalAmbient"]["z"] = globalAmbient.z;

	for (int i = 0; i < gameObjects.size(); i++)
	{
		game_objects_json.push_back(serializer.ExportGameObject(gameObjects.at(i)));
	}

	json_object["scene"]["gameObjects"] = game_objects_json;

	std::ofstream file(filename);
	if (file.is_open())
	{
		file << json_object.dump();
		file.close();
	}
}
