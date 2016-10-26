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
			Hit hit = gameObject->GetComponent<Physics>()->RayPicking(ray);

			if (hit.hitOccured)
			{
				hit.gameObject->OnCollision();
			}
		}
	}
};