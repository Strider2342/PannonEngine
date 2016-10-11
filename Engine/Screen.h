#pragma once
#include <DirectXMath.h>
#include "Camera.h"

class Screen
{
	int width;
	int height;

	Camera *camera;

public:
	Screen();

	DirectX::XMFLOAT3 ScreenToWorld(DirectX::XMFLOAT2 position);

	// get
	Camera* GetCamera();

	// set
	void SetCamera(Camera *camera);
};