#pragma once
#include <iostream>
#include <string>
#include "GameTime.h"
#include "GameObject.h"
#include "Script.h"
#include "DirectXMathExtension.h"
#include "DebugHelper.h"

class EditorCameraScript : public Script
{
private:
	float speed = 0.025f;

	Transform *camtransform;

public:
	EditorCameraScript() { }

	void Start()
	{
		camtransform = gameObject->GetTransform()->GetChild(0);
	}
	void Update(GameTime gameTime, Input input)
	{
		//std::cout << gameObject->GetName() << " " << "{" << std::to_string(gameObject->GetTransform()->GetPosition().x) << "; " << std::to_string(gameObject->GetTransform()->GetPosition().y) << "; " << std::to_string(gameObject->GetTransform()->GetPosition().z) << "}" << std::endl;
		if (input.GetMouseButtonDown(MouseButton::RightButton))
		{
			if (input.GetKeyDown(KeyCode::W))
			{
				XMFLOAT3 velocity = camtransform->GetForward() * speed;
				gameObject->GetTransform()->GetLocalPosition() = gameObject->GetTransform()->GetLocalPosition() + velocity;
			}
			else if (input.GetKeyDown(KeyCode::S))
			{
				XMFLOAT3 velocity = camtransform->GetForward() * -speed;
				gameObject->GetTransform()->GetLocalPosition() = gameObject->GetTransform()->GetLocalPosition() + velocity;
			}

			if (input.GetKeyDown(KeyCode::A))
			{
				XMFLOAT3 velocity = camtransform->GetRight() * -speed;
				gameObject->GetTransform()->GetLocalPosition() = gameObject->GetTransform()->GetLocalPosition() + velocity;
			}
			else if (input.GetKeyDown(KeyCode::D))
			{
				XMFLOAT3 velocity = camtransform->GetRight() * speed;
				gameObject->GetTransform()->GetLocalPosition() = gameObject->GetTransform()->GetLocalPosition() + velocity;
			}

			if (input.GetKeyDown(KeyCode::Q))
			{
				XMFLOAT3 velocity = camtransform->GetUp() * -speed;
				gameObject->GetTransform()->GetLocalPosition() = gameObject->GetTransform()->GetLocalPosition() + velocity;
			}
			else if (input.GetKeyDown(KeyCode::E))
			{
				XMFLOAT3 velocity = camtransform->GetUp() * speed;
				gameObject->GetTransform()->GetLocalPosition() = gameObject->GetTransform()->GetLocalPosition() + velocity;
			}

			//ShowCursor(false);
			DirectX::XMFLOAT2 delta = input.GetDeltaPosition();
			DirectX::XMFLOAT3 rotation = gameObject->GetTransform()->GetLocalRotation();

			//gameObject->GetTransform()->SetRotation(DirectX::XMFLOAT3(rotation.x, rotation.y + delta.x * 0.0005f, rotation.z));
			//gameObject->GetTransform()->GetChild(0)->SetRotation(DirectX::XMFLOAT3(rotation.x + delta.y * 0.0005f, rotation.y, rotation.z));

			gameObject->GetTransform()->GetLocalRotation().y += delta.x * 0.0005f;
			//std::cout << camtransform->GetForward().y << std::endl;
			//std::cout << gameObject->GetTransform()->GetRotation().y << std::endl;
			camtransform->GetLocalRotation().x += delta.y * 0.0005f;
			camtransform->GetLocalRotation().z = 0.0f;

			if (input.GetMousePosition().x > 1706)
			{
				input.SetMousePosition(1, input.GetMousePosition().y);
			}
			if (input.GetMousePosition().x < 0)
			{
				input.SetMousePosition(1705, input.GetMousePosition().y);
			}

			if (input.GetMousePosition().y > 960)
			{
				input.SetMousePosition(input.GetMousePosition().x, 1);
			}
			if (input.GetMousePosition().y < 0)
			{
				input.SetMousePosition(input.GetMousePosition().x, 959);
			}
		}

		//gameObject->GetTransform()->GetChild(0)->GetLocalRotation().x += 0.0005f;
	}
};