#pragma once
#include "Script.h"

class CameraScript : public Script<CameraScript>
{
	float speed = 2.5f;

public:
	CameraScript()
	{

	}

	void Start()
	{
		
	}

	void Update(GameTime gameTime, Input input)
	{
		if (input.GetKeyDown(KeyCode::W))
		{
			gameObject->GetTransform()->GetPosition().z += speed * gameTime.GetDeltaTime();
		}
		else if (input.GetKeyDown(KeyCode::S))
		{
			gameObject->GetTransform()->GetPosition().z -= speed * gameTime.GetDeltaTime();
		}

		/*if (input.GetMouseButtonDown(MouseButton::LeftButton))
		{
			DirectX::XMFLOAT2 delta = input.GetDeltaPosition();
			DirectX::XMFLOAT3 rotation = gameObject->GetTransform()->GetRotation();
			gameObject->GetTransform()->GetRotation() = DirectX::XMFLOAT3(rotation.x - delta.x * 0.0005f, rotation.y + delta.x * 0.0005f, rotation.z);
		}*/

		/*if (Input::GetKeyDown(KeyCode::LeftArrow))
		{
			gameObject->GetTransform()->GetRotation().y += speed * gameTime.GetDeltaTime();
		}
		else if (Input::GetKeyDown(KeyCode::RightArrow))
		{
			gameObject->GetTransform()->GetRotation().y -= speed * gameTime.GetDeltaTime();
		}*/

		/*Hit hit = gameObject->GetComponent<Physics>()->RayCast(gameObject->GetTransform()->GetPosition(), gameObject->GetTransform()->GetForward());

		if (hit.hitOccured)
		{
			std::cout << "Camera RayCast hit occured!" << std::endl;
		}*/
	}
};