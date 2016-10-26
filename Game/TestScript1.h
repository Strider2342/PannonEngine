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

		if (Input::GetKeyDown(KeyCode::U))
		{
			transform->GetRotation().y += speed * gameTime.GetDeltaTime();
		}
		else if (Input::GetKeyDown(KeyCode::I))
		{
			transform->GetRotation().y -= speed * gameTime.GetDeltaTime();
		}

		colliding = false;

		/*Hit hit = gameObject->GetComponent<Physics>()->RayCast(gameObject->GetTransform()->GetPosition(), gameObject->GetTransform()->GetRight());

		if (hit.hitOccured)
		{
			std::cout << "RayCast hit occured!" << std::endl;
		}*/
	}

	void PostRender()
	{
		gameObject->GetComponent<MeshRenderer>()->GetMaterial()->SetDiffuse(0.4f, 0.4f, 0.4f);
	}

	void OnCollision()
	{
		colliding = true;
		gameObject->GetComponent<MeshRenderer>()->GetMaterial()->SetDiffuse(0.0f, 1.0f, 0.0f);

		//std::cout << "I'm hit!" << std::endl;
	}
};