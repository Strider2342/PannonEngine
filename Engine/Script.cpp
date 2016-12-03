#include "Script.h"

Script::Script()
{
}

std::string Script::ScriptName()
{
	return classname;
}

void Script::SetScriptName(std::string name)
{
	classname = name;
}

void Script::SetBuilder(GameBuilder *builder)
{
	this->builder = builder;
}
