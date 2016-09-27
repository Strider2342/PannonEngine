#pragma once
#include "GameTime.h"
#include "Transform.h"

class Beka : public Script
{
private:
	Transform *transform;

	float speed = 0.5f;

public:
	Beka() {}

	void Start()
	{
		transform = gameObject->GetTransform();
	}

	void Update(GameTime gameTime)
	{
		if (Input::GetKeyDown(KeyCode::LeftArrow))
		{
			transform->GetPosition().x += speed * gameTime.GetDeltaTime();
		}
		else if (Input::GetKeyDown(KeyCode::RightArrow))
		{
			transform->GetPosition().x -= speed * gameTime.GetDeltaTime();
		}

		if (Input::GetKeyDown(KeyCode::UpArrow))
		{
			transform->GetPosition().y -= speed * gameTime.GetDeltaTime();
		}
		else if (Input::GetKeyDown(KeyCode::DownArrow))
		{
			transform->GetPosition().y += speed * gameTime.GetDeltaTime();
		}
	}
};