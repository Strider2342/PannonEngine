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

	void Update(GameTime gameTime, Input input)
	{
		if (input.GetMouseButtonDown(MouseButton::LeftButton))
		{
			Ray ray = screen->ScreenPointToRay(input.GetMousePosition());
			Hit hit = gameObject->GetComponent<Physics>()->RayPicking(ray);

			if (hit.hitOccured)
			{
				hit.gameObject->OnCollision();
				//std::cout << "Hit: x: " << hit.position.x << " y: " << hit.position.y << std::endl;
			}
		}
	}
};