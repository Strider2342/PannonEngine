#include "Collider.h"

// collider
Collider::Collider()
{
	center = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
}
DirectX::XMFLOAT3& Collider::GetCenter()
{
	return center;
}
void Collider::SetCenter(DirectX::XMFLOAT3 center)
{}
void Collider::Start()
{}
void Collider::Update(GameTime gameTime, Input input)
{}
bool Collider::Colliding(DirectX::BoundingSphere *collider2)
{
	return false;
}
bool Collider::Colliding(DirectX::BoundingOrientedBox *collider2)
{
	return false;
}

// sphere collider
SphereCollider::SphereCollider()
{
	radius = 1.0f;
}
DirectX::XMFLOAT3& SphereCollider::GetCenter()
{
	return center;
}
float& SphereCollider::GetRadius()
{
	return radius;
}
DirectX::BoundingSphere* SphereCollider::GetCollider()
{
	return &collider;
}
void SphereCollider::SetCenter(DirectX::XMFLOAT3 center)
{
	this->center = center;
	this->collider.Center = DirectX::XMFLOAT3(gameObject->GetTransform()->GetPosition().x + center.x, gameObject->GetTransform()->GetPosition().y + center.y, gameObject->GetTransform()->GetPosition().z + center.z);
}
void SphereCollider::SetRadius(float radius)
{
	this->radius = radius;
	collider.Radius = radius;
}
void SphereCollider::Start()
{
	float max = gameObject->GetTransform()->GetScale().x;
	if (gameObject->GetTransform()->GetScale().y > max) { max = gameObject->GetTransform()->GetScale().y; }
	if (gameObject->GetTransform()->GetScale().z > max) { max = gameObject->GetTransform()->GetScale().z; }

	collider.Center = DirectX::XMFLOAT3(gameObject->GetTransform()->GetPosition().x + gameObject->GetComponent<MeshRenderer>()->GetMesh()->GetBounds().GetCenter().x, gameObject->GetTransform()->GetPosition().y + gameObject->GetComponent<MeshRenderer>()->GetMesh()->GetBounds().GetCenter().y, gameObject->GetTransform()->GetPosition().z + gameObject->GetComponent<MeshRenderer>()->GetMesh()->GetBounds().GetCenter().z);
	collider.Radius = radius * max;
}
void SphereCollider::Update(GameTime gameTime, Input input)
{
	float max = gameObject->GetTransform()->GetScale().x;
	if (gameObject->GetTransform()->GetScale().y > max) { max = gameObject->GetTransform()->GetScale().y; }
	if (gameObject->GetTransform()->GetScale().z > max) { max = gameObject->GetTransform()->GetScale().z; }

	collider.Center = DirectX::XMFLOAT3(gameObject->GetTransform()->GetPosition().x + center.x, gameObject->GetTransform()->GetPosition().y + center.y, gameObject->GetTransform()->GetPosition().z + center.z);
	collider.Radius = radius * max;
}
bool SphereCollider::Colliding(DirectX::BoundingSphere *collider2)
{
	return collider.Intersects(*collider2);
}
bool SphereCollider::Colliding(DirectX::BoundingOrientedBox *collider2)
{
	return collider.Intersects(*collider2);
}

