#pragma once
#include <vector>
#include <DirectXMath.h>
#include "Component.h"
#include "Vector3.h"

using namespace DirectX;

class Transform : public Component
{
private:
	XMFLOAT3 position;
	XMFLOAT3 rotation;
	XMFLOAT3 scale;

	XMFLOAT3 forward;
	XMFLOAT3 up;
	XMFLOAT3 right;

	Transform *parent;
	std::vector<Transform *> children;

public:
	Transform();

	XMFLOAT3& GetPosition();
	XMFLOAT3& GetRotation();
	XMFLOAT3& GetScale();

	XMFLOAT3& GetForward();
	XMFLOAT3& GetUp();
	XMFLOAT3& GetRight();

	Transform* GetParent();
	Transform* GetChild(int id);
	std::vector<Transform *>& GetChildren();

	void SetPosition(XMFLOAT3 value);
	void SetRotation(XMFLOAT3 value);
	void SetScale(XMFLOAT3 value);

	void MultiplyScale(float value);
	
	void SetParent(Transform *parent);
	void AddChild(Transform *transform);

	DirectX::XMMATRIX GetWorldMatrix();
	DirectX::XMMATRIX GetRotationMatrix();

	bool HasParent();
	bool HasChildren();

	// object
	std::string Export();
	void Import(const Value &component);
};