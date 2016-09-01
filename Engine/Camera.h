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

	float nearClippingPlane;
	float farClippingPlane;

	float fov;
	
public:
	Camera();

	DirectX::XMMATRIX& GetViewMatrix();
	DirectX::XMMATRIX& GetProjectionMatrix();
};