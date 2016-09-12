#include "Scene1.h"

Scene1::Scene1()
{ }

void Scene1::Load()
{
	camera.Init();
	SetMainCamera(&camera);
	mainCamera->GetTransform()->GetPosition() = DirectX::XMFLOAT3(0.0f, 0.0f, -3.0f);

	material = Material();
	material.Init(graphics.GetDevice(), graphics.GetDeviceContext());

	test.InitMesh(graphics.GetDevice(), graphics.GetDeviceContext());
	teapot.InitMesh(graphics.GetDevice(), graphics.GetDeviceContext());

	ContentManager content = ContentManager();
	content.Init(graphics.GetDevice(), graphics.GetDeviceContext());
	
	material.SetTexture(content.LoadTexture("defaulttexture.png"));

	test.GetMeshRenderer()->SetCamera(mainCamera);
	test.GetMeshRenderer()->SetMaterial(&material);

	teapot.GetMeshRenderer()->SetCamera(mainCamera);
	teapot.GetTransform()->SetParent(test.GetTransform());
	teapot.GetMeshRenderer()->SetMaterial(&material);
	teapot.SetMesh(content.LoadMesh("Meshes/miniteapot.DAE"));
	teapot.GetTransform()->GetRotation() = DirectX::XMFLOAT3(AI_MATH_PI / 2, 0.0f, 0.0f);
	teapot.GetTransform()->MultiplyScale(0.025f);
}

void Scene1::Update()
{
	test.GetTransform()->GetRotation().y = test.GetTransform()->GetRotation().y + 0.005f;
	//std::cout << DebugHelper::XMFLOAT3ToString(mainCamera->GetTransform()->GetForward()) << std::endl;
	std::cout << DebugHelper::XMFLOAT3ToString(test.GetTransform()->GetRight()) << std::endl;
}

void Scene1::Draw()
{
	graphics.Begin();
	teapot.GetMeshRenderer()->Render();
	graphics.End();
}