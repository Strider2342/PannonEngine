#pragma once
#include "GameTime.h"
#include "Transform.h"
#include "Light.h"
#include "Physics.h"
#include "Collider.h"

class TestScript2 : public Script
{
private:
	Transform *transform;

	Light *light;

	float speed = 10.9f;

public:
	TestScript2() {}

	void Start()
	{
		transform = gameObject->GetTransform();
		light = gameObject->GetComponent<Light>();
	}

	void Update(GameTime gameTime, Input input)
	{
		Move(gameTime, input);
	}

	void Move(GameTime gameTime, Input input)
	{
		DirectX::XMFLOAT3 velocity = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);

		if (input.GetKeyDown(KeyCode::A))
		{
			velocity.x += speed * gameTime.GetDeltaTime();
		}
		else if (input.GetKeyDown(KeyCode::D))
		{
			velocity.x -= speed * gameTime.GetDeltaTime();
		}

		if (input.GetKeyDown(KeyCode::W))
		{
			velocity.y -= speed * gameTime.GetDeltaTime();
		}
		else if (input.GetKeyDown(KeyCode::S))
		{
			velocity.y += speed * gameTime.GetDeltaTime();
		}

		if (input.GetKeyDown(KeyCode::Plus))
		{
			velocity.z += speed * gameTime.GetDeltaTime();
		}
		else if (input.GetKeyDown(KeyCode::Minus))
		{
			velocity.z -= speed * gameTime.GetDeltaTime();
		}

		/*gameObject->GetTransform()->GetPosition().x += velocity.x;
		gameObject->GetTransform()->GetPosition().y += velocity.y;
		gameObject->GetTransform()->GetPosition().z += velocity.z;

		Collider *collider1 = gameObject->GetComponent<Collider>();
		bool colliding = false;
		for (int i = 0; i < gameObject->GetComponent<Physics>()->GetGameObjectArray()->size(); i++)
		{
			if ((*gameObject->GetComponent<Physics>()->GetGameObjectArray())[i] != gameObject)
			{
				if (collider1 != NULL)
				{

					Collider *collider2 = (*gameObject->GetComponent<Physics>()->GetGameObjectArray())[i]->GetComponent<Collider>();

					if (collider2 != NULL)
					{
						if (dynamic_cast<BoxCollider *>(collider1))
						{
							if (dynamic_cast<BoxCollider *>(collider2))
							{
								if (dynamic_cast<BoxCollider *>(collider1)->Colliding(dynamic_cast<BoxCollider *>(collider2)->GetCollider()))
								{
									colliding = true;
								}
							}
							else if (dynamic_cast<SphereCollider *>(collider2))
							{
								if (dynamic_cast<BoxCollider *>(collider1)->Colliding(dynamic_cast<SphereCollider *>(collider2)->GetCollider()))
								{
									colliding = true;
								}
							}
						}
						else if (dynamic_cast<SphereCollider *>(collider1))
						{
							if (dynamic_cast<BoxCollider *>(collider2))
							{
								if (dynamic_cast<SphereCollider *>(collider1)->Colliding(dynamic_cast<BoxCollider *>(collider2)->GetCollider()))
								{
									colliding = true;
								}
							}
							else if (dynamic_cast<SphereCollider *>(collider2))
							{
								if (dynamic_cast<SphereCollider *>(collider1)->Colliding(dynamic_cast<SphereCollider *>(collider2)->GetCollider()))
								{
									colliding = true;
								}
							}
						}
					}
				}
			}
		}

		if (colliding)
		{
			gameObject->GetTransform()->GetPosition().x -= velocity.x;
			gameObject->GetTransform()->GetPosition().y -= velocity.y;
			gameObject->GetTransform()->GetPosition().z -= velocity.z;
		}*/
		gameObject->GetTransform()->GetLocalPosition().x -= velocity.x;
		gameObject->GetTransform()->GetLocalPosition().y -= velocity.y;
		gameObject->GetTransform()->GetLocalPosition().z -= velocity.z;
	}
};