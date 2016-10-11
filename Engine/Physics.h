#pragma once
#include <vector>
#include "GameObject.h"
#include "Component.h"
#include "Collider.h"
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

	// get

	// set
	void SetGameObjectArray(std::vector<GameObject*> *gameObjects);
};