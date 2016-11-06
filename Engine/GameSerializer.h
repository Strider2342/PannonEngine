#pragma once
#include "json.hpp"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Collider.h"

using json = nlohmann::json;

class GameSerializer
{

public:
	GameSerializer();

	// Import
	//GameScene*		ImportScene(std::string filename);

	GameObject*		ImportGameObject(json json_object, DirectX::XMFLOAT3 globalAmbient);
	Transform*		ImportTransform(json json_object);
	MeshRenderer*	ImportMeshRenderer(json json_object);
	Camera*			ImportCamera(json json_object);
	Light*			ImportLight(json json_object);
	SphereCollider* ImportSphereCollider(json json_object);
	BoxCollider*	ImportBoxCollider(json json_object);
	Material*		ImportMaterial(json json_object);

	// Export
	//json ExportScene(GameScene *gameScene);

	json ExportGameObject(GameObject *gameObject);
	json ExportTransform(Transform *transform);
	json ExportMeshRenderer(MeshRenderer *meshRenderer);
	json ExportCamera(Camera *camera);
	json ExportLight(Light *light);
	json ExportSphereCollider(SphereCollider *sphereCollider);
	json ExportBoxCollider(BoxCollider *boxCollider);
	json ExportMaterial(Material *material);
};