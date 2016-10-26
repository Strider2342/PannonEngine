#include "Script.h"

Script::Script()
{ }

Script::~Script()
{ }

void Script::Start()
{ }

void Script::Update(GameTime gameTime)
{ }

void Script::Render()
{ }

void Script::OnCollision()
{
}

void Script::OnCollisionEnter()
{
}

void Script::OnCollisionStay()
{
}

void Script::OnCollisionExit()
{
}

std::string Script::Export()
{
	StringBuffer s;
	Writer<StringBuffer> writer(s);

	writer.StartObject();
	writer.Key("script");
	writer.StartObject();
	writer.Key("classname");
	writer.String(classname.c_str());
	writer.EndObject();
	writer.EndObject();

	return s.GetString();
}

void Script::Import(std::string json)
{
}
