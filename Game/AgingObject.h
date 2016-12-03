#pragma once
#include "Script.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "EnemyScript.h"
#include "Collider.h"

class AgingObject : public Script
{
private:
	float prev = -1.0f;
	float now;

	Material *material1;
	MeshRenderer *renderer1, *renderer2;

public:
	AgingObject()
	{
		material1 = new Material();
		renderer1 = new MeshRenderer();
		renderer2 = new MeshRenderer();
	}

	void Start()
	{
		material1->Init(gameObject->GetComponent<MeshRenderer>()->GetDev(), gameObject->GetComponent<MeshRenderer>()->GetDevcon());
		material1->GetShader().LoadVertexShaderPrecompiled(L"../Shaders/PhongVS.cso");
		material1->GetShader().LoadPixelShaderPrecompiled(L"../Shaders/PhongPS.cso");

		renderer1->SetMaterial(material1);
		renderer1->InitWithMat(gameObject->GetComponent<MeshRenderer>()->GetDev(), gameObject->GetComponent<MeshRenderer>()->GetDevcon());
		renderer1->SetMesh(gameObject->GetComponent<MeshRenderer>()->GetMesh());

		renderer2->SetMaterial(material1);
		renderer2->InitWithMat(gameObject->GetComponent<MeshRenderer>()->GetDev(), gameObject->GetComponent<MeshRenderer>()->GetDevcon());
		renderer2->SetMesh(gameObject->GetComponent<MeshRenderer>()->GetMesh());

		renderer1->GetMaterial()->SetDiffuse(1.0f, 0.4f, 0.4f);
		renderer2->GetMaterial()->SetDiffuse(0.4f, 0.4f, 1.0f);
	}

	void Update(GameTime gameTime, Input input)
	{
		renderer1->SetCamera(gameObject->GetComponent<MeshRenderer>()->GetCamera());
		renderer1->SetLights(gameObject->GetComponent<MeshRenderer>()->GetLights());
		renderer2->SetCamera(gameObject->GetComponent<MeshRenderer>()->GetCamera());
		renderer2->SetLights(gameObject->GetComponent<MeshRenderer>()->GetLights());

		now = gameTime.GetElapsedTime();
		if (prev == -1.0f)
		{
			prev = gameTime.GetElapsedTime();
		}
		gameObject->GetTransform()->GetLocalPosition().x += input.GetDeltaPosition().x * 0.01f;

		if (now - prev > 1.0f)
		{
			GameObject *gameobject = new GameObject();
			gameobject->GetTransform()->GetLocalPosition() = XMFLOAT3(1.0f, -1.5f, -0.2f);
			gameobject->GetTransform()->GetLocalScale() = XMFLOAT3(0.05f, 0.05f, 0.05f);
			gameobject->AddComponent<MeshRenderer>(renderer1);
			gameObject->AddComponent<SphereCollider>();
			gameObject->GetComponent<SphereCollider>()->SetRadius(8.0f);
			gameobject->AddComponent<EnemyScript>();
			gameobject->SetGameObjects(gameObject->GetGameObjects());
			gameobject->Start();

			gameObject->GetGameObjects()->push_back(gameobject);
			prev = gameTime.GetElapsedTime();
		}
	}

	void OnCollision()
	{
		//std::cout << "kjsdgvlkdjrfvg" << std::endl;
	}
};