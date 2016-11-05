#include "EditorScene.h"

EditorScene::EditorScene()
{ }

void EditorScene::LoadScene(GameScene *scene)
{
}

void EditorScene::Start()
{
	ContentManager content = ContentManager();
	content.Init(graphics.GetDevice(), graphics.GetDeviceContext());

	Mesh *mesh = content.LoadMesh("Meshes/microteapot.DAE");
	Mesh *mesh2 = content.LoadMesh("Meshes/minisorosuveg.DAE");

	ImGui_ImplDX11_Init(graphics.GetHWND(), graphics.GetDevice(), graphics.GetDeviceContext());
	
	camera = GameObject();
	light = GameObject();
	teapot = GameObject();
	bottle = GameObject();

	gameObjects.push_back(&camera);
	gameObjects.push_back(&teapot);
	gameObjects.push_back(&bottle);
	gameObjects.push_back(&light);
	
	camera.SetName("Main Camera");
	camera.AddComponent<Camera>();
	camera.GetComponent<Camera>()->Init();
	camera.GetComponent<Camera>()->SetTransform(camera.GetTransform());
	camera.AddComponent<Light>();
	camera.GetComponent<Light>()->SetType(1);
	camera.GetTransform()->GetPosition() = DirectX::XMFLOAT3(0.0f, 0.0f, -25.0f);
	camera.GetTransform()->GetRotation() = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);

	SetMainCamera(camera.GetComponent<Camera>());

	light.SetName("Directional Light");
	light.AddComponent<Light>();
	light.GetComponent<Light>()->SetType(1);
	light.GetTransform()->GetPosition() = DirectX::XMFLOAT3(0.0f, -10.3f, 0.0f);

	teapot.SetName("Teapot");
	teapot.GetTransform()->GetPosition() = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	teapot.GetTransform()->GetRotation() = DirectX::XMFLOAT3(-DirectX::XM_PI * 0.5f, 0.0f, 0.0f);
	teapot.GetTransform()->MultiplyScale(0.25f);
	teapot.AddComponent<MeshRenderer>();
	teapot.GetComponent<MeshRenderer>()->Init(graphics.GetDevice(), graphics.GetDeviceContext());
	teapot.GetComponent<MeshRenderer>()->SetCamera(mainCamera);
	teapot.GetComponent<MeshRenderer>()->SetMesh(mesh);
	teapot.AddComponent<BoxCollider>();
	teapot.AddComponent<SphereCollider>();

	bottle.SetName("Bottle");
	bottle.GetTransform()->SetParent(teapot.GetTransform());
	bottle.GetTransform()->GetPosition() = DirectX::XMFLOAT3(10.0f, 0.5f, 0.0f);
	bottle.GetTransform()->GetRotation() = DirectX::XMFLOAT3(-DirectX::XM_PI * 0.5f, 0.0f, 0.0f);
	bottle.GetTransform()->MultiplyScale(0.05f);	
	bottle.AddComponent<MeshRenderer>();
	bottle.GetComponent<MeshRenderer>()->Init(graphics.GetDevice(), graphics.GetDeviceContext());
	bottle.GetComponent<MeshRenderer>()->SetCamera(mainCamera);
	bottle.GetComponent<MeshRenderer>()->SetMesh(mesh2);

	gui.SetGameObjectList(&gameObjects);

	selected = &teapot;
	gui.SetSelected(selected);

	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Start();
	}
}

void EditorScene::PreUpdate()
{
	RefreshLights();
}

void EditorScene::Update()
{

}

void EditorScene::PostUpdate()
{
}

void EditorScene::Render()
{
	gui.AssembleGUI();
	graphics.Begin(0.3f, 0.3f, 0.3f);

	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Render();
	}

	gui.Render();
	graphics.End();
}

void EditorScene::PostRender()
{
}
