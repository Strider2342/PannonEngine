#include "Scene.h"

Scene::Scene()
{
	graphics = Graphics();

	globalAmbient = DirectX::XMFLOAT3(0.5f, 0.5f, 0.5f);
}

void Scene::Init(Graphics &graphics)
{
	this->graphics = graphics;

	gameObjects = std::vector<GameObject*>();
	lights = std::vector<Light::ShaderInput>();
	cameras = std::vector<Camera*>();

	meshes = std::vector<Mesh*>();
	textures = std::vector<Texture*>();
}

std::vector<GameObject*>& Scene::GetGameObjectList()
{
	return gameObjects;
}

void Scene::AddGameObject(GameObject *gameObject)
{
	gameObjects.push_back(gameObject);
}
GameObject* Scene::FindGameObject(std::string name)
{
	std::vector<GameObject*>::iterator iterator;

	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects[i]->GetName() == name)
		{
			return gameObjects[i];
		}
	}

	return nullptr;
}

std::vector<Camera*>& Scene::GetCameraList()
{
	return cameras;
}

void Scene::AddCamera(Camera *camera)
{
	cameras.push_back(camera);
}

Camera* Scene::GetMainCamera()
{
	return mainCamera;
}

DirectX::XMFLOAT3& Scene::GetGlobalAmbient()
{
	return globalAmbient;
}

void Scene::SetMainCamera(Camera *camera)
{
	mainCamera = camera;
}

void Scene::SetGlobalAmbient(DirectX::XMFLOAT3 globalAmbient)
{
	this->globalAmbient = globalAmbient;
}

void Scene::RefreshLights()
{
	lights.clear();

	for (int i = 0; i < gameObjects.size(); i++)
	{
		Light *light = gameObjects[i]->GetComponent<Light>();
		if (light)
		{
			Light::ShaderInput shaderinput = light->GetShaderInput();
			lights.push_back(shaderinput);
		}
	}

	for (int i = 0; i < gameObjects.size(); i++)
	{
		MeshRenderer *renderer = gameObjects[i]->GetComponent<MeshRenderer>();
		if (renderer)
		{
			renderer->SetLights(&lights);
		}
	}
}

std::string Scene::Export()
{
	StringBuffer s;
	Writer<StringBuffer> writer(s);

	writer.StartObject();
	writer.Key("scene");
	writer.StartObject();
	writer.Key("globalAmbient");
	writer.StartObject();
	writer.Key("x");
	writer.Double(globalAmbient.x);
	writer.Key("y");
	writer.Double(globalAmbient.y);
	writer.Key("z");
	writer.Double(globalAmbient.z);
	writer.EndObject();
	writer.Key("gameObjects");
	writer.StartArray();
	for (int i = 0; i < gameObjects.size(); i++)
	{
		std::string json = gameObjects[i]->Export();
		writer.RawValue(json.c_str(), json.size(), rapidjson::Type::kStringType);
	}
	writer.EndArray();
	writer.EndObject();
	writer.EndObject();

	//std::cout << "Scene: " << s.GetString() << std::endl;

	std::string str = s.GetString();

	for (int i = 1; i < str.length() - 1; i++)
	{
		if (str[i] == '\'')
		{
			str[i] = '\"';
		}
	}

	std::ofstream file("scene1.scn");
	if (file.is_open())
	{
		file << str;
		file.close();
	}

	return str;
}

void Scene::ImportFromFile(std::string filename)
{
	std::ifstream file("scene1.scn");
	std::string json = "";

	if (file.is_open())
	{
		std::string line;
		while (getline(file, line))
		{
			json += line;
		}
		file.close();
	}
	
	Document d;
	d.Parse(json.c_str());

	const Value &objects = d["scene"]["gameObjects"];
	assert(objects.IsArray());
	for (rapidjson::SizeType i = 0; i < objects.Size(); i++)
	{
		std::cout << objects[i]["name"].GetString() << std::endl;

		GameObject *gameObject = new GameObject();
		gameObject->SetName(objects[i]["name"].GetString());

		const Value &components = objects[i]["components"];
		
		std::cout << components.Size() << std::endl;

		for (Value::ConstMemberIterator iter = components.MemberBegin(); iter != components.MemberEnd(); ++iter)
		{
			/*if (iter->name.GetString() == "transform")
			{
				gameObject->GetComponent<Transform>()->Import(components["transform"]);
			}
			else if (iter->name == "meshRenderer")
			{
				gameObject->AddComponent<MeshRenderer>();
			}
			else if (iter->name == "camera")
			{
				gameObject->AddComponent<Camera>();
				gameObject->GetComponent<Camera>()->Import(components["camera"]);
			}
			else if (iter->name == "sphereCollider")
			{
				gameObject->AddComponent<SphereCollider>();
				gameObject->GetComponent<SphereCollider>()->Import(components["sphereCollider"]);
			}
			else if (iter->name == "boxCollider")
			{
				gameObject->AddComponent<BoxCollider>();
				gameObject->GetComponent<BoxCollider>()->Import(components["boxCollider"]);
			}
			else if (iter->name == "light")
			{
				gameObject->AddComponent<Light>();
				gameObject->GetComponent<Light>()->Import(components["light"]);
			}*/
		}

		gameObjects.push_back(gameObject);
	}
}

void Scene::Import(const Value & component)
{
}
