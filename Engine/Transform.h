#pragma once
#include <DirectXMath.h>
#include "Vector3.h"

class GameObject;
class Transform
{
private:
	GameObject *gameObject = nullptr;

	Vector3 position;
	Vector3 rotation;
	Vector3 scale;

	Vector3 forward;
	Vector3 up;
	Vector3 right;

	Transform *parent;

public:
	Transform();

	void Init(GameObject *gameObject);

	Vector3& GetPosition();
	Vector3& GetRotation();
	Vector3& GetScale();
	Transform* GetParent();

	void SetPosition(Vector3 value);
	void SetRotation(Vector3 value);
	void SetScale(Vector3 value);
	void SetParent(Transform *parent);

	DirectX::XMMATRIX GetWorldMatrix();

	bool HasParent();
};