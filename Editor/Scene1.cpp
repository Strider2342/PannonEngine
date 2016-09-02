#include "Scene1.h"

Scene1::Scene1()
{ }

void Scene1::Load()
{
	
}

void Scene1::Update()
{
	std::cout << test.GetTransform()->GetPosition().ToString() << std::endl;
	test.GetTransform()->SetPosition(Vector3(test.GetTransform()->GetPosition().GetX() + 0.1f, test.GetTransform()->GetPosition().GetY(), test.GetTransform()->GetPosition().GetZ()));
}

void Scene1::Draw()
{
	graphics.Begin();

	graphics.End();
}