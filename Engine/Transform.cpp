#include "Transform.h"

Transform::Transform()
{
	position = Vector3(0, 0, 0);
	rotation = Vector3(0, 0, 0);
	scale = Vector3(1, 1, 1);

	forward = Vector3(0, 0, 1);
	up = Vector3(0, 1, 0);
	right = Vector3(1, 0, 0);

	parent = nullptr;
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
Vector3& Transform::GetForward()
{
	return forward;
}
Vector3& Transform::GetUp()
{
	return up;
}
Vector3& Transform::GetRight()
{
	return right;
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

void Transform::MultiplyScale(float value)
{
	scale = Vector3(scale.GetX() * value, scale.GetY() * value, scale.GetZ() * value);
}

void Transform::SetParent(Transform* parent)
{
	this->parent = parent;
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

DirectX::XMMATRIX Transform::GetRotationMatrix()
{
	DirectX::XMMATRIX matRotateX, matRotateY, matRotateZ;

	return matRotateX * matRotateY * matRotateZ;
}

bool Transform::HasParent()
{
	if (parent == nullptr)
		return false;
	else
		return true;
}