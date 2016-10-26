#pragma once
#include <vector>
#include "GameObject.h"
#include "Component.h"
#include "Collider.h"
#include "Ray.h"
#include "Hit.h"

class Physics : public Component
{
private:
	std::vector<GameObject*> *gameObjects;

public:
	Physics();

	void Start();
	void Update(GameTime gameTime);
	void Render();

	Hit LineCast(DirectX::XMFLOAT3 origin, DirectX::XMFLOAT3 destination); // yet to be written
	Hit RayCast(DirectX::XMFLOAT3 origin, DirectX::XMFLOAT3 direction);
	Hit RayCast(DirectX::XMFLOAT3 origin, DirectX::XMFLOAT3 direction, float distance);
	Hit RayCast(Ray ray);
	Hit RayCast(Ray ray, float distance);
	Hit RayPicking(Ray ray);

	// get
	std::vector<GameObject*>* GetGameObjectArray();

	DirectX::BoundingOrientedBox* GetColliderByBoundingBox();

	// set
	void SetGameObjectArray(std::vector<GameObject*> *gameObjects);
};