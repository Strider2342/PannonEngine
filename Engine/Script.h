#pragma once
#include <iostream>
#include "GameTime.h"
#include "Component.h"
#include "Input.h"

class Script :public Component
{
public:
	Script();
	virtual ~Script();

	virtual void Start();
	virtual void Update(GameTime gameTime);
	virtual void Render();
};