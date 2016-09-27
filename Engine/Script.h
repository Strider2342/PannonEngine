#pragma once
#include <iostream>
#include "Component.h"
#include "Input.h"

class Script :public Component
{
public:
	Script();
	virtual ~Script();

	virtual void Start();
	virtual void Update();
	virtual void Render();
};