#include "Physics.h"

RayCaster::RayCaster()
{
}

Hit RayCaster::RayCast(DirectX::XMFLOAT3 origin, DirectX::XMFLOAT3 direction)
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
Hit RayCaster::RayCast(DirectX::XMFLOAT3 origin, DirectX::XMFLOAT3 direction, float distance)
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
Hit RayCaster::RayCast(Ray ray)
{
	/*std::cout << "Origin: " << ray.GetOrigin().x << ":" << ray.GetOrigin().y << ":" << ray.GetOrigin().z << std::endl;
	std::cout << "Direction: " << ray.GetDirection().x << ":" << ray.GetDirection().y << ":" << ray.GetDirection().z << std::endl;*/
	return RayCast(ray.GetOrigin(), ray.GetDirection());
}
Hit RayCaster::RayCast(Ray ray, float distance)
{
	return RayCast(ray.GetOrigin(), ray.GetDirection(), distance);
}

std::vector<GameObject*>* RayCaster::GetGameObjectArray()
{
	return gameObjects;
}

void RayCaster::SetGameObjectArray(std::vector<GameObject*> *gameObjects)
{
	this->gameObjects = gameObjects;
}
