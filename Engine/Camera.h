#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include "Transform.h"
#include "Component.h"

enum ProjectionType
{
	Perspective,
	Orthographic
};

class Camera : public Component
{
private:
	Transform *transform;

	DirectX::XMMATRIX matView;
	DirectX::XMMATRIX matProjection;
	
	float fov;
	float aspectRatio;
	float nearClippingPlane;
	float farClippingPlane;
	
public:
	Camera();
	
	void Init();

	// get
	DirectX::XMMATRIX& GetViewMatrix();
	DirectX::XMMATRIX& GetProjectionMatrix();

	float GetFOV();
	float GetAspectRatio();
	float GetNearClippingPlane();
	float GetFarClippingPlane();

	Transform *GetTransform();

	// set
	void SetTransform(Transform *transform);

	void SetFOV(float fov);
	void SetAspectRatio(float aspectRatio);
	void SetNearClippingPlane(float nearClippingPlane);
	void SetFarClippingPlane(float farClippingPlane);
};