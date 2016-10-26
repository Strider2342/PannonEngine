#include "Scene1.h"

Scene1::Scene1()
{ }

void Scene1::Start()
{
	HWND hWnd = graphics.GetHWND();
	RECT rect;
	GetClientRect(hWnd, &rect);
	DirectX::XMFLOAT2 windowClientSize = DirectX::XMFLOAT2(rect.right - rect.left, rect.bottom - rect.top);

	screen = Screen(windowClientSize.x, windowClientSize.y);

	gameObjects.push_back(&main);
	gameObjects.push_back(&camera);
	gameObjects.push_back(&light1);
	gameObjects.push_back(&light2);
	gameObjects.push_back(&test);
	gameObjects.push_back(&teapot);
	gameObjects.push_back(&teapot2);

	main.AddComponent<MainScript>();
	main.GetComponent<MainScript>()->screen = &screen;

	main.AddComponent<Physics>();
	main.GetComponent<Physics>()->SetGameObjectArray(&gameObjects);

	camera.AddComponent<Camera>();
	camera.GetComponent<Camera>()->Init();
	camera.GetComponent<Camera>()->SetTransform(camera.GetTransform());
	SetMainCamera(camera.GetComponent<Camera>());
	camera.GetTransform()->GetPosition() = DirectX::XMFLOAT3(0.0f, 0.0f, -3.0f);
	camera.AddComponent<Physics>();
	camera.GetComponent<Physics>()->SetGameObjectArray(&gameObjects);
	//camera.GetTransform()->GetRotation() = DirectX::XMFLOAT3(0.0f, 3.14f, 0.0f);

	screen.SetCamera(camera.GetComponent<Camera>());

	light1.AddComponent<Light>();
	light1.GetTransform()->GetPosition() = DirectX::XMFLOAT3(0.0f, 0.0f, -1.3f);

	/*light2.AddComponent<Light>();
	light2.GetTransform()->GetPosition() = DirectX::XMFLOAT3(-2.0f, 0.0f, -1.0f);*/

	camera.AddComponent<CameraScript>();

	teapot.SetName("Object 1");
	teapot.AddComponent<Physics>();
	teapot.GetComponent<Physics>()->SetGameObjectArray(&gameObjects);

	teapot.AddComponent<MeshRenderer>();
	teapot.GetComponent<MeshRenderer>()->Init(graphics.GetDevice(), graphics.GetDeviceContext());
	teapot.GetComponent<MeshRenderer>()->SetCamera(mainCamera);
	
	teapot.GetTransform()->MultiplyScale(0.025f);
	teapot.GetTransform()->GetPosition() = DirectX::XMFLOAT3(0.0f, 0.15f, 0.0f);
	teapot.GetTransform()->GetRotation() = DirectX::XMFLOAT3(AI_MATH_PI / 2, 0.0f, 0.0f);

	teapot.AddComponent<SphereCollider>();
	teapot.GetComponent<SphereCollider>()->SetRadius(16.0f);

	teapot.AddComponent<TestScript1>();

	teapot2.SetName("Object 2");
	teapot2.AddComponent<Physics>();
	teapot2.GetComponent<Physics>()->SetGameObjectArray(&gameObjects);

	teapot2.AddComponent<MeshRenderer>();
	teapot2.GetComponent<MeshRenderer>()->Init(graphics.GetDevice(), graphics.GetDeviceContext());
	teapot2.GetComponent<MeshRenderer>()->SetCamera(mainCamera);
	//teapot2.GetComponent<MeshRenderer>()->GetMaterial()->SetDiffuse(0.0f, 1.0f, 0.0f);

	teapot2.GetTransform()->GetPosition() = DirectX::XMFLOAT3(-1.0f, 0.15f, 0.0f);
	teapot2.GetTransform()->GetRotation() = DirectX::XMFLOAT3(AI_MATH_PI / 2, 0.0f, 0.0f);
	teapot2.GetTransform()->MultiplyScale(0.025f);

	teapot2.AddComponent<SphereCollider>();
	teapot2.GetComponent<SphereCollider>()->SetRadius(16.0f);	

	//teapot2.AddComponent<TestScript1>();

	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Start();
	}
	
	std::string json;
	std::cout << "kujhuki: ";
	std::cin >> json;
	teapot.GetTransform()->Import(json);
	std::cout << teapot.GetTransform()->Export() << std::endl;
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

void Scene1::Render()
{
	graphics.Begin();

	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Render();
	}

	graphics.End();
}