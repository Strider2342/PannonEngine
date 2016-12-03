#pragma once
#include <iostream>
#include <vector>
#include <string>

class GameBuilder
{
	std::string projectPath;
	std::vector<std::string> scripts;

public:
	GameBuilder();

	void SetScriptHeader();
	void CreateScript(std::string classname);
	void ModifySceneFile(std::vector<std::string> commands);
	void BuildGame();

	std::string GetProjectPath();
	void SetProjectPath(std::string projectPath);
};