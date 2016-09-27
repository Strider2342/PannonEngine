#include "Scene1.h"

Scene1::Scene1()
{ }

void Scene1::Start()
{
	camera.Init();
	SetMainCamera(&camera);
	mainCamera->GetTransform()->GetPosition() = DirectX::XMFLOAT3(0.0f, 0.0f, -3.0f);

	test.Init(graphics.GetDevice(), graphics.GetDeviceContext());
	teapot.Init(graphics.GetDevice(), graphics.GetDeviceContext());

	gameObjects.push_back(&test);
	gameObjects.push_back(&teapot);

	teapot.AddComponent<MeshRenderer>();
	teapot.GetComponent<MeshRenderer>()->Init(graphics.GetDevice(), graphics.GetDeviceContext());
	teapot.GetComponent<MeshRenderer>()->SetTransform(teapot.GetTransform());
	teapot.GetComponent<MeshRenderer>()->SetCamera(mainCamera);

	teapot.GetTransform()->GetRotation() = DirectX::XMFLOAT3(AI_MATH_PI / 2, 0.0f, 0.0f);
	teapot.GetTransform()->MultiplyScale(0.025f);

	test.AddComponent<Beka>();

	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Start();
	}
}

void Scene1::Load()
{
	ContentManager content = ContentManager();
	content.Init(graphics.GetDevice(), graphics.GetDeviceContext());
		
	teapot.GetTransform()->SetParent(test.GetTransform());
	teapot.GetComponent<MeshRenderer>()->SetMesh(content.LoadMesh("Meshes/miniteapot.DAE"));
}

void Scene1::Update()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Update(gameTime);
	}

	if (Input::GetKeyDown(KeyCode::G))
	{
		std::cout << (float)gameTime.GetDeltaTime() << std::endl;
	}

	Scene::Update();
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