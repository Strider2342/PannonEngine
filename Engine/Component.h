#pragma once
#include "GameTime.h"

class GameObject;
class Component
{
	friend class GameObject;

protected:
	GameObject *gameObject;

public:
	Component();
	virtual ~Component();

	virtual void Start();
	virtual void Update(GameTime gameTime);
	virtual void Render();

	void SetGameObject(GameObject *gameObject);
};