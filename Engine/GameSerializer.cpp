#include "GameSerializer.h"

GameSerializer::GameSerializer()
{
}

GameScene* GameSerializer::ImportScene(std::string filename)
{
	std::ifstream file(filename);
	std::string text = "";

	if (file.is_open())
	{
		std::string line;
		while (getline(file, line))
		{
			text += line;
		}
		file.close();
	}

	json scene_json = json::parse(text.c_str())["scene"];

	GameScene *newscene = new GameScene();
	
	// global ambient light
	DirectX::XMFLOAT3 globalAmbient = DirectX::XMFLOAT3(scene_json["globalAmbient"]["x"], scene_json["globalAmbient"]["y"], scene_json["globalAmbient"]["z"]);
	newscene->SetGlobalAmbient(globalAmbient);

	// game objects
	json gameObjects_json = scene_json["gameObjects"];
	for (json::iterator it = gameObjects_json.begin(); it != gameObjects_json.end(); ++it) 
	{
		GameObject *gameObject = new GameObject();
		gameObject->SetName((*it)["name"]);
		
		json components_json = (*it)["components"];

		for (json::iterator comp_it = components_json.begin(); comp_it != components_json.end(); ++comp_it)
		{
			if (comp_it->count("transform"))
			{
				gameObject->SetTransform(ImportTransform((*comp_it)["transform"]));
			}
			else if (comp_it->count("meshRenderer"))
			{
				gameObject->AddComponent<MeshRenderer>(ImportMeshRenderer((*comp_it)["meshRenderer"]));
			}
			else if (comp_it->count("camera"))
			{
				gameObject->AddComponent<Camera>(ImportCamera((*comp_it)["camera"]));
			}
			else if (comp_it->count("light"))
			{
				gameObject->AddComponent<Light>(ImportLight((*comp_it)["light"]));
			}
			else if (comp_it->count("sphereCollider"))
			{
				gameObject->AddComponent<SphereCollider>(ImportSphereCollider((*comp_it)["sphereCollider"]));
			}
			else if (comp_it->count("boxCollider"))
			{
				gameObject->AddComponent<BoxCollider>(ImportBoxCollider((*comp_it)["boxCollider"]));
			}
		}

		newscene->AddGameObject(gameObject);
	}

	return newscene;
}

Transform* GameSerializer::ImportTransform(json json_object)
{
	Transform *transform = new Transform();

	return transform;
}

MeshRenderer* GameSerializer::ImportMeshRenderer(json json_object)
{
	MeshRenderer *meshRenderer = new MeshRenderer();

	return meshRenderer;
}

Camera* GameSerializer::ImportCamera(json json_object)
{
	Camera *camera = new Camera();

	return camera;
}

Light* GameSerializer::ImportLight(json json_object)
{
	Light *light = new Light();

	return light;
}

SphereCollider* GameSerializer::ImportSphereCollider(json json_object)
{
	SphereCollider *sphereCollider = new SphereCollider();

	return sphereCollider;
}

BoxCollider* GameSerializer::ImportBoxCollider(json json_object)
{
	BoxCollider *boxCollider = new BoxCollider();

	return boxCollider;
}
