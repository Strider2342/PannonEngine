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

	//gameObjects.push_back(&camera);

	camera.SetName("Main Camera");
	camera.AddComponent<Camera>();
	camera.GetComponent<Camera>()->Init();
	camera.GetComponent<Camera>()->SetTransform(camera.GetTransform());
	camera.AddComponent<Light>();
	camera.GetComponent<Light>()->SetType(1);
	camera.GetTransform()->GetPosition() = DirectX::XMFLOAT3(0.0f, 0.0f, -25.0f);
	camera.GetTransform()->GetRotation() = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	SetMainCamera(camera.GetComponent<Camera>());

	ImportFromFile("scene2.scn");

	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects.at(i)->GetComponent<MeshRenderer>() != nullptr)
		{
			gameObjects.at(i)->GetComponent<MeshRenderer>()->Init(graphics.GetDevice(), graphics.GetDeviceContext());
		}
		if (gameObjects.at(i)->GetName() == "Main Camera")
		{
			SetMainCamera(gameObjects[0]->GetComponent<Camera>());
		}
	}
	
	SetSceneProperties();

	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Start();
	}
}

void EditorScene::PreUpdate()
{
	RefreshLights();
	SetSceneProperties();
	//RefreshCamera();
}

void EditorScene::Update()
{

}

void EditorScene::PostUpdate()
{
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
