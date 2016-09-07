#include "Scene1.h"

Scene1::Scene1()
{ }

void Scene1::Load()
{
	camera.Init();
	SetMainCamera(&camera);
	mainCamera->GetTransform()->GetPosition() = Vector3(0.0f, 0.0f, -3.0f);

	material = Material();
	material.Init(graphics.GetDevice(), graphics.GetDeviceContext());

	test.InitMesh(graphics.GetDevice(), graphics.GetDeviceContext());

	ContentManager content = ContentManager();
	
	test.GetMeshRenderer()->SetCamera(mainCamera);
	test.GetMeshRenderer()->SetMaterial(&material);
	test.SetMesh(content.LoadMesh("Meshes/miniteapot.DAE"));
	test.GetTransform()->MultiplyScale(0.025f);
}

void Scene1::Update()
{
	//test.GetTransform()->MultiplyScale(0.1f);
}

void Scene1::Draw()
{
	graphics.Begin();
	test.GetMeshRenderer()->Render();
	graphics.End();
}