#pragma once

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
	virtual void Update();
	virtual void Render();

	void SetGameObject(GameObject *gameObject);
};