#pragma once
#include "Transform.h"

class Beka : public Script
{
private:
	Transform *transform;

public:
	Beka() {}

	void Start()
	{
		transform = gameObject->GetTransform();
	}

	void Update()
	{
		if (Input::GetKeyDown(KeyCode::LeftArrow))
		{
			transform->GetPosition().x += 0.005f;
		}
		else if (Input::GetKeyDown(KeyCode::RightArrow))
		{
			transform->GetPosition().x -= 0.005f;
		}

		if (Input::GetKeyDown(KeyCode::UpArrow))
		{
			transform->GetPosition().y -= 0.005f;
		}
		else if (Input::GetKeyDown(KeyCode::DownArrow))
		{
			transform->GetPosition().y += 0.005f;
		}
	}
};