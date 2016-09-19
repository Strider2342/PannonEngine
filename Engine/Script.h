#pragma once
#include <iostream>

class GameObject;
class Script
{
	friend class GameObject;
protected:
	GameObject *gameObject;

public:
	Script();
	virtual ~Script();

	virtual void Start();
	virtual void Update();
	virtual void Render();

	void SetGameObject(GameObject *gameObject);
};