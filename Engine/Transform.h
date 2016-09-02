#pragma once
#include <DirectXMath.h>
#include "Vector3.h"

class Transform
{
private:
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;

	Vector3 forward;
	Vector3 up;
	Vector3 right;

	Transform *parent;

public:
	Transform();

	Vector3& GetPosition();
	Vector3& GetRotation();
	Vector3& GetScale();

	Vector3& GetForward();
	Vector3& GetUp();
	Vector3& GetRight();

	Transform* GetParent();

	void SetPosition(Vector3 value);
	void SetRotation(Vector3 value);
	void SetScale(Vector3 value);


	void SetParent(Transform *parent);

	DirectX::XMMATRIX GetWorldMatrix();

	bool HasParent();
};