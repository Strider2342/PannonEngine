#include "Camera.h"

Camera::Camera()
{
	fov = 75.0f;
	aspectRatio = 1280 / 720;
	nearClippingPlane = 0.0f;
	farClippingPlane = 100.0f;
}

DirectX::XMMATRIX& Camera::GetViewMatrix()
{
	DirectX::XMVECTOR eyePos = transform->GetPosition().ToXMVector();
	DirectX::XMVECTOR focusPos = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 1.0f);
	DirectX::XMVECTOR upDir = DirectX::XMVectorSet(transform->GetUp().GetX(), transform->GetUp().GetY(), transform->GetUp().GetZ(), 1.0f);

	matView = DirectX::XMMatrixLookAtLH(eyePos, focusPos, upDir);

	return matView;
}

DirectX::XMMATRIX& Camera::GetProjectionMatrix()
{
	matProjection = DirectX::XMMatrixPerspectiveFovLH(fov, aspectRatio, nearClippingPlane, farClippingPlane);

	return matProjection;
}