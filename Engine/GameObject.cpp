#include "GameObject.h"

GameObject::GameObject()
{
	AddComponent<Transform>();
}

GameObject::~GameObject()
{ }

void GameObject::Start()
{
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->Start();
	}
}
void GameObject::PreUpdate()
{
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->PreUpdate();
	}
}
void GameObject::Update(GameTime gameTime, Input input)
{
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->Update(gameTime, input);
	}
}
void GameObject::PostUpdate()
{
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->PostUpdate();
	}
}
void GameObject::Render()
{
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->Render();
	}
}
void GameObject::PostRender()
{
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->PostRender();
	}
}

void GameObject::OnCollision()
{
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->OnCollision();
	}
}
void GameObject::OnCollisionEnter()
{
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->OnCollisionEnter();
	}
}
void GameObject::OnCollisionStay()
{
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->OnCollisionStay();
	}
}
void GameObject::OnCollisionExit()
{
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->OnCollisionExit();
	}
}

Transform* GameObject::GetTransform()
{
	return GetComponent<Transform>();
}
std::string GameObject::GetName()
{
	return name;
}

bool GameObject::IsEmpty()
{
	return isEmpty;
}

int GameObject::GetNumberOfComponents()
{
	return components.size();
}

Component* GameObject::GetComponentById(int id)
{
	return components[id];
}

std::string GameObject::Export()
{
	StringBuffer s;
	Writer<StringBuffer> writer(s);

	writer.StartObject();
	writer.Key("name");
	writer.String(name.c_str());
	writer.Key("transform");
	std::string json = GetTransform()->Export();
	writer.RawValue(json.c_str(), GetTransform()->Export().size(), rapidjson::Type::kStringType);
	writer.EndObject();

	std::string str = s.GetString();

	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == '\"')
		{
			str[i] = '\'';
		}
	}

	return str;
}

void GameObject::Import(std::string json)
{
	Document d;
	d.Parse(json.c_str());

	name = d["gameObject"]["name"].GetString();

	GetTransform()->Import(d["gameObject"]["transform"].GetString());
}

void GameObject::SetName(std::string name)
{
	this->name = name;
}
