#pragma once
#include "Script.h"

class EnemyScript : public Script
{
private:
	float born = -1.0f;
	float age = 10;

public:
	EnemyScript()
	{

	}

	void Start()
	{

	}

	void Update(GameTime gameTime, Input input)
	{
		age = gameTime.GetElapsedTime();
		if (born == -1.0f)
		{
			born = gameTime.GetElapsedTime();
		}
		gameObject->GetTransform()->GetLocalPosition().y += 0.01f;

		if (age - born > 5)
		{
			gameObject->Destroy();
		}
	}
};