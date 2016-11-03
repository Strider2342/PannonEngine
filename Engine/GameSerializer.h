#pragma once
#include "json.hpp"
#include "GameScene.h"

using json = nlohmann::json;

class GameSerializer
{

public:
	GameSerializer();

	GameScene* ImportScene(std::string filename);

	Transform* ImportTransform(json json_object);
	MeshRenderer* ImportMeshRenderer(json json_object);
	Camera* ImportCamera(json json_object);
	Light* ImportLight(json json_object);
	SphereCollider* ImportSphereCollider(json json_object);
	BoxCollider* ImportBoxCollider(json json_object);
};