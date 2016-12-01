#pragma once
#include <iostream>
#include <string>
#include "GameTime.h"
#include "Component.h"
#include "Input.h"

class Script : public Component
{
protected:
	std::string classname;

public:
	Script();

	std::string ScriptName();

	void SetScriptName(std::string name);
};
