#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include "Object.h"
#include "Vector3.h"

enum ProjectionType
{
	Perspective,
	Orthographic
};

class Camera : public Object
{
private:
	DirectX::XMMATRIX matView;
	DirectX::XMMATRIX matProjection;
	
	float fov;
	float aspectRatio;
	float nearClippingPlane;
	float farClippingPlane;
	
public:
	Camera();
	
	void Init();

	DirectX::XMMATRIX& GetViewMatrix();
	DirectX::XMMATRIX& GetProjectionMatrix();

	float GetFOV();
	float GetAspectRatio();
	float GetNearClippingPlane();
	float GetFarClippingPlane();
};