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
	this->parent = parent;
}

void Transform::AddChild(Transform *child)
{
	children.push_back(child);
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
	return false;
}

std::string Transform::Export()
{
	StringBuffer s;
	Writer<StringBuffer> writer(s);

	writer.StartObject();
	writer.Key("parent");
	writer.String("parentid");
	writer.Key("position");
	writer.StartObject();
	writer.Key("x");
	writer.Double(position.x);
	writer.Key("y");
	writer.Double(position.y);
	writer.Key("z");
	writer.Double(position.z);
	writer.EndObject();
	writer.Key("rotation");
	writer.StartObject();
	writer.Key("x");
	writer.Double(rotation.x);
	writer.Key("y");
	writer.Double(rotation.y);
	writer.Key("z");
	writer.Double(rotation.z);
	writer.EndObject();
	writer.Key("scale");
	writer.StartObject();
	writer.Key("x");
	writer.Double(scale.x);
	writer.Key("y");
	writer.Double(scale.y);
	writer.Key("z");
	writer.Double(scale.z);
	writer.EndObject();
	writer.EndObject();

	std::string str = s.GetString();

	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == '\"')
		{
			str[i] = '\'';
		}
	}

	return str;
}

void Transform::Import(std::string json)
{
	Document d;
	d.Parse(json.c_str());

	float position_x = d["transform"]["position"]["x"].GetFloat();
	float position_y = d["transform"]["position"]["y"].GetFloat();
	float position_z = d["transform"]["position"]["x"].GetFloat();

	float rotation_x = d["transform"]["position"]["x"].GetFloat();
	float rotation_y = d["transform"]["position"]["y"].GetFloat();
	float rotation_z = d["transform"]["position"]["z"].GetFloat();

	float scale_x = d["transform"]["position"]["x"].GetFloat();
	float scale_y = d["transform"]["position"]["y"].GetFloat();
	float scale_z = d["transform"]["position"]["z"].GetFloat();

	position = DirectX::XMFLOAT3(position_x, position_y, position_z);
	rotation = DirectX::XMFLOAT3(rotation_x, rotation_y, rotation_z);
	scale = DirectX::XMFLOAT3(scale_x, scale_y, scale_z);
}
