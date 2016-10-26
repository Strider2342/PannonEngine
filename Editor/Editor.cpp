#include "Editor.h"

Editor::Editor()
{ }

void Editor::Init(EditorGraphics *graphics)
{
	this->graphics = graphics;

	gameObjects = std::vector<GameObject *>();
	lights = std::vector<Light::ShaderInput>();

	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize.x = 1706;
	io.DisplaySize.y = 960;

	ImGui_ImplDX11_Init(graphics->GetHWND(), graphics->GetDevice(), graphics->GetDeviceContext());

	camera = new GameObject();
	camera->SetName("Main Camera");
	camera->AddComponent<Camera>();
	camera->GetComponent<Camera>()->Init();
	camera->GetComponent<Camera>()->SetTransform(camera->GetTransform());
	camera->GetTransform()->GetPosition() = DirectX::XMFLOAT3(0.0f, 0.0f, 4.0f);
	camera->GetTransform()->GetRotation() = DirectX::XMFLOAT3(0.0f, DirectX::XM_PI, 0.0f);

	light = new GameObject();
	light->SetName("Directional Light");
	light->AddComponent<Light>();
	//light->GetComponent<Light>()->SetType(0);
	//light->GetTransform()->GetRotation() = DirectX::XMFLOAT3(4.0f, 4.0f, 4.0f);

	teapot = new GameObject();
	teapot->SetName("Teapot");
	teapot->GetTransform()->GetPosition() = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	teapot->AddComponent<MeshRenderer>();

	teapot->GetTransform()->MultiplyScale(0.025f);

	teapot->AddComponent<Camera>();
	teapot->GetComponent<Camera>()->SetFOV(75.0f);
	teapot->GetComponent<Camera>()->SetNearClippingPlane(0.1f);
	teapot->GetComponent<Camera>()->SetFarClippingPlane(1000.0f);

	teapot->AddComponent<BoxCollider>();
	teapot->AddComponent<SphereCollider>();

	bottle = new GameObject();
	bottle->SetName("Bottle");
	bottle->GetTransform()->GetPosition() = DirectX::XMFLOAT3(1.0f, 0.5f, 0.0f);
	bottle->AddComponent<MeshRenderer>();

	bottle->GetTransform()->MultiplyScale(0.005f);

	ContentManager content = ContentManager();
	content.Init(graphics->GetDevice(), graphics->GetDeviceContext());

	Mesh *mesh = content.LoadMesh("Meshes/microteapot.DAE");
	teapot->GetComponent<MeshRenderer>()->Init(graphics->GetDevice(), graphics->GetDeviceContext());
	teapot->GetComponent<MeshRenderer>()->SetCamera(camera->GetComponent<Camera>());
	teapot->GetComponent<MeshRenderer>()->SetMesh(mesh);
	teapot->GetComponent<MeshRenderer>()->SetLights(&lights);

	Mesh *mesh2 = content.LoadMesh("Meshes/minisorosuveg.DAE");
	bottle->GetComponent<MeshRenderer>()->Init(graphics->GetDevice(), graphics->GetDeviceContext());
	bottle->GetComponent<MeshRenderer>()->SetCamera(camera->GetComponent<Camera>());
	bottle->GetComponent<MeshRenderer>()->SetMesh(mesh2);
	bottle->GetComponent<MeshRenderer>()->SetLights(&lights);

	gameObjects.push_back(camera);
	gameObjects.push_back(teapot);
	gameObjects.push_back(bottle);
	gameObjects.push_back(light);

	gui.SetGameObjectList(&gameObjects);

	selected = teapot;
	gui.SetSelected(selected);
}

void Editor::Start()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Start();
	}
}

void Editor::Load()
{ }

void Editor::Update()
{
	RefreshLights();

	//std::cout << Input::GetMousePosition().x << " : " << Input::GetMousePosition().y << std::endl;
}

void Editor::Draw()
{
	gui.AssembleGUI();
	graphics->Begin();

	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Render();
	}

	ImGui::Render();

	graphics->End();
}

void Editor::RefreshLights()
{
	lights.clear();

	for (int i = 0; i < gameObjects.size(); i++)
	{
		Light *light = gameObjects[i]->GetComponent<Light>();
		if (light)
		{
			Light::ShaderInput input = light->GetShaderInput();
			lights.push_back(input);
		}
	}

	for (int i = 0; i < gameObjects.size(); i++)
	{
		MeshRenderer *renderer = gameObjects[i]->GetComponent<MeshRenderer>();
		if (renderer)
		{
			renderer->SetLights(&lights);
		}
	}
}