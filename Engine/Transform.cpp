#include "Transform.h"

Transform::Transform()
{
	position = XMFLOAT3(0, 0, 0);
	rotation = XMFLOAT3(0, 0, 0);
	scale = XMFLOAT3(1, 1, 1);

	forward = XMFLOAT3(0, 0, 1);
	up = XMFLOAT3(0, 1, 0);
	right = XMFLOAT3(1, 0, 0);

	parent = nullptr;
}

XMFLOAT3& Transform::GetPosition()
{
	return position;
}
XMFLOAT3& Transform::GetRotation()
{
	return rotation;
}
XMFLOAT3& Transform::GetScale()
{
	return scale;
}
XMFLOAT3& Transform::GetForward()
{
	XMFLOAT3 vector;
	XMStoreFloat3(&vector, XMVector3Normalize(XMVector3Transform(XMLoadFloat3(&forward), GetRotationMatrix())));

	return vector;
}
XMFLOAT3& Transform::GetUp()
{
	XMFLOAT3 vector;
	XMStoreFloat3(&vector, XMVector3Normalize(XMVector3Transform(XMLoadFloat3(&up), GetRotationMatrix())));

	return vector;
}
XMFLOAT3& Transform::GetRight()
{
	XMFLOAT3 vector;
	XMStoreFloat3(&vector, XMVector3Normalize(XMVector3Transform(XMLoadFloat3(&right), GetRotationMatrix())));

	return vector;
}
Transform* Transform::GetParent()
{
	return parent;
}

Transform* Transform::GetChild(int id)
{
	return children.at(id);
}

std::vector<Transform*>& Transform::GetChildren()
{
	return children;
}

void Transform::SetPosition(XMFLOAT3 value)
{
	position = XMFLOAT3(value.x, value.y, value.z);
}
void Transform::SetRotation(XMFLOAT3 value)
{
	rotation = XMFLOAT3(value.x, value.y, value.z);
}
void Transform::SetScale(XMFLOAT3 value)
{
	scale = XMFLOAT3(value.x, value.y, value.z);
}

void Transform::MultiplyScale(float value)
{
	scale = XMFLOAT3(scale.x * value, scale.y * value, scale.z * value);
}

void Transform::SetParent(Transform* parent)
{
	if (HasParent())
	{
		this->parent->RemoveChild(this);
	}

	this->parent = parent;
	parent->AddChild(this);
}

void Transform::AddChild(Transform *child)
{
	bool contained = false;
	for (int i = 0; i < children.size(); i++)
	{
		if (child == children.at(i))
		{
			contained = true;
			break;
		}
	}

	if (!contained)
	{
		children.push_back(child);
	}
}

void Transform::RemoveChild(Transform * child)
{
	for (int i = 0; i < children.size(); i++)
	{
		if (child == children.at(i))
		{
			children.erase(children.begin() + i);
			break;
		}
	}
}

DirectX::XMMATRIX Transform::GetWorldMatrix()
{
	DirectX::XMMATRIX matRotateX, matRotateY, matRotateZ, matScale, matTranslate;

	matRotateX = DirectX::XMMatrixRotationX(rotation.x);
	matRotateY = DirectX::XMMatrixRotationY(rotation.y);
	matRotateZ = DirectX::XMMatrixRotationZ(rotation.z);
	matScale = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
	matTranslate = DirectX::XMMatrixTranslation(position.x, position.y, position.z);

	if (HasParent())
	{
		return matScale * matRotateX * matRotateY * matRotateZ * matTranslate * parent->GetWorldMatrix();
	}
	else
	{
		return matScale * matRotateX * matRotateY * matRotateZ * matTranslate;
	}
}

DirectX::XMMATRIX Transform::GetRotationMatrix()
{
	DirectX::XMMATRIX matRotateX, matRotateY, matRotateZ;

	matRotateX = DirectX::XMMatrixRotationX(rotation.x);
	matRotateY = DirectX::XMMatrixRotationY(rotation.y);
	matRotateZ = DirectX::XMMatrixRotationZ(rotation.z);

	return matRotateX * matRotateY * matRotateZ;
}

bool Transform::HasParent()
{
	if (parent == nullptr)
		return false;
	else
		return true;
}

bool Transform::HasChildren()
{
	if (children.size() > 0)
		return true;
	else
		return false;
}
