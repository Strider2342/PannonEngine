#pragma once
#include "GameTime.h"
#include "Transform.h"
#include "Light.h"

class TestScript1 : public Script
{
private:
	Transform *transform;

	Light *light;

	float speed = 0.9f;

	bool colliding = false;

public:
	TestScript1() {}

	void Start()
	{
		transform = gameObject->GetTransform();
		light = gameObject->GetComponent<Light>();
	}

	void Update(GameTime gameTime)
	{
		std::cout << colliding << std::endl;
		if (!colliding)
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

		colliding = false;

		/*transform->GetPosition().x = cos(gameTime.GetElapsedTime()) / 2.0f;
		transform->GetPosition().y = sin(gameTime.GetElapsedTime()) / 2.0f;*/
	}

	void OnCollision()
	{
		colliding = true;
	}
};