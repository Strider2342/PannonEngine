#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include "Vector3.h"

enum ProjectionType
{
	Perspective,
	Orthographic
};

class Camera
{
private:
	Vector3 position;
	Vector3 rotation;

	Vector3 up;

	DirectX::XMMATRIX matView;
	DirectX::XMMATRIX matProjection;
	
	float fov;
	float aspectRatio;
	float nearClippingPlane;
	float farClippingPlane;
	
public:
	Camera();

	DirectX::XMMATRIX& GetViewMatrix();
	DirectX::XMMATRIX& GetProjectionMatrix();
};