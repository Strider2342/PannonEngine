#include "Transform.h"

Transform::Transform()
{
	position = Vector3(0, 0, 0);
	rotation = Vector3(0, 0, 0);
	scale = Vector3(1, 1, 1);
	parent = nullptr;
}

void Transform::Init(GameObject *gameObject)
{
	this->gameObject = gameObject;
}

Vector3& Transform::GetPosition()
{
	return position;
}
Vector3& Transform::GetRotation()
{
	return rotation;
}
Vector3& Transform::GetScale()
{
	return scale;
}
Transform* Transform::GetParent()
{
	return parent;
}

void Transform::SetPosition(Vector3 value)
{
	position = Vector3(value.GetX(), value.GetY(), value.GetZ());
}
void Transform::SetRotation(Vector3 value)
{
	rotation = Vector3(value.GetX(), value.GetY(), value.GetZ());
}
void Transform::SetScale(Vector3 value)
{
	scale = Vector3(value.GetX(), value.GetY(), value.GetZ());
}

DirectX::XMMATRIX Transform::GetWorldMatrix()
{
	DirectX::XMMATRIX matRotateX, matRotateY, matRotateZ, matScale, matTranslate;

	matRotateX = DirectX::XMMatrixRotationX(rotation.GetX());
	matRotateY = DirectX::XMMatrixRotationY(rotation.GetY());
	matRotateZ = DirectX::XMMatrixRotationZ(rotation.GetZ());
	matScale = DirectX::XMMatrixScaling(scale.GetX(), scale.GetY(), scale.GetZ());
	matTranslate = DirectX::XMMatrixTranslation(position.GetX(), position.GetY(), position.GetZ());

	if (HasParent())
	{
		return matRotateX * matRotateY * matRotateZ * matScale * matTranslate * parent->GetWorldMatrix();
	}
	else
	{
		return matRotateX * matRotateY * matRotateZ * matScale * matTranslate;
	}
}

bool Transform::HasParent()
{
	if (parent == nullptr)
		return false;
	else
		return true;
}