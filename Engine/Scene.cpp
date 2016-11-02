#include "Scene.h"

Scene::Scene()
{
	graphics = Graphics();
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

void Scene::SetMainCamera(Camera *camera)
{
	mainCamera = camera;
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
	writer.Key("gameObjects");
	writer.StartArray();
	for (int i = 0; i < gameObjects.size(); i++)
	{
		std::string json = gameObjects[i]->Export();
		writer.RawValue(json.c_str(), gameObjects[i]->Export().size(), rapidjson::Type::kStringType);
	}
	writer.EndArray();
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

void Scene::Import(std::string filename)
{
	std::ifstream file("scene1.scn");
	std::string json = "";

	if (file.is_open())
	{
		while (getline(file, json))
		{
			//std::cout << line << '\n';
		}
		file.close();
	}

	Document d;
	d.Parse(json.c_str());

	for (rapidjson::SizeType i = 0; i < d["gameObjects"].Size(); i++)
	{
		/*const Value& c = go[i];*/
		
		std::cout << d["gameObjects"][i]["name"].GetString() << std::endl;

		GameObject *gameObject = new GameObject();
		gameObject->SetName(d["gameObjects"][i]["name"].GetString());

		gameObjects.push_back(gameObject);
	}
}
