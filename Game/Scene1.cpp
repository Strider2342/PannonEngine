#include "Scene1.h"

Scene1::Scene1()
{ }

void Scene1::Start()
{
	camera.AddComponent<Camera>();
	camera.GetComponent<Camera>()->Init();
	camera.GetComponent<Camera>()->SetTransform(camera.GetTransform());
	SetMainCamera(camera.GetComponent<Camera>());
	mainCamera->GetTransform()->GetPosition() = DirectX::XMFLOAT3(0.0f, 0.0f, -3.0f);

	light1.AddComponent<Light>();
	light1.GetComponent<Light>()->SetTransform(light1.GetTransform());
	light1.GetTransform()->GetPosition() = DirectX::XMFLOAT3(0.0f, 0.0f, -1.3f);

	/*light2.AddComponent<Light>();
	light2.GetComponent<Light>()->SetTransform(light2.GetTransform());
	light2.GetTransform()->GetPosition() = DirectX::XMFLOAT3(-2.0f, 0.0f, -1.0f);*/

	gameObjects.push_back(&camera);
	gameObjects.push_back(&light1);
	gameObjects.push_back(&light2);
	gameObjects.push_back(&test);
	gameObjects.push_back(&teapot);
	gameObjects.push_back(&teapot2);

	teapot.SetName("Object 1");
	teapot.AddComponent<Physics>(&physics);

	teapot.AddComponent<MeshRenderer>();
	teapot.GetComponent<MeshRenderer>()->Init(graphics.GetDevice(), graphics.GetDeviceContext());
	teapot.GetComponent<MeshRenderer>()->SetTransform(teapot.GetTransform());
	teapot.GetComponent<MeshRenderer>()->SetCamera(mainCamera);
	
	teapot.GetTransform()->MultiplyScale(0.025f);
	teapot.GetTransform()->GetPosition() = DirectX::XMFLOAT3(1.25f, 0.23f, 0.0f);
	teapot.GetTransform()->GetRotation() = DirectX::XMFLOAT3(AI_MATH_PI / 2, 0.0f, 0.0f);

	teapot.AddComponent<SphereCollider>();
	teapot.GetComponent<SphereCollider>()->SetRadius(12.0f);

	teapot.AddComponent<TestScript1>();

	teapot2.SetName("Object 2");
	teapot2.AddComponent<MeshRenderer>();
	teapot2.GetComponent<MeshRenderer>()->Init(graphics.GetDevice(), graphics.GetDeviceContext());
	teapot2.GetComponent<MeshRenderer>()->SetTransform(teapot2.GetTransform());
	teapot2.GetComponent<MeshRenderer>()->SetCamera(mainCamera);
	//teapot2.GetComponent<MeshRenderer>()->GetMaterial()->SetDiffuse(0.0f, 1.0f, 0.0f);

	teapot2.GetTransform()->GetPosition() = DirectX::XMFLOAT3(-1.0f, 0.0f, 0.0f);
	teapot2.GetTransform()->GetRotation() = DirectX::XMFLOAT3(AI_MATH_PI / 2, 0.0f, 0.0f);
	teapot2.GetTransform()->MultiplyScale(0.025f);

	teapot2.AddComponent<SphereCollider>();
	teapot2.GetComponent<SphereCollider>()->SetRadius(12.0f);	

	teapot2.AddComponent<TestScript2>();

	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Start();
	}
}

void Scene1::Load()
{
	ContentManager content = ContentManager();
	content.Init(graphics.GetDevice(), graphics.GetDeviceContext());

	Mesh *mesh = content.LoadMesh("Meshes/microteapot.DAE");
		
	//teapot.GetTransform()->SetParent(test.GetTransform());
	teapot.GetComponent<MeshRenderer>()->SetMesh(mesh);

	//teapot2.GetTransform()->SetParent(test.GetTransform());
	teapot2.GetComponent<MeshRenderer>()->SetMesh(mesh);
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