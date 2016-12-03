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
	//gameObjects.push_back(&teapot2);

	main.AddComponent<MainScript>();
	main.GetComponent<MainScript>()->screen = &screen;

	//main.AddComponent<RayCaster>();
	//main.GetComponent<RayCaster>()->SetGameObjectArray(&gameObjects);

	camera.AddComponent<Camera>();
	camera.GetComponent<Camera>()->Init();
	camera.GetComponent<Camera>()->SetTransform(camera.GetTransform());
	SetMainCamera(camera.GetComponent<Camera>());
	camera.GetTransform()->GetPosition() = DirectX::XMFLOAT3(0.0f, 0.0f, -4.0f);
	//camera.AddComponent<RayCaster>();
	//camera.GetComponent<RayCaster>()->SetGameObjectArray(&gameObjects);
	//camera.GetTransform()->GetRotation() = DirectX::XMFLOAT3(0.0f, 3.14f, 0.0f);

	screen.SetCamera(camera.GetComponent<Camera>());

	light1.AddComponent<Light>();
	light1.GetComponent<Light>()->SetType(0);
	light1.GetTransform()->GetPosition() = DirectX::XMFLOAT3(0.0f, 0.0f, -1.3f);

	/*light2.AddComponent<Light>();
	light2.GetTransform()->GetPosition() = DirectX::XMFLOAT3(-2.0f, 0.0f, -1.0f);*/

	//camera.AddComponent<CameraScript>();

	teapot.SetName("Object 1");
	teapot.SetGameObjects(&gameObjects);
	//teapot.AddComponent<RayCaster>();
	//teapot.GetComponent<RayCaster>()->SetGameObjectArray(&gameObjects);

	teapot.AddComponent<MeshRenderer>();
	teapot.GetComponent<MeshRenderer>()->Init(graphics.GetDevice(), graphics.GetDeviceContext());
	teapot.GetComponent<MeshRenderer>()->SetCamera(mainCamera);
	
	teapot.GetTransform()->MultiplyScale(0.025f);
	//teapot.GetTransform()->GetPosition() = DirectX::XMFLOAT3(0.0f, 0.15f, 0.0f);
	teapot.GetTransform()->GetRotation() = DirectX::XMFLOAT3(-AI_MATH_PI / 2, 0.0f, 0.0f);

	teapot.AddComponent<SphereCollider>();
	teapot.GetComponent<SphereCollider>()->SetRadius(16.0f);

	teapot.AddComponent<AgingObject>();

	//std::cout << teapot.GetComponent<TestScript1>()->ScriptName();

	/*teapot2.SetName("Object 2");
	teapot2.AddComponent<RayCaster>();
	teapot2.GetComponent<RayCaster>()->SetGameObjectArray(&gameObjects);

	teapot2.AddComponent<MeshRenderer>();
	teapot2.GetComponent<MeshRenderer>()->Init(graphics.GetDevice(), graphics.GetDeviceContext());
	teapot2.GetComponent<MeshRenderer>()->SetCamera(mainCamera);
	//teapot2.GetComponent<MeshRenderer>()->GetMaterial()->SetDiffuse(0.0f, 1.0f, 0.0f);

	//teapot2.GetTransform()->GetPosition() = DirectX::XMFLOAT3(-1.5f, 0.25f, 0.0f);
	//teapot2.GetTransform()->GetRotation() = DirectX::XMFLOAT3(-AI_MATH_PI / 2, 0.0f, 0.0f);
	//teapot2.GetTransform()->MultiplyScale(0.025f);

	teapot2.AddComponent<SphereCollider>();
	teapot2.GetComponent<SphereCollider>()->SetRadius(16.0f);	

	teapot2.AddComponent<TestScript2>();*/


	ContentManager content = ContentManager();
	content.Init(graphics.GetDevice(), graphics.GetDeviceContext());

	Mesh *mesh = content.LoadMesh("Meshes/microteapot.DAE");

	teapot.GetTransform()->SetParent(test.GetTransform());
	teapot.GetComponent<MeshRenderer>()->SetMesh(mesh);
	teapot.GetComponent<MeshRenderer>()->GetMaterial()->SetTexture(content.LoadTexture("defaulttexture.jpg"));

	//teapot2.GetTransform()->SetParent(teapot.GetTransform());
	//teapot2.GetComponent<MeshRenderer>()->SetMesh(mesh);


	GameScene::Start();
}