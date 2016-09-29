#pragma once
#include "GameTime.h"
#include "Transform.h"
#include "Light.h"

class Beka : public Script
{
private:
	Transform *transform;

	Light *light;

	float speed = 0.9f;

public:
	Beka() {}

	void Start()
	{
		transform = gameObject->GetTransform();
		light = gameObject->GetComponent<Light>();
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

		if (Input::GetKeyDown(KeyCode::Plus))
		{
			transform->GetPosition().z += speed * gameTime.GetDeltaTime();
		}
		else if (Input::GetKeyDown(KeyCode::Minus))
		{
			transform->GetPosition().z -= speed * gameTime.GetDeltaTime();
		}
	}
};