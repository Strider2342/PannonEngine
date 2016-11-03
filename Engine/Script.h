#pragma once
#include <iostream>
#include "GameTime.h"
#include "Component.h"
#include "Input.h"

class Script :public Component
{
protected:
	std::string classname;

public:
	Script();
	virtual ~Script();

	virtual void Start();
	virtual void Update(GameTime gameTime);
	virtual void Render();

	virtual void OnCollision();
	virtual void OnCollisionEnter();
	virtual void OnCollisionStay();
	virtual void OnCollisionExit();
};