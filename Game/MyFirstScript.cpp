#include "MyFirstScript.h"

MyFirstScript::MyFirstScript()
{ }

void MyFirstScript::Start()
{
	std::cout << "My first fucking script just fucking started!!!" << std::endl;
}

void MyFirstScript::Update(GameTime gameTime, Input input)
{
	gameObject->GetTransform()->GetRotation().y = gameObject->GetTransform()->GetRotation().y + 0.0005f;
}
