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
	virtual void PreUpdate();
	virtual void Update(GameTime gameTime);
	virtual void PostUpdate();
	virtual void Render();

	virtual void OnCollision();
	virtual void OnCollisionEnter();
	virtual void OnCollisionStay();
	virtual void OnCollisionExit();

	void SetGameObject(GameObject *gameObject);
};