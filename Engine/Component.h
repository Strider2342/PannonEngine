#pragma once
#include <iostream>
#include <string>
#include "Object.h"
#include "GameTime.h"
#include "Input.h"

class GameObject;
class Component : public Object
{
	friend class GameObject;

protected:
	GameObject *gameObject;

public:
	Component();
	virtual ~Component();

	virtual void Start();
	virtual void PreUpdate();
	virtual void Update(GameTime gameTime, Input input);
	virtual void PostUpdate();
	virtual void Render();
	virtual void PostRender();

	virtual void OnCollision();
	virtual void OnCollisionEnter();
	virtual void OnCollisionStay();
	virtual void OnCollisionExit();

	void SetGameObject(GameObject *gameObject);
};