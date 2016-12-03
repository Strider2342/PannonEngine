#pragma once
#include <iostream>
#include <string>
#include "GameBuilder.h"
#include "GameTime.h"
#include "Component.h"
#include "Input.h"

class Script : public Component
{
protected:
	GameBuilder *builder;

	std::string classname;

public:
	Script();

	std::string ScriptName();

	void SetScriptName(std::string name);
	void SetBuilder(GameBuilder *builder);
};