std::string SphereCollider::Export()
{
	StringBuffer s;
	Writer<StringBuffer> writer(s);

	writer.StartObject();
	writer.Key("sphereCollider");
	writer.StartObject();
	writer.Key("center");
	writer.StartObject();
	writer.Key("x");
	writer.Double(center.x);
	writer.Key("y");
	writer.Double(center.y);
	writer.Key("z");
	writer.Double(center.z);
	writer.EndObject();
	writer.Key("radius");
	writer.Double(radius);
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

void SphereCollider::Import(const Value &component)
{
	float center_x = component["center"]["x"].GetFloat();
	float center_y = component["center"]["y"].GetFloat();
	float center_z = component["center"]["x"].GetFloat();

	center = DirectX::XMFLOAT3(center_x, center_y, center_z);
	radius = component["radius"].GetFloat();
}

// box collider
BoxCollider::BoxCollider()
{ 
	size = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
}
DirectX::XMFLOAT3& BoxCollider::GetCenter()
{
	return center;
}
DirectX::XMFLOAT3& BoxCollider::GetSize()
{
	return size;
}
DirectX::BoundingOrientedBox* BoxCollider::GetCollider()
{
	return &collider;
}
void BoxCollider::SetCenter(DirectX::XMFLOAT3 center)
{
	this->center = center;
	collider.Center = DirectX::XMFLOAT3(gameObject->GetTransform()->GetPosition().x + center.x, gameObject->GetTransform()->GetPosition().y + center.y, gameObject->GetTransform()->GetPosition().z + center.z);
}
void BoxCollider::SetSize(DirectX::XMFLOAT3 size)
{
	this->size = size;
	collider.Extents = DirectX::XMFLOAT3(gameObject->GetTransform()->GetScale().x * size.x, gameObject->GetTransform()->GetScale().y * size.y, gameObject->GetTransform()->GetScale().z * size.z);
}
void BoxCollider::Start()
{
	collider.Center = DirectX::XMFLOAT3(gameObject->GetTransform()->GetPosition().x + center.x, gameObject->GetTransform()->GetPosition().y + center.y, gameObject->GetTransform()->GetPosition().z + center.z);
	collider.Extents = DirectX::XMFLOAT3(gameObject->GetTransform()->GetScale().x * size.x * 2.0f, gameObject->GetTransform()->GetScale().y * size.y * 2.0f, gameObject->GetTransform()->GetScale().z * size.z * 2.0f);
	//collider.Orientation = DirectX::XMFLOAT4(gameObject->GetTransform()->GetForward().x, gameObject->GetTransform()->GetForward().y, gameObject->GetTransform()->GetForward().z, 1.0f);
	collider.Orientation = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
}
void BoxCollider::Update(GameTime gameTime, Input input)
{
	collider.Center = DirectX::XMFLOAT3(gameObject->GetTransform()->GetPosition().x + center.x, gameObject->GetTransform()->GetPosition().y + center.y, gameObject->GetTransform()->GetPosition().z + center.z);
	collider.Extents = DirectX::XMFLOAT3(gameObject->GetTransform()->GetScale().x * size.x * 2.0f, gameObject->GetTransform()->GetScale().y * size.y * 2.0f, gameObject->GetTransform()->GetScale().z * size.z * 2.0f);
	//collider.Orientation = DirectX::XMFLOAT4(gameObject->GetTransform()->GetForward().x, gameObject->GetTransform()->GetForward().y, gameObject->GetTransform()->GetForward().z, 1.0f);
	collider.Orientation = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
}
bool BoxCollider::Colliding(DirectX::BoundingSphere *collider2)
{
	return collider.Intersects(*collider2);
}
bool BoxCollider::Colliding(DirectX::BoundingOrientedBox *collider2)
{
	return collider.Intersects(*collider2);
}

std::string BoxCollider::Export()
{
	StringBuffer s;
	Writer<StringBuffer> writer(s);

	writer.StartObject();
	writer.Key("boxCollider");
	writer.StartObject();
	writer.Key("center");
	writer.StartObject();
	writer.Key("x");
	writer.Double(center.x);
	writer.Key("y");
	writer.Double(center.y);
	writer.Key("z");
	writer.Double(center.z);
	writer.EndObject();
	writer.Key("size");
	writer.StartObject();
	writer.Key("x");
	writer.Double(size.x);
	writer.Key("y");
	writer.Double(size.y);
	writer.Key("z");
	writer.Double(size.z);
	writer.EndObject();
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

void BoxCollider::Import(const Value &component)
{
	float center_x = component["center"]["x"].GetFloat();
	float center_y = component["center"]["y"].GetFloat();
	float center_z = component["center"]["x"].GetFloat();

	float size_x = component["size"]["x"].GetFloat();
	float size_y = component["size"]["y"].GetFloat();
	float size_z = component["size"]["x"].GetFloat();

	center = DirectX::XMFLOAT3(center_x, center_y, center_z);
	size = DirectX::XMFLOAT3(size_x, size_y, size_z);
}
