#include "Screen.h"

Screen::Screen()
{
}

DirectX::XMFLOAT3 Screen::ScreenToWorld(DirectX::XMFLOAT2 position)
{
	return DirectX::XMFLOAT3();
}

Camera* Screen::GetCamera()
{
	return camera;
}

void Screen::SetCamera(Camera *camera)
{
	this->camera = camera;
}
