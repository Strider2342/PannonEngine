#pragma once
#include <iostream>
#include "GameObject.h"
#include "Script.h"

class MyFirstScript : public Script
{
public:
	MyFirstScript();

	void Start();
	void Update();
};