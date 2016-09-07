#include "Camera.h"

Camera::Camera()
{ }

void Camera::Init()
{
	fov = 75.0f;
	aspectRatio = 1280.0f / 720.0f;
	nearClippingPlane = 0.1f;
	farClippingPlane = 100.0f;
}

DirectX::XMMATRIX& Camera::GetViewMatrix()
{
	DirectX::XMVECTOR eyePos = transform->GetPosition().ToXMVector();
	DirectX::XMVECTOR focusPos = DirectX::XMVectorSet(transform->GetForward().GetX(), transform->GetForward().GetY(), transform->GetForward().GetZ(), 1.0f);
	DirectX::XMVECTOR upDir = DirectX::XMVectorSet(transform->GetUp().GetX(), transform->GetUp().GetY(), transform->GetUp().GetZ(), 1.0f);

	matView = DirectX::XMMatrixLookAtLH(eyePos, focusPos, upDir);
	//matView = DirectX::XMMatrixInverse(nullptr, matView);

	return matView;
}

DirectX::XMMATRIX& Camera::GetProjectionMatrix()
{
	matProjection = DirectX::XMMatrixPerspectiveFovLH(fov, aspectRatio, nearClippingPlane, farClippingPlane);

	return matProjection;
}