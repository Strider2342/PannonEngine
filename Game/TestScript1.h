#pragma once
#include "GameTime.h"
#include "Transform.h"
#include "Light.h"

class TestScript1 : public Script<TestScript1>
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

	void Update(GameTime gameTime, Input input)
	{
		if (input.GetKeyDown(KeyCode::LeftArrow))
		{
			transform->GetLocalPosition().x -= speed * gameTime.GetDeltaTime();
		}
		else if (input.GetKeyDown(KeyCode::RightArrow))
		{
			transform->GetLocalPosition().x += speed * gameTime.GetDeltaTime();
		}

		if (input.GetKeyDown(KeyCode::UpArrow))
		{
			transform->GetLocalPosition().y += speed * gameTime.GetDeltaTime();
		}
		else if (input.GetKeyDown(KeyCode::DownArrow))
		{
			transform->GetLocalPosition().y -= speed * gameTime.GetDeltaTime();
		}

		if (input.GetKeyDown(KeyCode::Plus))
		{
			transform->GetLocalPosition().z += speed * gameTime.GetDeltaTime();
		}
		else if (input.GetKeyDown(KeyCode::Minus))
		{
			transform->GetLocalPosition().z -= speed * gameTime.GetDeltaTime();
		}

		if (input.GetKeyDown(KeyCode::U))
		{
			transform->GetLocalRotation().y += speed * gameTime.GetDeltaTime();
		}
		else if (input.GetKeyDown(KeyCode::I))
		{
			transform->GetLocalRotation().y -= speed * gameTime.GetDeltaTime();
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

	std::string GetName()
	{
		return Script::classname;
	}
};