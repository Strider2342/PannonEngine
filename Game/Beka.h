#pragma once

class Beka : public Script
{
public:
	Beka() {}

	void Update()
	{
		if (Input::GetKeyDown(KeyCode::LeftArrow))
		{
			gameObject->GetTransform()->GetPosition().x += 0.005f;
		}
		else if (Input::GetKeyDown(KeyCode::RightArrow))
		{
			gameObject->GetTransform()->GetPosition().x -= 0.005f;
		}

		if (Input::GetKeyDown(KeyCode::UpArrow))
		{
			gameObject->GetTransform()->GetPosition().y -= 0.005f;
		}
		else if (Input::GetKeyDown(KeyCode::DownArrow))
		{
			gameObject->GetTransform()->GetPosition().y += 0.005f;
		}
	}
};