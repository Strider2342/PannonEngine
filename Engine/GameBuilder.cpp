#include "GameBuilder.h"

GameBuilder::GameBuilder()
{
	scripts = std::vector<std::string>();
}

void GameBuilder::SetScriptHeader()
{
	std::string headers = "";

	for (int i = 0; i < scripts.size(); i++)
	{
		headers += "#include \"" + scripts.at(i) + ".hpp\"\n";
	}
}

void GameBuilder::CreateScript(std::string classname)
{
	std::string script = "";

	script += "#pragma once\n";
	script += "#include \"Script.h\"\n\n";
	script += "class " + classname + " : Script\n";
	script += "{\n";
	script += "protected:\n\n";
	script += "public:\n";
	script += "\t" + classname + "()\n";
	script += "\t{\n\n\t}\n\n";
	script += "\tvoid Start()\n";
	script += "\t{\n\n\t}\n\n";
	script += "\tvoid Update()\n";
	script += "\t{\n\n\t}\n\n";
	script += "};";
}

void GameBuilder::ModifySceneFile(std::vector<std::string> commands)
{
	std::string firstPart, secondPart;
}

void GameBuilder::BuildGame()
{

}

std::string GameBuilder::GetProjectPath()
{
	return projectPath;
}

void GameBuilder::SetProjectPath(std::string projectPath)
{
	this->projectPath = projectPath;
}
