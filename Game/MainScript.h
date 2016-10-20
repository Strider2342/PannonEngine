#pragma once
#include "Script.h"
#include "Physics.h"

class MainScript : public Script
{

public:
	Screen *screen;

	MainScript()
	{

	}

	void Update(GameTime gameTime)
	{
		if (Input::GetMouseButtonDown(MouseButton::LeftButton))
		{
			Ray ray = screen->ScreenPointToRay(Input::GetMousePosition());
			Hit hit = gameObject->GetComponent<Physics>()->RayCast(ray);

			if (hit.hitOccured)
			{
				hit.gameObject->OnCollision();
				//std::cout << "RayCast hit occured!" << std::endl;
			}
			/*std::cout << "Origin: " << ray.GetOrigin().x << ":" << ray.GetOrigin().y << ":" << ray.GetOrigin().z << std::endl;
			std::cout << "Direction: " << ray.GetDirection().x << ":" << ray.GetDirection().y << ":" << ray.GetDirection().z << std::endl;*/
		}
	}
};