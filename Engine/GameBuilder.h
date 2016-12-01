#pragma once
#include <iostream>
#include <vector>

class GameBuilder
{
	std::string projectPath;
	std::string scripts;

public:
	GameBuilder();

	void SetScriptHeader();
	void CreateScript(std::string classname);
	void ModifySceneFile();
	void BuildGame();
};