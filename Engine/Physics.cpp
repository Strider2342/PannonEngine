#include "Physics.h"

Physics::Physics()
{
}

void Physics::Start()
{
}
void Physics::Update(GameTime gameTime)
{
}
void Physics::Render()
{
}

Hit Physics::LineCast(DirectX::XMFLOAT3 origin, DirectX::XMFLOAT3 destination)
{
	for (int i = 0; i < gameObjects->size(); i++)
	{

	}

	return Hit();
}
Hit Physics::RayCast(DirectX::XMFLOAT3 origin, DirectX::XMFLOAT3 direction)
{
	Hit hit = Hit();

	for (int i = 0; i < (*gameObjects).size(); i++)
	{
		if ((*gameObjects)[i] != gameObject)
		{
			Collider *collider = (*gameObjects)[i]->GetComponent<Collider>();

			if (collider != NULL)
			{
				float dist = -1.0f;

				if (dynamic_cast<BoxCollider *>(collider))
				{
					if (dynamic_cast<BoxCollider *>(collider)->GetCollider()->Intersects(DirectX::XMLoadFloat3(&origin), DirectX::XMLoadFloat3(&direction), dist))
					{
						XMVECTOR hitPoint = XMVectorMultiplyAdd(DirectX::XMLoadFloat3(&direction), XMVectorReplicate(dist), DirectX::XMLoadFloat3(&origin));

						hit.gameObject = (*gameObjects)[i];
						hit.hitOccured = true;
						DirectX::XMStoreFloat3(&(hit.position), hitPoint);
					}
				}
				else if (dynamic_cast<SphereCollider *>(collider))
				{
					if (dynamic_cast<SphereCollider *>(collider)->GetCollider()->Intersects(DirectX::XMLoadFloat3(&origin), DirectX::XMLoadFloat3(&direction), dist))
					{
						XMVECTOR hitPoint = XMVectorMultiplyAdd(DirectX::XMLoadFloat3(&direction), XMVectorReplicate(dist), DirectX::XMLoadFloat3(&origin));

						hit.gameObject = (*gameObjects)[i];
						hit.hitOccured = true;
						DirectX::XMStoreFloat3(&(hit.position), hitPoint);
					}
				}
			}
		}
	}

	return hit;
}
Hit Physics::RayCast(DirectX::XMFLOAT3 origin, DirectX::XMFLOAT3 direction, float distance)
{
	Hit hit = Hit();

	for (int i = 0; i < gameObjects->size(); i++)
	{
		if ((*gameObjects)[i] != gameObject)
		{
			Collider *collider = (*gameObjects)[i]->GetComponent<Collider>();

			if (collider != NULL)
			{
				float dist = -1.0f;

				if (dynamic_cast<BoxCollider *>(collider))
				{
					if (dynamic_cast<BoxCollider *>(collider)->GetCollider()->Intersects(DirectX::XMLoadFloat3(&origin), DirectX::XMLoadFloat3(&direction), dist))
					{
						if (dist <= distance)
						{
							XMVECTOR hitPoint = XMVectorMultiplyAdd(DirectX::XMLoadFloat3(&direction), XMVectorReplicate(dist), DirectX::XMLoadFloat3(&origin));

							hit.gameObject = (*gameObjects)[i];
							hit.hitOccured = true;
							DirectX::XMStoreFloat3(&(hit.position), hitPoint);
						}
					}
				}
				else if (dynamic_cast<SphereCollider *>(collider))
				{
					if (dynamic_cast<SphereCollider *>(collider)->GetCollider()->Intersects(DirectX::XMLoadFloat3(&origin), DirectX::XMLoadFloat3(&direction), dist))
					{
						if (dist <= distance)
						{
							XMVECTOR hitPoint = XMVectorMultiplyAdd(DirectX::XMLoadFloat3(&direction), XMVectorReplicate(dist), DirectX::XMLoadFloat3(&origin));

							hit.gameObject = (*gameObjects)[i];
							hit.hitOccured = true;
							DirectX::XMStoreFloat3(&(hit.position), hitPoint);
						}
					}
				}
			}
		}
	}

	return hit;
}

void Physics::SetGameObjectArray(std::vector<GameObject*> *gameObjects)
{
	this->gameObjects = gameObjects;
}
