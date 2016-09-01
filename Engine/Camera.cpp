#include "Camera.h"

Camera::Camera()
{ }

DirectX::XMMATRIX& Camera::GetViewMatrix()
{
	return DirectX::XMMatrixIdentity();
}

DirectX::XMMATRIX& Camera::GetProjectionMatrix()
{
	return DirectX::XMMatrixIdentity();
}