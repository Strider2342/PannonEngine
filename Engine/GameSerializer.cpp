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
		newscene->AddGameObject(ImportGameObject((*it), globalAmbient));
	}

	return newscene;
}
GameObject* GameSerializer::ImportGameObject(json json_object, DirectX::XMFLOAT3 globalAmbient)
{
	GameObject *gameObject = new GameObject();
	gameObject->SetName(json_object["name"]);

	json components_json = json_object["components"];

	for (json::iterator comp_it = components_json.begin(); comp_it != components_json.end(); ++comp_it)
	{
		if (comp_it->count("transform"))
		{
			gameObject->SetTransform(ImportTransform((*comp_it)["transform"]));
		}
		else if (comp_it->count("meshRenderer"))
		{
			gameObject->AddComponent<MeshRenderer>(ImportMeshRenderer((*comp_it)["meshRenderer"]));
			gameObject->GetComponent<MeshRenderer>()->SetGlobalAmbient(globalAmbient);
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

	return gameObject;
}
Transform* GameSerializer::ImportTransform(json json_object)
{
	Transform *transform = new Transform();

	transform->SetPosition(XMFLOAT3(json_object["position"]["x"], json_object["position"]["y"], json_object["position"]["z"]));
	transform->SetRotation(XMFLOAT3(json_object["rotation"]["x"], json_object["rotation"]["y"], json_object["rotation"]["z"]));
	transform->SetScale(XMFLOAT3(json_object["scale"]["x"], json_object["scale"]["y"], json_object["scale"]["z"]));

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

	camera->SetFOV(json_object["fov"]);
	camera->SetNearClippingPlane(json_object["nearClippingPlane"]);
	camera->SetFarClippingPlane(json_object["farClippingPlane"]);

	return camera;
}
Light* GameSerializer::ImportLight(json json_object)
{
	Light *light = new Light();

	light->SetColor(XMFLOAT4(json_object["color"]["x"], json_object["color"]["y"], json_object["color"]["z"], 1.0f));
	light->SetType(json_object["type"]);
	light->SetIntensity(json_object["intensity"]);
	light->SetEnabled(json_object["enabled"]);
	light->SetSpotAngle(json_object["spotAngle"]);
	light->SetConstantAttenuation(json_object["constantAttenuation"]);
	light->SetLinearAttenuation(json_object["linearAttenuation"]);
	light->SetQuadraticAttenuation(json_object["quadraticAttenuation"]);

	return light;
}
SphereCollider* GameSerializer::ImportSphereCollider(json json_object)
{
	SphereCollider *sphereCollider = new SphereCollider();

	sphereCollider->SetCenter(XMFLOAT3(json_object["center"]["x"], json_object["center"]["y"], json_object["center"]["z"]));
	sphereCollider->SetRadius(json_object["radius"]);

	return sphereCollider;
}
BoxCollider* GameSerializer::ImportBoxCollider(json json_object)
{
	BoxCollider *boxCollider = new BoxCollider();

	boxCollider->SetCenter(XMFLOAT3(json_object["center"]["x"], json_object["center"]["y"], json_object["center"]["z"]));
	boxCollider->SetSize(XMFLOAT3(json_object["size"]["x"], json_object["size"]["y"], json_object["size"]["z"]));

	return boxCollider;
}
Material* GameSerializer::ImportMaterial(json json_object)
{
	Material *material = new Material();

	material->SetDiffuse(json_object["diffuse"]["x"], json_object["diffuse"]["y"], json_object["diffuse"]["z"]);
	material->SetSpecular(json_object["specular"]["x"], json_object["specular"]["y"], json_object["specular"]["z"]);
	material->SetAmbient(json_object["ambient"]["x"], json_object["ambient"]["y"], json_object["ambient"]["z"]);
	material->SetEmissive(json_object["emissive"]["x"], json_object["emissive"]["y"], json_object["emissive"]["z"]);
	material->SetPower(json_object["power"]);

	return nullptr;
}

json GameSerializer::ExportScene(GameScene *gameScene)
{
	json json_object;
	json game_objects_json;

	json_object["scene"]["globalAmbient"]["x"] = gameScene->GetGlobalAmbient().x;
	json_object["scene"]["globalAmbient"]["y"] = gameScene->GetGlobalAmbient().y;
	json_object["scene"]["globalAmbient"]["z"] = gameScene->GetGlobalAmbient().z;

	for (int i = 0; i < gameScene->GetGameObjectList().size(); i++)
	{
		game_objects_json.push_back(json_object);
	}

	json_object["scene"]["gameObjects"] = game_objects_json;

	return json_object;
}
json GameSerializer::ExportGameObject(GameObject *gameObject)
{
	json json_object;

	json_object["name"] = gameObject->GetName();

	for (int i = 0; i < gameObject->GetNumberOfComponents(); i++)
	{
		if (dynamic_cast<Transform *>(gameObject->GetComponentById(i)))
		{
			json_object["components"]["transform"] = ExportTransform(dynamic_cast<Transform *>(gameObject->GetComponentById(i)));
		}
		else if (dynamic_cast<MeshRenderer *>(gameObject->GetComponentById(i)))
		{
			json_object["components"]["meshRenderer"] = ExportMeshRenderer(dynamic_cast<MeshRenderer *>(gameObject->GetComponentById(i)));
		}
		else if (dynamic_cast<Camera *>(gameObject->GetComponentById(i)))
		{
			json_object["components"]["camera"] = ExportCamera(dynamic_cast<Camera *>(gameObject->GetComponentById(i)));
		}
		else if (dynamic_cast<Light *>(gameObject->GetComponentById(i)))
		{
			json_object["components"]["light"] = ExportLight(dynamic_cast<Light *>(gameObject->GetComponentById(i)));
		}
		else if (dynamic_cast<SphereCollider *>(gameObject->GetComponentById(i)))
		{
			json_object["components"]["sphereCollider"] = ExportSphereCollider(dynamic_cast<SphereCollider *>(gameObject->GetComponentById(i)));
		}
		else if (dynamic_cast<BoxCollider *>(gameObject->GetComponentById(i)))
		{
			json_object["components"]["boxCollider"] = ExportBoxCollider(dynamic_cast<BoxCollider *>(gameObject->GetComponentById(i)));
		}
	}

	return json_object;
}
json GameSerializer::ExportTransform(Transform *transform)
{
	json json_object;

	json_object["position"]["x"] = transform->GetPosition().x;
	json_object["position"]["y"] = transform->GetPosition().y;
	json_object["position"]["z"] = transform->GetPosition().z;

	json_object["rotation"]["x"] = transform->GetRotation().x;
	json_object["rotation"]["y"] = transform->GetRotation().y;
	json_object["rotation"]["z"] = transform->GetRotation().z;

	json_object["scale"]["x"] = transform->GetScale().x;
	json_object["scale"]["y"] = transform->GetScale().y;
	json_object["scale"]["z"] = transform->GetScale().z;

	return json_object;
}
json GameSerializer::ExportMeshRenderer(MeshRenderer *meshRenderer)
{
	json json_object;

	return json_object;
}
json GameSerializer::ExportCamera(Camera *camera)
{
	json json_object;

	json_object["fov"] = camera->GetFOV();
	json_object["nearClippingPlane"] = camera->GetNearClippingPlane();
	json_object["farClippingPlane"] = camera->GetFarClippingPlane();

	return json_object;
}
json GameSerializer::ExportLight(Light *light)
{
	json json_object;

	json_object["color"]["x"] = light->GetColor().x;
	json_object["color"]["y"] = light->GetColor().y;
	json_object["color"]["z"] = light->GetColor().z;

	json_object["type"] = light->GetType();
	json_object["intensity"] = light->GetIntensity();
	json_object["enabled"] = light->GetEnabled();
	json_object["spotAngle"] = light->GetSpotAngle();
	json_object["constantAttenuation"] = light->GetConstantAttenuation();
	json_object["linearAttenuation"] = light->GetLinearAttenuation();
	json_object["quadraticAttenuation"] = light->GetQuadraticAttenuation();

	return json_object;
}
json GameSerializer::ExportSphereCollider(SphereCollider *sphereCollider)
{
	json json_object;

	json_object["center"]["x"] = sphereCollider->GetCenter().x;
	json_object["center"]["y"] = sphereCollider->GetCenter().y;
	json_object["center"]["z"] = sphereCollider->GetCenter().z;

	json_object["radius"] = sphereCollider->GetRadius();

	return json_object;
}
json GameSerializer::ExportBoxCollider(BoxCollider *boxCollider)
{
	json json_object;

	json_object["center"]["x"] = boxCollider->GetCenter().x;
	json_object["center"]["y"] = boxCollider->GetCenter().y;
	json_object["center"]["z"] = boxCollider->GetCenter().z;

	json_object["size"]["x"] = boxCollider->GetSize().x;
	json_object["size"]["y"] = boxCollider->GetSize().y;
	json_object["size"]["z"] = boxCollider->GetSize().z;

	return json_object;
}
json GameSerializer::ExportMaterial(Material *material)
{
	json json_object;

	json_object["diffuse"]["x"] = material->GetDiffuse().x;
	json_object["diffuse"]["y"] = material->GetDiffuse().y;
	json_object["diffuse"]["z"] = material->GetDiffuse().z;

	json_object["specular"]["x"] = material->GetSpecular().x;
	json_object["specular"]["y"] = material->GetSpecular().y;
	json_object["specular"]["z"] = material->GetSpecular().z;

	json_object["ambient"]["x"] = material->GetAmbient().x;
	json_object["ambient"]["y"] = material->GetAmbient().y;
	json_object["ambient"]["z"] = material->GetAmbient().z;

	json_object["emissive"]["x"] = material->GetEmissive().x;
	json_object["emissive"]["y"] = material->GetEmissive().y;
	json_object["emissive"]["z"] = material->GetEmissive().z;

	json_object["power"] = material->GetPower();

	return json_object;
}