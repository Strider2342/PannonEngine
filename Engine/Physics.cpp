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
Hit Physics::RayCast(Ray ray)
{
	/*std::cout << "Origin: " << ray.GetOrigin().x << ":" << ray.GetOrigin().y << ":" << ray.GetOrigin().z << std::endl;
	std::cout << "Direction: " << ray.GetDirection().x << ":" << ray.GetDirection().y << ":" << ray.GetDirection().z << std::endl;*/
	return RayCast(ray.GetOrigin(), ray.GetDirection());
}
Hit Physics::RayCast(Ray ray, float distance)
{
	return RayCast(ray.GetOrigin(), ray.GetDirection(), distance);
}

Hit Physics::RayPicking(Ray ray)
{
	Hit hit = Hit();
	
	for (int i = 0; i < gameObjects->size(); i++)
	{
		if ((*gameObjects)[i]->GetComponent<MeshRenderer>() != NULL)
		{
			/*DirectX::BoundingOrientedBox *collider = (*gameObjects)[i]->GetComponent<Physics>()->GetColliderByBoundingBox();
			float dist = -1.0f;

			if (collider->Intersects(DirectX::XMLoadFloat3(&(ray.GetOrigin())), DirectX::XMLoadFloat3(&(ray.GetDirection())), dist))
			{
				XMVECTOR hitPoint = XMVectorMultiplyAdd(DirectX::XMLoadFloat3(&(ray.GetDirection())), XMVectorReplicate(dist), DirectX::XMLoadFloat3(&(ray.GetOrigin())));

				hit.gameObject = (*gameObjects)[i];
				hit.hitOccured = true;
				DirectX::XMStoreFloat3(&(hit.position), hitPoint);
			}*/

			GameObject *gameObject1 = (*gameObjects)[i];

			std::vector<Triangle> triangles = gameObject1->GetComponent<MeshRenderer>()->GetTriangles();
			
			for (int j = 0; j < triangles.size(); j++)
			{
				float dist = 1000.0f;
				if (DirectX::TriangleTests::Intersects(DirectX::XMLoadFloat3(&ray.GetOrigin()), DirectX::XMLoadFloat3(&ray.GetDirection()), DirectX::XMLoadFloat3(&triangles[j].GetPointA()), DirectX::XMLoadFloat3(&triangles[j].GetPointB()), DirectX::XMLoadFloat3(&triangles[j].GetPointC()), dist))
				{
					std::cout << "kjldfkjbvgnlsvjlsrtfjv" << std::endl;
				}
			}
		}
	}

	return hit;
}

std::vector<GameObject*>* Physics::GetGameObjectArray()
{
	return gameObjects;
}

DirectX::BoundingOrientedBox* Physics::GetColliderByBoundingBox()
{
	DirectX::BoundingOrientedBox *collider = new DirectX::BoundingOrientedBox();

	DirectX::XMFLOAT3 center = gameObject->GetComponent<MeshRenderer>()->GetBounds().GetCenter();
	collider->Center = center;
	collider->Extents = DirectX::XMFLOAT3(gameObject->GetComponent<MeshRenderer>()->GetMesh()->GetBounds().GetXLength(), gameObject->GetComponent<MeshRenderer>()->GetMesh()->GetBounds().GetYLength(), gameObject->GetComponent<MeshRenderer>()->GetMesh()->GetBounds().GetZLength());
	collider->Orientation = DirectX::XMFLOAT4(gameObject->GetTransform()->GetForward().x, gameObject->GetTransform()->GetForward().y, gameObject->GetTransform()->GetForward().z, 1.0f);

	return collider;
}

void Physics::SetGameObjectArray(std::vector<GameObject*> *gameObjects)
{
	this->gameObjects = gameObjects;
}
