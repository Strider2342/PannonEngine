#include "Scene2.h"

Scene2::Scene2()
{ }

void Scene2::Start()
{
	camera.AddComponent<Camera>();
	camera.GetComponent<Camera>()->Init();
	camera.GetComponent<Camera>()->SetTransform(camera.GetTransform());
	SetMainCamera(camera.GetComponent<Camera>());
	mainCamera->GetTransform()->GetPosition() = DirectX::XMFLOAT3(0.0f, 0.0f, -3.0f);

	gameObjects.push_back(&camera);
	gameObjects.push_back(&test);

	test.SetName("Object 1");
	test.AddComponent<MeshRenderer>();
	test.GetComponent<MeshRenderer>()->Init(graphics.GetDevice(), graphics.GetDeviceContext());
	test.GetComponent<MeshRenderer>()->SetTransform(test.GetTransform());
	test.GetComponent<MeshRenderer>()->SetCamera(mainCamera);

	test.GetTransform()->MultiplyScale(0.0025f);
	test.GetTransform()->GetRotation() = DirectX::XMFLOAT3(AI_MATH_PI / 2, 0.0f, 0.0f);

	test.AddComponent<SphereCollider>();
	test.GetComponent<SphereCollider>()->SetRadius(12.0f);
	
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Start();
	}
}

void Scene2::Load()
{
	ContentManager content = ContentManager();
	content.Init(graphics.GetDevice(), graphics.GetDeviceContext());

	Mesh *mesh = content.LoadMesh("Meshes/minisorosuveg.DAE");

	test.GetComponent<MeshRenderer>()->SetMesh(mesh);
}

void Scene2::Update()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Update(gameTime);
	}
}

void Scene2::Render()
{
	graphics.Begin();

	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Render();
	}

	graphics.End();
}