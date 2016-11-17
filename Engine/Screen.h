#pragma once
#include <DirectXMath.h>
#include "DirectXMathExtension.h"
#include "Camera.h"
#include "Ray.h"

class Screen
{
	int width;
	int height;

	Camera *camera;

public:
	Screen();
	Screen(int width, int height);

	Ray ScreenPointToRay(DirectX::XMFLOAT2 position);
	DirectX::XMFLOAT2 NormalizeScreenPoint(DirectX::XMFLOAT2 position);

	void ShowCursor(bool value);

	// get
	Camera* GetCamera();

	// set
	void SetCamera(Camera *camera);
};