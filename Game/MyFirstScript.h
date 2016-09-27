#pragma once
#include <iostream>
#include "GameTime.h"
#include "GameObject.h"
#include "Script.h"

class MyFirstScript : public Script
{
public:
	MyFirstScript();

	void Start();
	void Update(GameTime gameTime);
};