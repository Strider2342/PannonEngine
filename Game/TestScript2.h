#pragma once
#include "GameTime.h"
#include "Transform.h"
#include "Light.h"

class TestScript2 : public Script
{
private:
	Transform *transform;

	Light *light;

	float speed = 0.9f;

public:
	TestScript2() {}

	void Start()
	{
		transform = gameObject->GetTransform();
		light = gameObject->GetComponent<Light>();
	}

	void Update(GameTime gameTime)
	{
		if (Input::GetKeyDown(KeyCode::A))
		{
			transform->GetPosition().x += speed * gameTime.GetDeltaTime();
		}
		else if (Input::GetKeyDown(KeyCode::D))
		{
			transform->GetPosition().x -= speed * gameTime.GetDeltaTime();
		}

		if (Input::GetKeyDown(KeyCode::W))
		{
			transform->GetPosition().y -= speed * gameTime.GetDeltaTime();
		}
		else if (Input::GetKeyDown(KeyCode::S))
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