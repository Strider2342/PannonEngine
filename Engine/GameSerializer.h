#pragma once
#include "json.hpp"
#include "Graphics.h"
#include "ContentManager.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Collider.h"
#include "Script.h"

using json = nlohmann::json;

class GameSerializer
{
private:
	Graphics *graphics;
	std::string scripts = "";

public:
	GameSerializer();

	// Import
	//GameScene*		ImportScene(std::string filename);

	GameObject*		ImportGameObject(json json_object, DirectX::XMFLOAT3 globalAmbient, int i);
	Transform*		ImportTransform(json json_object);
	MeshRenderer*	ImportMeshRenderer(json json_object);
	Camera*			ImportCamera(json json_object);
	Light*			ImportLight(json json_object);
	SphereCollider* ImportSphereCollider(json json_object);
	BoxCollider*	ImportBoxCollider(json json_object);
	Material*		ImportMaterial(json json_object);
	void			ImportScript(json json_object, int i);

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
	json ExportScript(Script *script);

	void SetGraphics(Graphics *graphics);
	void ClearScripts();
	std::string GetScripts();
};