#pragma once
#include "Script.h"

class CameraScript : public Script
{
	float speed = 2.5f;

public:
	CameraScript()
	{

	}

	void Start()
	{
		
	}

	void Update(GameTime gameTime)
	{
		if (Input::GetKeyDown(KeyCode::W))
		{
			gameObject->GetTransform()->GetPosition().z += speed * gameTime.GetDeltaTime();
		}
		else if (Input::GetKeyDown(KeyCode::S))
		{
			gameObject->GetTransform()->GetPosition().z -= speed * gameTime.GetDeltaTime();
		}

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