#include "Scene1.h"

Scene1::Scene1()
{ }

void Scene1::Load()
{
	camera.Init();
	SetMainCamera(&camera);
	mainCamera->GetTransform()->GetPosition() = Vector3(0.0f, 0.0f, -3.0f);
	//mainCamera->GetTransform()->GetRotation() = Vector3(3.14f, 3.14f, 0.0f);

	material = Material();
	material.Init(graphics.GetDevice(), graphics.GetDeviceContext());

	test.InitMesh(graphics.GetDevice(), graphics.GetDeviceContext());

	ContentManager content = ContentManager();
	
	test.GetMeshRenderer()->SetCamera(mainCamera);
	test.GetMeshRenderer()->SetMaterial(&material);
	test.SetMesh(content.LoadMesh("Meshes/miniteapot.DAE"));
	//test.GetTransform()->GetRotation() = Vector3(3.14f, 1.57f, 0.0f);
	test.GetTransform()->MultiplyScale(0.025f);
}

void Scene1::Update()
{
	//test.GetTransform()->GetRotation().SetX(test.GetTransform()->GetRotation().GetX() + 0.01f);
	test.GetTransform()->GetRotation().SetY(test.GetTransform()->GetRotation().GetY() + 0.0005f);
	std::cout << test.GetTransform()->GetForward().ToString() << std::endl;

	//test.GetTransform()->MultiplyScale(0.1f);
}

void Scene1::Draw()
{
	graphics.Begin();
	test.GetMeshRenderer()->Render();
	graphics.End();
}