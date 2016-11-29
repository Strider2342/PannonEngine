#include "EditorScene.h"

EditorScene::EditorScene()
{ }

void EditorScene::LoadScene(GameScene *scene)
{
}

void EditorScene::Start()
{
	gui->Init();
	
	ImGui_ImplDX11_Init(graphics.GetHWND(), graphics.GetDevice(), graphics.GetDeviceContext());
	
	camera = GameObject();
	cameraMain = GameObject();

	cameraMain.SetName("Main Camera");
	cameraMain.AddComponent<EditorCameraScript>();
	cameraMain.GetTransform()->SetPosition(DirectX::XMFLOAT3(0.0f, 0.0f, -15.0f));
	//cameraMain.GetTransform()->SetRotation(DirectX::XMFLOAT3(0.0f, DirectX::XM_PI / 4.0f, 0.0f));

	camera.SetName("Camera");
	camera.AddComponent<Camera>();
	camera.GetComponent<Camera>()->Init();
	camera.GetComponent<Camera>()->SetTransform(camera.GetTransform());
	cameraMain.GetTransform()->SetPosition(DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f));
	camera.GetTransform()->SetParent(cameraMain.GetTransform());
	SetMainCamera(camera.GetComponent<Camera>());

	cameraMain.Start();

	ImportFromFile("..\\Scenes\\proba.scn");

	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects.at(i)->GetComponent<MeshRenderer>() != nullptr)
		{
			gameObjects.at(i)->GetComponent<MeshRenderer>()->Init(graphics.GetDevice(), graphics.GetDeviceContext());
		}
		/*if (gameObjects.at(i)->GetName() == "Main Camera")
		{
			SetMainCamera(gameObjects[0]->GetComponent<Camera>());
		}*/
	}
	
	SetSceneProperties();

	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Start();
	}

	gameObjects[1]->AddComponent<EditorCameraScript>();
}

void EditorScene::PreUpdate()
{
	RefreshLights();
	SetSceneProperties();
	//RefreshCamera();
}

void EditorScene::Update()
{
	cameraMain.Update(gameTime, input);
	camera.Update(gameTime, input);
}

void EditorScene::Render()
{
	gui->AssembleGUI();
	graphics.Begin(0.3f, 0.3f, 0.3f);

	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Render();
	}

	gui->Render();
	graphics.End();
}

void EditorScene::PostRender()
{
}
