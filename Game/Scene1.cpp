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
	light1.GetTransform()->GetPosition() = DirectX::XMFLOAT3(2.0f, 0.0f, -0.3f);

	/*light2.AddComponent<Light>();
	light2.GetComponent<Light>()->SetTransform(light2.GetTransform());
	light2.GetTransform()->GetPosition() = DirectX::XMFLOAT3(-2.0f, 0.0f, -1.0f);*/

	gameObjects.push_back(&camera);
	gameObjects.push_back(&light1);
	gameObjects.push_back(&light2);
	gameObjects.push_back(&test);
	gameObjects.push_back(&teapot);

	teapot.AddComponent<MeshRenderer>();
	teapot.GetComponent<MeshRenderer>()->Init(graphics.GetDevice(), graphics.GetDeviceContext());
	teapot.GetComponent<MeshRenderer>()->SetTransform(teapot.GetTransform());
	teapot.GetComponent<MeshRenderer>()->SetCamera(mainCamera);
	
	teapot.AddComponent<BoxCollider>();

	teapot.GetTransform()->GetRotation() = DirectX::XMFLOAT3(AI_MATH_PI / 2, 0.0f, 0.0f);
	teapot.GetTransform()->MultiplyScale(0.025f);

	light1.AddComponent<Beka>();

	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Start();
	}
	
	BoxCollider *coll = new BoxCollider();
	coll->SetCenter(DirectX::XMFLOAT3(20000.0f, 20000.0f, 20000.0f));

	if (teapot.GetComponent<Collider>() != NULL)
	{
		if (dynamic_cast<BoxCollider *>(teapot.GetComponent<Collider>()))
		{
			if (dynamic_cast<BoxCollider *>(teapot.GetComponent<Collider>())->Colliding(coll->GetCollider()))
			{
				std::cout << dynamic_cast<BoxCollider *>(teapot.GetComponent<Collider>())->GetSize().x << std::endl;
			}
		}
		else if (dynamic_cast<SphereCollider *>(teapot.GetComponent<Collider>()))
		{

		}
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